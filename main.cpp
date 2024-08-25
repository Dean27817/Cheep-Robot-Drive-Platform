#include "Arduino.h"
#include "ESP32Servo.h"
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
//define the pins that the inputs of the Motor controller will be soldered to
#define in1 10
#define in2 8
#define in3 3
#define in4 5

//creates the objects from the PWM library
ESP32PWM speedControl1;
ESP32PWM speedControl2;
ESP32PWM speedControl3;
ESP32PWM speedControl4;
XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

//the maximum frequency of each pin
int freq = 1000;
int controllerMode = 0;

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

  float buffer = 0.1;
  //controls the left motors
  //each motor will take a value between 0 and 1
  if(left > buffer || left < -buffer || right > buffer || right < -buffer)
  {
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
  else
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
  xboxController.begin();
  //tells the code which pins are being used for each clock
  speedControl1.attachPin(in1, freq, 10);
  speedControl2.attachPin(in2, freq, 10);
  speedControl3.attachPin(in3, freq, 10);
  speedControl4.attachPin(in4, freq, 10);

  //plays a startup on the drive motors
  drive(1, -1);
  delay(50);
  drive(0, 0);
  drive(1, -1);
  delay(50);
  drive(-1, 1);
  delay(100);
  drive(0, 0);
}

void loop()
{
   //refreshes the input from the xbox
  xboxController.onLoop();

  //checks if th3e controler is connected
  if(xboxController.isConnected())
  {
    //checks if the controler has been fully set up
    if(!xboxController.isWaitingForFirstNotification())
    {
        float left = ((xboxController.xboxNotif.joyRVert - 32767.5) / (65535))*2;
        float right = ((xboxController.xboxNotif.joyLVert - 32767.5) / (65535))*2;

        Serial.println(xboxController.xboxNotif.joyRVert);

        switch(controllerMode)
        {
          case 0:
          drive(0, 0);
          break;
          case 1:
          drive(((xboxController.xboxNotif.joyRVert - 32767.5) / (65535))*2, ((xboxController.xboxNotif.joyLVert - 32767.5) / (65535))*2);
          break;
          case 2:
          drive((((xboxController.xboxNotif.joyRVert - 32767.5) / (65535))*2) + (((xboxController.xboxNotif.joyRHori - 32767.5) / (65535))*2), (((xboxController.xboxNotif.joyRVert - 32767.5) / (65535))*2) - (((xboxController.xboxNotif.joyRHori - 32767.5) / (65535))*2));
          break;
          case 3:
          drive((((xboxController.xboxNotif.joyRVert - 32767.5) / (65535))*2) + (((xboxController.xboxNotif.joyLHori - 32767.5) / (65535))*2), (((xboxController.xboxNotif.joyRVert - 32767.5) / (65535))*2) - (((xboxController.xboxNotif.joyLHori - 32767.5) / (65535))*2));
          break;
        };
      }

      

      if(xboxController.xboxNotif.btnA)
      {
        controllerMode = 1;
      }
      else if (xboxController.xboxNotif.btnB)
      {
        controllerMode = 2;
      }
      else if (xboxController.xboxNotif.btnX)
      {
        controllerMode = 0;
      }
      else if (xboxController.xboxNotif.btnY)
      {
        controllerMode = 3;
      }
  }
}