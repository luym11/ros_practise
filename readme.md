##Exercise 1

- Correct way to publish to control gazebo husky

	rostopic pub /husky_velocity_controller/cmd_vel geometry_msgs/Twist -r 100 '[0.5,0,0]' '[0,0,0]'

- Each time changes code, need to rebuild and resource
- If the program can't find something (eg., .world file), look at the launch file, use roscd to find correct place and put the files there

##Exercise 2

- yaml file: care about the format and the way to write topic name (/scan)
- .hpp: include essential header files
- .cpp: 
	- callback: use -> for vector
- .launch: rosparam format

