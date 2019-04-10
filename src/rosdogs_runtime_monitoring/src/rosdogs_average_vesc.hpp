#pragma once

#include <queue>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <vesc_msgs/VescStateStamped.h>
#include <geometry_msgs/Twist.h>

#define QUEUE_SIZE 10


class AverageVescNode {
public:
	AverageVescNode(ros::NodeHandle* nodeHandle);
private:
	// Private member variables
	double velocitySum;
	std::queue<double> velocityQueue;
	ros::NodeHandle nh;
	ros::Subscriber vescSub;
	ros::Publisher velocityPub;

	// ROS initializers
	void initializeSubscribers();
	void initializePublishers();

	// Subscriber callbacks
	void VescCallback(const vesc_msgs::VescStateStamped& msg);

};
