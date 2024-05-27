//cheep robot base
//created by dean morgan
//this code is designed to be used on a esp32-S3-Zero from waveshare
//it uses a basic 2 chanel H-Bridge motor controller, each chanel driving 2 motors with custom printed gearboxes

//used to see if the program is running on an esp32 board
#if !defined( ESP32 ) 
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting. 
#endif 

//defonitions to use the gamepad moduel on dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

//basic arduino library
#include <Arduino.h>
//used to allow the user to control the robot with their phone
#include <DabbleESP32.h>
//used for PWM
#include <ESP32PWM.h>
//define the pins that the inputs of the Motor controller will be solderd to
#define in1 5
#define in2 3
#define in3 4
#define in4 10

//creates the objects from the PWM library
ESP32PWM speedControl1;
ESP32PWM speedControl2;
ESP32PWM speedControl3;
ESP32PWM speedControl4;

//the maximum frequency of each pin
int freq = 1000;

void setup() {
  // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  //used for communication with the computer
  Serial.begin(9600);

  //starts the bluetooth connection
  Dabble.begin("Dean Morgan Drive Base");

  //tells the code wich pins are being used for each clock
  speedControl1.attachPin(in1, freq, 10);
  speedControl2.attachPin(in2, freq, 10);
  speedControl3.attachPin(in3, freq, 10);
  speedControl4.attachPin(in4, freq, 10);
}


void drive(float left, float right)
{
  //controls the left motors
  //each motor will take a value between 0 and 1
  if(left > 0)
  {
    speedControl1.writeScaled(abs(left));
    speedControl2.writeScaled(0);
  }
  else
  {
    speedControl1.writeScaled(0);
    speedControl2.writeScaled(abs(left));
  }

  //controls the right motors
  //each motor will take a value between 0 and 1
  if(right > 0)
  {
    speedControl3.writeScaled(abs(right));
    speedControl4.writeScaled(0);
  }
  else
  {
    speedControl3.writeScaled(0);
    speedControl4.writeScaled(abs(right));
  }
}



void loop() {
  //makes the esp32 reload the input from the phone
  Dabble.processInput();

  float forward = GamePad.getYaxisData()/7;
  float rotate = GamePad.getXaxisData()/7;

  drive(forward - rotate, forward + rotate);
}
