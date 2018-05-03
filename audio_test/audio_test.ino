// Perkins Spinner Game Code
// Pins:
//      - Hall Effect - D12
//      - Button - D0
//      - Motor - Port 1 on Adafruit Motor Shield V2

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <WaveHC.h>
#include <WaveUtil.h>

// Sensing
int buttonPin = 0;
bool buttonState = false;
int hallEffectPin = A0;
float hallEffectValue;
float hallEffectAverageArray[5] = {1.0, 1.0, 1.0, 1.0, 1.0};
int arrLen = 5;
float hallEffectAverage = 0;
bool hallEffectState = false;
// Motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *spinner = AFMS.getMotor(1);
int motorSpeed = 150; // 0-255
int motorSpinupTime = 2000; //ms
// Music
SdReader card;
FatVolume vol;
FatReader root;
WaveHC wave;
uint8_t dirLevel;
dir_t dirBuf;

#define error(msg) error_P(PSTR(msg))
void play(FatReader &dir);

////////// Setup //////////

void setup() {
  Serial.begin(9600);
  
  // Init motor
  AFMS.begin();
  spinner->setSpeed(motorSpeed);

  // Init sensing
  pinMode(buttonPin, INPUT); 

  // Init music and sd reader
  if (!card.init()) {
    error("Card init. failed!");
  }  
  card.partialBlockRead(true);  
  uint8_t part;
  for (part = 0; part < 5; part++) {
    if (vol.init(card, part)) break;
  }
  if (part == 5) { error("No valid FAT partition!"); }
  if (!root.openRoot(vol)) { error("Can't open root dir!"); }
  Serial.println("SETUP COMPLETE");
}

////////// Main ///////////

void loop() {
  root.rewind();
  play(root);
}

////////// Audio Support /////////

void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}

void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

void play(FatReader &dir) {
  FatReader file;
  while (dir.readDir(dirBuf) > 0) {
    if (!DIR_IS_SUBDIR(dirBuf)
         && strncmp_P((char *)&dirBuf.name[8], PSTR("WAV"), 3)) {
      continue;
    }
    Serial.println();
    for (uint8_t i = 0; i < dirLevel; i++) {
       Serial.write(' ');
    }
    if (!file.open(vol, dirBuf)) { error("file.open failed"); }
    if (file.isDir()) {
      Serial.println();
      dirLevel += 2;
      play(file);
      dirLevel -= 2;    
    }
    else {
      if (!wave.create(file)) {
        putstring(" Not a valid WAV");
      } else {
        wave.play();
        
        uint8_t n = 0;
        while (wave.isplaying) {
          delay(100);
        }       
        sdErrorCheck();
      }
    }
  }
}

