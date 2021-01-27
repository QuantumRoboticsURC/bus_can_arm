# bus_can_arm

A simple CAN system that reads twist messages and sends them over a network CAN1 using CTRE Phoenix class library on Linux/JetsonTX2/RaspPi platforms. It’s a complement to the simple_arm repository.
  
##
![controller](https://raw.githubusercontent.com/QuantumRoboticsURC/simple_drive/main/images/simple_arm_controller.png)


```
1. SOFTWARE SETUP:

Once you have your Device setup open a terminal and run the following commands to install necessary files.
$ sudo apt-get upgrade
$ sudo apt-get update
$ sudo apt-get upgrade

Install CAN tools
$ sudo apt-get install can-utils.

Install necessary libs to build example.
$ sudo apt-get install cmake
$ sudo apt-get install libsdl2-dev

Clone repo into user directory git clone
$ cd catkin/ws
$ git clone https://github.com/QuantumRoboticsURC/bus_can_arm.git

Navigate into repo
$ cd catkin_ws/src/bus_can_arm/src

Chmod shell scripts to allow you to use them:
$ chmod +x canableStart.sh

Bring up can1 ./canableStart.sh (if you see the message Device or resource busy it means the can network is already up and requires no further action).
$ ./canableStart.sh

```

2. LAUNCH ROS NODES:

```
$ rosrun  bus_can_arm arm_can
```

