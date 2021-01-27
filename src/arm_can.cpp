#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "ctre/phoenix/cci/Unmanaged_CCI.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <unistd.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <geometry_msgs/Twist.h>



using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;


/* make some talons for drive train */

VictorSPX tal1(4); //Base
VictorSPX tal2(5); //Codo 1
VictorSPX tal3(6); //Codo 2
VictorSPX tal4(7); //Codo 3


void initDrive()
{
	/* both talons should blink green when driving forward */
	//printf("Init Drive started");
	tal1.SetInverted(true);
}

void drive(double motor1, double motor2, double motor3, double motor4)
{
        tal1.Set(ControlMode::PercentOutput, motor1);   //Base
        tal2.Set(ControlMode::PercentOutput, motor2);   //Codo1
        tal3.Set(ControlMode::PercentOutput, motor3);   //Codo2
        tal4.Set(ControlMode::PercentOutput, motor4);   //Codo3
}

/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

float base, joint1, joint2, joint3;

void filterVelocityCallback(const geometry_msgs::Twist& msg){
   //Using the callback function just for subscribing  
   //Subscribing the message and storing it in 'base', and 'joint#'
   base = msg.angular.x;
   joint1 = msg.linear.x; //
   joint2 = msg.linear.y; //Leyendo valores palanca dewrecha -1 a 1
   joint3 = msg.linear.z; //Leyendo valores

}

int main(int argc, char **argv) {
      	
	/* don't bother prompting, just use can0 */

	std::string interface;
	interface = "can1";
	ctre::phoenix::platform::can::SetCANInterface(interface.c_str());

	/* setup drive */
	initDrive();
        drive(0, 0, 0, 0);
	while (true) {
                ros::init(argc, argv, "arm_can");
		ros::NodeHandle nh;
                ros::Subscriber sub = nh.subscribe("arm_teleop", 10, &filterVelocityCallback);

		while (ros::ok()){
			/* grab some stick values */
                        drive(base, joint1, joint2, joint3); // 1 1

			ctre::phoenix::unmanaged::FeedEnable(100);	
			/* loop yield for a bit */
			sleepApp(20);

     			ros::spinOnce();      //Notice this
		}
		
                drive(0, 0, 0, 0);
		
	}

	SDL_Quit();
	return 0;
}
