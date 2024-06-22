/*
  Cheep robot base
    > created by Dean Morgan
  
  This base code was designed with the following hardware in mind:
    > Waveshare esp32-S3-zero
    > 2 channel H-Bridge motor controller
    > Maximum of 2 motors
      > one left motor and one right motor
*/

//used to see if the program is running on an esp32 board
#if !defined( ESP32 ) 
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting. 
#endif 

//definitions to use the game-pad module on dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

//basic arduino library
#include <Arduino.h>
//used to allow the user to control the robot with their phone
#include <DabbleESP32.h>
//used for PWM
#include <ESP32PWM.h>
//define the pins that the inputs of the Motor controller will be soldered to
#define in1 6
#define in2 5
#define in3 8
#define in4 7

//creates the objects from the PWM library
ESP32PWM speedControl1;
ESP32PWM speedControl2;
ESP32PWM speedControl3;
ESP32PWM speedControl4;

//the maximum frequency of each pin
int freq = 1000;

float forward;
float rotate;

//used to make the code for the robot look cleaner
//takes the speed the left and right motors should go (from -1 to 1) and works with the PWM to make them move appropriately
void drive(float left, float right)
{
  //reverses the left or right motor
  //makes it so that if one is soldered backwards you dont have to worry about it because you can just reverse one of the motors
  left *= -1; 
  right *= -1;
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

  if(right == 0 && left == 0)
  {
    speedControl1.writeScaled(0);
    speedControl2.writeScaled(0);
    speedControl3.writeScaled(0);
    speedControl4.writeScaled(0);
  }
}

void setup() {
  // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  //used for communication with the computer
  Serial.begin(9600);

  //starts the bluetooth connection
  Dabble.begin("Cheep Chirp Speed");

  //tells the code which pins are being used for each clock
  speedControl1.attachPin(in1, freq, 10);
  speedControl2.attachPin(in2, freq, 10);
  speedControl3.attachPin(in3, freq, 10);
  speedControl4.attachPin(in4, freq, 10);

  //plays a startup on the drive motors
  drive(1, -1);
  delay(50);
  drive(0, 0);
  Dabble.waitForAppConnection();
  drive(1, -1);
  delay(50);
  drive(-1, 1);
  delay(100);
  drive(0, 0);
}

void loop() {
  //Makes the ESP32 reload the input from the phone
  Dabble.processInput();

  //Check if the device is connected
  if (!esp32ble.available()) {
    // If connected, allow the robot to move
      forward = -1 * ((0.002915451895044) * (GamePad.getYaxisData() * GamePad.getYaxisData() * GamePad.getYaxisData()));
      rotate = -1 * (GamePad.getXaxisData()/10);  
    drive(rotate - forward, rotate + forward);
  } else {
    //If not connected, stop the robot
    drive(0, 0);
    //add a message to indicate disconnection
    Serial.println("App disconnected. Stopping the robot.");
  }
  
  //Continue to wait for app connection in the loop
  Dabble.waitForAppConnection();
}