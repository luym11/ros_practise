# [ETHZ ROS lectures](http://www.rsl.ethz.ch/education-students/lectures/ros.html)

## Exercise 1

- Way to publish to control gazebo husky (press Tab as much as you can)
		```
		rostopic pub /husky_velocity_controller/cmd_vel geometry_msgs/Twist -r 100 '[0.5,0,0]' '[0,0,0]'
		```
- Need to rebuild and resource when codes get changed
- If the program can't find something (eg., .world file), look at the launch file, use roscd to find correct path and put it there

## [Exercise 2](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/exercise2.pdf)

- yaml file: mind the format and the way to write topic name (/scan with "/")
- .hpp: include essential header files(msgs, C++ libraries, etc)
- .cpp: 
	- callback: use -> for vector
	- CORRECT WAY to write a subscriber and do some processing in callback function
- .launch: rosparam format
- Use RViz to visualize stuffs is better in Gazebo

## [Exercise 3](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/exercise3.pdf)

### Husky bumps into pillar
- Check the exact value of the members in sensor_msgs/LaserScan, it might not be what you imagined. 
- Need to adjust control gain to get good performance. 
- CORRECT WAY to write a publisher. 

### Visualize pillar observation

- Another publisher
- Include headers for message
- Compute using angle and distance, remember to use correct tf link to visualize in Gazebo

## [Exercise 4](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/exercise4.pdf)

- Make sure how nodes communicate by looking at their subs and pubs, and looking at topics as well
- To launch ekf node, need to load parameters from somewhere. In this example it's in husky_control package
- To use rqt_multiplot more efficiently, one can save the configuration file and load it directly next time
- For time, if anything in gazebo is loaded(eg., a world), the time will be set to use_sim_time. otherwise this should be set in the launch file by 

		```
		<param name="use_sim_time" value="true"/>

		```

And be sure to add --clock while playing rosbag

		```
		rosbag play data.bag --clock
		```

- For husky visualization in RViz, because it's not loaded via gazebo, we need to do 2 things
	- Add a robot_state_publisher node in the launch file(If you notice that there's already /ekf_localization_node publishing to /tf topic. Here's one explanation: because frame and husky config info is not complete only by /ekf's publications)

		```
		<node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher" />
		```

	- Husky's configuration need to be written in launch file. Do this by imitating spawn_husky.launch. Namely, these lines: 

		```
		  <arg name="husky_gazebo_description" default="$(optenv HUSKY_GAZEBO_DESCRIPTION)"/>
		  <arg name="laser_enabled" default="true"/>
		  <arg name="ur5_enabled" default="false"/>
		  <arg name="kinect_enabled" default="false"/>
		
		  <param name="robot_description" command="$(find xacro)/xacro.py '$(arg husky_gazebo_description)'
		    laser_enabled:=$(arg laser_enabled)
		    ur5_enabled:=$(arg ur5_enabled)
		    kinect_enabled:=$(arg kinect_enabled)
		    " />
		```

## [Exercise 5](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/exercise5.pdf)

- Implemented a service server to send bool info to a topic, /start_stop to control manual stop of husky
		```
		rosservice call /emergency_stop "data: true"
		```
- Implemented a service client to communicate with service server, send command from the client and receive feedback as an addition. 
		```
		rosrun husky_highlevel_controller husky_highlevel_controller_client 1      // for start, anything other than 1 for stop
		```
- Because there are more than one executables now, need to do a lot of modifications to CMakeLists.txt, especially in 
	- find_package
	- add_executable
	- target\_link\_libraries

- Need to modify package.xml accordingly
- Created a subs in Husky node to enable/disable husky by sending controller real signals or a constant
- Corresponding publ is in service server, as it's running all the time
- Don't know why but ROS\_DEBUG\_MESSAGE only shows while calling service server in console
- Didn't write client in launch file now. Can be done in future or add this in other parts of the program(automatic stop)

## References

- https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/exercise5.pdf    
- https://github.com/fairlight1337/ros_service_examples/blob/master/CMakeLists.txt   
- http://docs.ros.org/jade/api/std_srvs/html/srv/SetBool.html   
- https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/lecture4.pdf   
- http://wiki.ros.org/ROS/Tutorials/ExaminingServiceClient   



