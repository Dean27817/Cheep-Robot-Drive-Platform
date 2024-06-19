<h1>$20 Combat Robot Drive Base</h1><br>
this is a project designed to make the world of combat robotics more accessible. It achieves this by lowering costs for the robot to just $20. No expensive controllers or motors. This robot will use a phone connected via Bluetooth as a controller and cheap N20/N10 motors for driving. It uses the esp32-S3-ZERO from Waveshare to connect to the phone and act as a brain to control the H-bridge, which is a basic form of speed controler. This does mean that you will have to upload code, but the code is already written and you need to load it onto the esp32.

<h2>Current big update</h2><br>
I am happy to say that this robot is in a fully working MVP state. I still have to do major updates to the BOM and assembly guide, as well as do better commenting in my code, but the project now works in its entirety. There are still many things that I would like to do and fix with this project, but for now, it works.

<h2>assembly</h2>
<h3>Electronics and programming</h3><br>
This project will involve soldering to connect all the components (Listed in the BOM). 

1. You will need a pairs of motors. each motor will be soldered to one output on the H-Bridge. make sure both of the black/blue wires are connected to the same channel on the H-bridge to make sure they spin in the same direction. 
2. The red power lead should then be soldered to the switch, and the other end of the switch soldered to the VCC pin on the H-bridge, and the black goes directly to the GND pin.
3. Solder the pins according to the table below
   
   |esp32|H-bridge|
   |-----|--------|
   |5V|VCC|
   |GND|GND|
   |GPIO5|in1|
   |GPIO3|in3|
   |GPIO4|in2|
   |GPIO10|in4|
   
   This is just the way it is in code right now, but you can change it if you solder it differently


4. Upload the code to the ESP32. You will need to install the ESP32Servo Library (Used for the ESP32PWM) and the DabbleESP32 library (used for bluetooth). Also make sure to change the name in the Dabble.begin call in the setup function as this will be the name that will show up in the bluetooth connection. When you go to upload you will need to make sure that you have installed the ESP32 add on if you are using the arduino IDE (toutorial here: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

<h3>Chassis</h3><br>
The chassis for this robot is entirely 3D printed. It is designed as a simple wedge so it is just the wheels and a basic body. I am pretty happy with how the body is (although I havent tested the switch hole yet). the motors fit into the slots by the holes in the sides and are held in with zip-ties (though also using hot glue is recomended). the wheels have slots for a M2 nut to fit into and have a bolt go through to hold them in place. All of the electronics go in front of the motors (pics coming soon). The TPU wheels work, but have very little traction with the floor.

<h2>TODO</h2><br>
Finish failsafes<br>
Finish assembly guide<br>
Take and upload photos for assembly and electronics<br>
Finish code comments<br>
