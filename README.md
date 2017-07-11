# [ETHZ ROS lectures](http://www.rsl.ethz.ch/education-students/lectures/ros.html)
## Exercise 1

- Correct way to publish to control gazebo husky

	rostopic pub /husky_velocity_controller/cmd_vel geometry_msgs/Twist -r 100 '[0.5,0,0]' '[0,0,0]'

- Each time changes code, need to rebuild and resource
- If the program can't find something (eg., .world file), look at the launch file, use roscd to find correct place and put the files there

## Exercise 2

- yaml file: care about the format and the way to write topic name (/scan)
- .hpp: include essential header files
- .cpp: 
	- callback: use -> for vector
- .launch: rosparam format

## Exercise 3

### Husky bumps into pillar
- check the exact value of sensor_msgs/LaserScan, this time the values are not what I imagined
- Need to adjust control gain to get good performance

### Visualize pillar observation

- include headers for message
- correct tf link
## Exercise 4

- Make sure how nodes communicate by looking at their subs and pubs, and looking at topics as well
- for launch ekf node, need to load parameters from somewhere
- to use rqt_multiplot, can save the configuration file and load it directly next time
- for time, if anything in gazebo is loaded(eg., a world), the time will be set to use_sim_time. otherwise this should be set in the launch file by 
        ```
	<param name="use_sim_time" value="true"/>
	```
And be sure to add --clock while playing rosbag

	```
	rosbag play data.bag --clock
	```
- for husky visualization in RViz, because it's not loaded via gazebo, we need to do 2 things
	- Add a robot_state_publisher node in the launch file(But there's already /ekf_localization_node publishing to /tf topic?: Because frame and husky config info is not complete only by /ekf)
		```
		<node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher" />
		```
	- Husky's configuration need to be written in launch file. Do this by imitating spawn_husky.launch
	
## Exercise 5

- implemented a service server to send some info to a topic, /start_stop to control manual stop of husky
		```
		rosservice call /emergency_stop "data: true"
		```
- implemented a service client to communicate with service server, send command from the client and receive feedback as an addition. 
		```
		rosrun husky_highlevel_controller husky_highlevel_controller_client 1      // for start, anything other than 1 for stop
		```
- Because there are more than one executables now, need to do a lot of modifications to CMakeLists.txt, especially in 
	- find_package
	- add_executable
	- target_link_libraries

- Need to modify package.xml accordingly
- Created a subs in Husky node to enable/disable husky by sending controller real signal or a constant
- According publ is in service server, as it's running all the time
- Don't know why but ROS_DEBUG_MESSAGE only shows while calling service server in console


- Didn't write client in launch file now. Can be done in future or add this in other parts of the program(automatic stop)

###Refs

https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/exercise5.pdf    
https://github.com/fairlight1337/ros_service_examples/blob/master/CMakeLists.txt   
http://docs.ros.org/jade/api/std_srvs/html/srv/SetBool.html   
https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/lecture4.pdf   
http://wiki.ros.org/ROS/Tutorials/ExaminingServiceClient   



