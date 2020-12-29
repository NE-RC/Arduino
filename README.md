# Arduino

An Arduino Uno receives a custom ROS message from the Jetson TX2 and writes PWM signals to the servo and motor controller. Also reads from a quadrature encoder connected to the gearbox and sends encoder data to the Jetson.

Use `./upload` to upload the `arduino_node.ino` sketch from command line without the IDE.

# Installing Arduino IDE on Jetson TX2 (not tested on TX1)
1. Download the latest aarch64 Arduino IDE
  >- [Arduino 1.8.7](https://www.arduino.cc/download_handler.php?f=/arduino-1.8.7-linuxaarch64.tar.xz)
  >- Sourced from [here](https://github.com/arduino/arduino/issues/7302)
2. Install necessary JDK and/or JRE
  >- Try `sudo apt-get install default-jdk` (needs to be verified to work)
