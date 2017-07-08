#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include <string>
#include <std_msgs/Float32.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#define pi 3.1419265358

using std::vector;
using std::string;

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	void laser_scan_Callback( const sensor_msgs::LaserScan::ConstPtr& laser_scan_msgs );
	vector<float> laser_scan_distance; 
	string topic_name; 
	int queue_size;
	float minDistance; 
	float pillarAngle; 
	void husky_angle_controller(float angle); 
	geometry_msgs::Twist cmd_vel_command; 
	float control_gain; 
	int direction_index; 
	void pillar_vis_marker_func(); 

	ros::Subscriber laser_scan_subs;
	ros::Publisher controlled_cmd_vel_publ; 
	ros::Publisher pillar_vis; 
 
};

} /* namespace */
