#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
	nodeHandle.getParam("/husky_highlevel_controller/husky/topic_name", topic_name); 
	nodeHandle.getParam("/husky_highlevel_controller/husky/queue_size", queue_size);     
	ROS_INFO_STREAM(topic_name << " " << queue_size); 
	laser_scan_subs = nodeHandle.subscribe( topic_name, queue_size, &HuskyHighlevelController::laser_scan_Callback, this); 
}

void HuskyHighlevelController::laser_scan_Callback( const sensor_msgs::LaserScan::ConstPtr& laser_scan_msgs ){
	minDistance = 30; 
	laser_scan_distance = laser_scan_msgs->ranges;
	ROS_INFO_STREAM("msgs received" << std::endl); 
	for(int i = 0; i < laser_scan_distance.size(); i++){
		// ROS_INFO_STREAM("The " << i << "st message in " << laser_scan_distance.size() << " messages");
		 if(minDistance > laser_scan_distance[i]) minDistance = laser_scan_distance[i]; 
	}
	ROS_INFO_STREAM("minDistance detected by Lidar: " << minDistance << " ");
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

} /* namespace */
