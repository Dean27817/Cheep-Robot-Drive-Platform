# $20 Combat Robot Drive Base
this is a project designed to make the world of combat robotics more accessible. It achieves this by lowering costs for the robot to just $20. No expensive controllers or motors. This robot will use a phone connected via Bluetooth as a controller and cheap drone motors for driving. It uses custom gearboxes for the drive that can be adjusted to give more torque or more speed. In order to make up for the lack of power from these motors it will use four of them controlled by a basic H-bridge motor controller. It uses the esp32-S3-ZERO from Waveshare to connect to the phone and act as a brain to control the H-bridge. This does mean that you will have to upload code, but the code is already written and you need to load it onto the esp32.

**use**<br>
This project will involve soldering to connect all the components (Listed in the BOM coming soon). 

1. You will need two pairs of motors (Two black and white and two red and blue). each pair will be soldered to one output on the H-Bridge to be controlled at the same time. make sure both of the black/blue wires are connected to the same channel on the H-bridge to make sure they spin in the same direction. 
2. The red power lead should then be soldered to the switch, and the other end of the switch soldered to the VCC pin on the H-bridge, and the black goes directly to the GND pin.
3. Solder the pins according to the table below
   
   |esp32|H-bridge|
   |-----|--------|
   |5V|VCC|
   |GND|GND|
   |GPIO2|in1|
   |GPIO3|in3|
   |GPIO4|in2|
   |GPIO5|in4|
   
   This is just the way it is in code right now, but you can change it if you need

   I need to move pin 2 (in4, Speed4) to a different pin, as aparently this pin is also used with the bluetooth connection
