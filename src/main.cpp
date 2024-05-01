//cheep robot base
//created by dean morgan
//this code is designed to be used on a esp32-S3-Zero from waveshare
//it uses a basic 2 chanel H-Bridge motor controller, each chanell drivig 2 motors with custom printed gearboxes

//defonitions to use the gamepad modual on dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

//basic arduino library
#include <Arduino.h>
//used to allow the user to control the robot with their phone
#include <DabbleESP32.h>
//define the pins that the inputs of the Motor controller will be solderd to
#define HBridge1 4
#define HBridge2 5

void setup() {
    //used for communication with the computer
    Serial.begin(9600);
    //used for communication over bluetooth
    Dabble.begin("Basic Drive Base");
}

void loop() {
  Dabble.processInput();
  Serial.println("x: ");
  Serial.print(GamePad.getXaxisData());
  Serial.print(" y: "); 
  Serial.print(GamePad.getYaxisData());
}

