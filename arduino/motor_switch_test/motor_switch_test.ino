#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

int buttonPin = 0;
int hallEffectPin = 12;
float hallEffectValue;
float hallEffectAverageArray[5];
int arrLen = 5;
float hallEffectAverage = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *spinner = AFMS.getMotor(1);

void setup() {
  Serial.begin(9600);
  
  AFMS.begin();
  spinner->setSpeed(200);

  pinMode(buttonPin, INPUT); 
  pinMode(hallEffectPin, INPUT);
}

void loop() {
  // Test spinner and button response
  Serial.print("Button: ");
  if (digitalRead(buttonPin)) {
    Serial.println(0);
    spinner->run(RELEASE);
  } else {
    Serial.println(1);
    spinner->run(FORWARD);
  }

  //Test Hall Effect sensor
  hallEffectValue = digitalRead(hallEffectPin);
  for(int i=1; i<arrLen; i++) {
    hallEffectAverageArray[i] = hallEffectAverageArray[i-1]; 
  }
  hallEffectAverageArray[0] = hallEffectValue;
  for(int i=0; i<arrLen; i++) {
    hallEffectAverage += hallEffectAverageArray[i];
  }
  Serial.print("Hall Effect: ");
  Serial.println(hallEffectAverage/arrLen);
  hallEffectAverage = 0;
  
  delay(100);
}
