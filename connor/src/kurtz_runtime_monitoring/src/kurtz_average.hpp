#pragma once

#include <queue>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

#define QUEUE_SIZE 10


class AverageVelocityNode {
public:
	AverageVelocityNode(ros::NodeHandle* nodeHandle);
private:
	// Private member variables
	double velocitySum;
	std::queue<double> velocityQueue;
	ros::NodeHandle nh;
	ros::Subscriber cmdSub;
	ros::Publisher velocityPub;

	// ROS initializers
	void initializeSubscribers();
	void initializePublishers();

	// Subscriber callbacks
	void velocityCallback(const geometry_msgs::Twist& msg);

};
