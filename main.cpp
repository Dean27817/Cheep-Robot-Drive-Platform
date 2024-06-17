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
#define in3 10
#define in4 8

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
//takes the speed the left and right motors should go (from -1 to 1) and works with the PWM to make them move appropriatly
void drive(float left, float right)
{
  //reverses the left or right motor
  //makes it so that if one is solderd backwards you dont have to worry about it because you can just reverse one of the motors
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
  Dabble.begin("Dean Morgan Drive Base");

  //tells the code wich pins are being used for each clock
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
  if (Dabble.isAppConnected()) {
    // If connected, allow the robot to move
      forward = -1 * ((0.002915451895044) * (GamePad.getYaxisData() * GamePad.getYaxisData() * GamePad.getYaxisData()));
      rotate = 1 * (((0.002915451895044) * (GamePad.getXaxisData() * GamePad.getXaxisData() * GamePad.getXaxisData()))/2);    
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