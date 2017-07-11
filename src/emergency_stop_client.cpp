#include <ros/ros.h>
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <std_srvs/SetBool.h>
#include <cstdlib>

int main(int argc, char **argv) {
	ros::init(argc, argv, "emergency_stop_client");
	if (argc != 2) {
		ROS_INFO("usage incorrect");
		return 1;
	}
	ros::NodeHandle nh;
	
	ros::ServiceClient client = nh.serviceClient<std_srvs::SetBool>("emergency_stop");
	std_srvs::SetBool service;
	//for(int i = 0; i < argc; i++){
	//	ROS_INFO("%d %s \n", i, argv[i]);
	//}
	if(atoi(argv[1]) == 1){
		ROS_INFO("It's true"); 
		service.request.data = true; 
	}else{
		service.request.data = false;
	}
	if (client.call(service)) {
		ROS_INFO("Result: %B", (bool)service.response.success);
		if(service.response.success == true){
			
			ROS_DEBUG_STREAM(service.response.message);
		} else{
			
			ROS_DEBUG_STREAM(service.response.message);		
		}
	} else {
		ROS_ERROR("Failed to call service emergency_stop");
		return 1;
	}
	return 0;
} 
