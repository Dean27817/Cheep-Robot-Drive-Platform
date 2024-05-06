//cheep robot base
//created by dean morgan
//this code is designed to be used on a esp32-S3-Zero from waveshare
//it uses a basic 2 chanel H-Bridge motor controller, each chanel driving 2 motors with custom printed gearboxes

//defonitions to use the gamepad modual on dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

//basic arduino library
#include <Arduino.h>
//used to allow the user to control the robot with their phone
#include <DabbleESP32.h>
//used to control PWM for the MC
#include <ESP32Servo.h>
//Used to make the speed controller easier to work with
#include "ESC.h"


//define the pins that the inputs of the Motor controller will be solderd to
#define in1 5
#define in2 3
#define in3 4
#define in4 2

//defines the limits of the speeds being sent
#define MIN_SPEED 0 // speed just slow enough to turn motor off
#define MAX_SPEED 2000 // speed where my motor drew 3.6 amps at 12v.

//declaring an ESC object for each "in" pin
ESC Speed1(in1, 0, 3000, 500);
ESC Speed2(in2, 0, 3000, 500);
ESC Speed3(in3, 0, 3000, 500);
ESC Speed4(in4, 0, 3000, 500);

void setup() {
    //used for communication with the computer
    Serial.begin(9600);
    //starts the bluetooth connection
    Dabble.begin("Dean Morgan Drive Base");
    delay(1000);

    //Allow the pins to send electricity out
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    //prepares the pins for PWM
    Speed1.arm();
    Speed2.arm();
    Speed3.arm();
    Speed4.arm();
}

void loop() {
  //makes the esp32 reload the input from the phone
  Dabble.processInput();

  //gets the speed values that the left and right wheels should be traveling
  //the multiplication is to take the -7 to 7 value given by dabble and turns it into a usable value to use in the ESC functions
  double Left = (GamePad.getYaxisData() - GamePad.getXaxisData()) * (MAX_SPEED/7);
  double Right = (GamePad.getYaxisData() - GamePad.getXaxisData()) * (MAX_SPEED/7);

  //right wheel forward
  if(Right > 0.2)
  {
    digitalWrite(in1, LOW);
    Speed2.speed(abs(Right));
  }
  //right wheel stop
  else if(Right > -0.2 && Right < 0.2)
  {
    Speed1.stop();
    Speed2.stop();
  }
  //right wheel backwards
  else 
  {
    digitalWrite(in2, LOW);
    Speed1.speed(abs(Right));
  }


  //left wheel forward
  if(Left > 0.2)
  {
    digitalWrite(in3, LOW);
    Speed4.speed(abs(Left));
  }
  //left wheel stop
  else if(Left > -0.2 && Left < 0.2)
  {
    Speed3.stop();
    Speed4.stop();
  }
  //left wheel backwards
  else 
  {
    digitalWrite(in4, LOW);
    Speed3.speed(abs(Left));
  }
}