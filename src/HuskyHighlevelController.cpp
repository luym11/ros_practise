#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
	nodeHandle.getParam("/husky_highlevel_controller/husky/topic_name", topic_name); 
	nodeHandle.getParam("/husky_highlevel_controller/husky/queue_size", queue_size);   
	nodeHandle.getParam("/husky_highlevel_controller/husky/control_gain", control_gain);   
	ROS_INFO_STREAM(topic_name << " " << queue_size); 
	laser_scan_subs = nodeHandle.subscribe( topic_name, queue_size, &HuskyHighlevelController::laser_scan_Callback, this); 
	controlled_cmd_vel_publ = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 1); 
	pillar_vis = nodeHandle.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
}

void HuskyHighlevelController::laser_scan_Callback( const sensor_msgs::LaserScan::ConstPtr& laser_scan_msgs ){
	minDistance = 30; 
	direction_index = 0; 
	laser_scan_distance = laser_scan_msgs->ranges;
	ROS_INFO_STREAM("msgs received" << std::endl); 
	for(int i = 0; i < laser_scan_distance.size(); i++){
		
		if(minDistance > laser_scan_distance[i]) {
			minDistance = laser_scan_distance[i];
			 direction_index = i; 
		}
	}
	pillarAngle =  -0.785 + 1.5*pi/720 * direction_index; 
	husky_angle_controller(2, pillarAngle); 
	controlled_cmd_vel_publ.publish(cmd_vel_command);
	pillar_vis_marker_func(); 
	ROS_INFO_STREAM("The " << direction_index << "st message is chosen in " << laser_scan_distance.size() << " messages");
	ROS_INFO_STREAM("minDistance detected by Lidar: " << minDistance << ", angle is " << pillarAngle);
	ROS_INFO_STREAM("Angle_min " << laser_scan_msgs->angle_min << ", Angle_increment " << laser_scan_msgs->angle_increment);
}

void HuskyHighlevelController::husky_angle_controller(float speed; float angle){
	// let the husky go at a constant speed
	// read the angle towards the pillar, and use PID to turn the husky to the pillar (control the angle to 0)
	cmd_vel_command.linear.x = speed; 
	cmd_vel_command.angular.z = control_gain * (0 - (angle-pi/2)); 
	
}

void HuskyHighlevelController::pillar_vis_marker_func(){
	visualization_msgs::Marker marker;
	marker.header.frame_id = "base_laser";
	marker.header.stamp = ros::Time();
	marker.ns = "my_namespace";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::SPHERE;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position.y = minDistance * cos(pillarAngle);
	marker.pose.position.x = minDistance * sin(pillarAngle);
	marker.pose.position.z = 1;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 0.0;
	marker.scale.x = 1;
	marker.scale.y = 1;
	marker.scale.z = 1;
	marker.color.a = 1.0; // Don't forget to set the alpha!
	marker.color.r = 0.0;
	marker.color.g = 0.0;
	marker.color.b = 1.0;
	//only if using a MESH_RESOURCE marker type:
	marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
	pillar_vis.publish( marker );
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

} /* namespace */
