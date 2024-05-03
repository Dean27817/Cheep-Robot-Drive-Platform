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
#define in1 5
#define in2 3
#define in3 4
#define in4 2

void setup() {
    //used for communication with the computer
    Serial.begin(9600);
    //used for communication over bluetooth
    Dabble.begin("Basic Drive Base");
}

void loop() {
  //makes the esp32 reload the input from the phone
  Dabble.processInput();

  //prints the X and Y cordonates from the phone
  //for some reason its values between -7 and 7
  //I need PWM values, so i do math for that.
  Serial.println("x: ");
  Serial.print((GamePad.getXaxisData() + 7) * 18.2142857143);
  Serial.print(" y: "); 
  Serial.print((GamePad.getYaxisData() + 7) * 18.2142857143);

  //gets the speed values that the left and right wheels should be traveling
  double Left = GamePad.getYaxisData() - GamePad.getXaxisData();
  double Right = GamePad.getYaxisData() - GamePad.getXaxisData();

  //writes the PWM values to the pins that will control the motors.
  analogWrite(in1, (GamePad.getXaxisData()+7) * 18.2142857143);
  analogWrite(in4, (GamePad.getYaxisData()+7) * 18.2142857143);
  analogWrite(in1, (GamePad.getXaxisData()+7) * 0);
  analogWrite(in4, (GamePad.getYaxisData()+7) * 0);
}