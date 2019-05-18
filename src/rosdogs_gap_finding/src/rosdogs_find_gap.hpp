#pragma once

#include <vector>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Vector3.h>

class FindGapNode {
public:
	FindGapNode(ros::NodeHandle* nodeHandle);
private:
	ros::NodeHandle nh;
	ros::Subscriber lidarSub;
	ros::Publisher gapPub;
	ros::Publisher centerPub;
	
	void initializeSubscribers();
	void initializePublishers();
	
	void LidarCallback(const sensor_msgs::LaserScan& msg);

};

class RadialGap{
	public:
		RadialGap(float start, float end, float r);
		~RadialGap();
		float th_start;
		float th_end;
		float radius;
		geometry_msgs::Vector3 center;

};

class GapBag{
	public:
		int num_gaps;
		std::vector<RadialGap> gaps;
};