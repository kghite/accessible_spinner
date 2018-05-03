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
int hallEffectPin = 12;
float hallEffectValue;
float hallEffectAverageArray[5] = {1.0, 1.0, 1.0, 1.0, 1.0};
int arrLen = 5;
float hallEffectAverage = 0;
bool hallEffectState = false;
// Motors
int vibrationPin = 8;
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
// Button timer
int timeSinceButton = 0; //ms
int unlockTime = 7000; //ms

#define error(msg) error_P(PSTR(msg))
void play(FatReader &dir);

////////// Setup //////////

void setup() {
  Serial.begin(9600);
  Serial.println("STARTING SETUP");
  
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
  //root.ls(LS_R | LS_FLAG_FRAGMENTED); // DEBUG: Check files found
  Serial.println("SETUP COMPLETE");
}

////////// Main ///////////

void loop() {
  // Get sensing updates
  getButtonUpdate();
  getHallEffectUpdate();

  Serial.println(buttonState);
  Serial.println(hallEffectState);

  // Respond to button or manual spin
  if (buttonState == true) {
    spinUpMotor();
  }
  if (hallEffectState == true) {
    // Play audio
    root.rewind();
    play(root);
    respondHallEffect();
  }

  // Reset sensing
  buttonState = false;
  hallEffectState = false;

  delay(500);
}

////////// Sensing and Motor Support //////////

void getButtonUpdate() {
  Serial.print("Button: ");
  if (digitalRead(buttonPin)) {
    buttonState = false;
  }
  else {
    buttonState = true;
  }
  Serial.println(buttonState);
}

void getHallEffectUpdate() {
  hallEffectValue = digitalRead(hallEffectPin);
  for(int i=1; i<arrLen; i++) {
    hallEffectAverageArray[i] = hallEffectAverageArray[i-1]; 
  }
  hallEffectAverageArray[0] = hallEffectValue;
  for(int i=0; i<arrLen; i++) {
    hallEffectAverage += hallEffectAverageArray[i];
  }
  Serial.print("Hall Effect: ");
  hallEffectAverage = hallEffectAverage/arrLen;
  if (hallEffectAverage > 0.0) {
    hallEffectState = false;
  } else {
    hallEffectState = true;
  }
  Serial.println(hallEffectState);
  hallEffectAverage = 0.0;
}

void spinUpMotor () {
  Serial.println("Button response");
  spinner->run(FORWARD);
  delay(motorSpinupTime);
  spinner->run(RELEASE);
}

void respondHallEffect() {
  Serial.println("Hall Effect response");
  // Run vibration motors
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
  while (dir.readDir(dirBuf) > 0) {    // Read every file in the directory one at a time
  
    // Skip it if not a subdirectory and not a .WAV file
    if (!DIR_IS_SUBDIR(dirBuf)
         && strncmp_P((char *)&dirBuf.name[8], PSTR("WAV"), 3)) {
      continue;
    }

    Serial.println();            // clear out a new line
    
    for (uint8_t i = 0; i < dirLevel; i++) {
       Serial.write(' ');       // this is for prettyprinting, put spaces in front
    }
    if (!file.open(vol, dirBuf)) {        // open the file in the directory
      error("file.open failed");          // something went wrong
    }
    
    if (file.isDir()) {                   // check if we opened a new directory
      putstring("Subdir: ");
      printEntryName(dirBuf);
      Serial.println();
      dirLevel += 2;                      // add more spaces
      // play files in subdirectory
      play(file);                         // recursive!
      dirLevel -= 2;    
    }
    else {
      // Aha! we found a file that isnt a directory
      putstring("Playing ");
      printEntryName(dirBuf);              // print it out
      if (!wave.create(file)) {            // Figure out, is it a WAV proper?
        putstring(" Not a valid WAV");     // ok skip it
      } else {
        Serial.println();                  // Hooray it IS a WAV proper!
        wave.play();                       // make some noise!
        
        uint8_t n = 0;
        while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
          putstring(".");
          if (!(++n % 32))Serial.println();
          delay(100);
        }       
        sdErrorCheck();                    // everything OK?
        // if (wave.errors)Serial.println(wave.errors);     // wave decoding errors
      }
    }
  }
}
