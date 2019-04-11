#include "rosdogs_find_gap.hpp"

#define THRESHOLD 0.5

FindGapNode::FindGapNode(ros::NodeHandle* nodeHandle) {
	ROS_INFO("Initializing Find Gap Node");
	nh = *nodeHandle;
	initializeSubscribers();
	initializePublishers();
}

void FindGapNode::initializeSubscribers() {
	ROS_INFO("Initializing Find Gap subscribers");
	lidarSub = nh.subscribe("/scan", 10, &FindGapNode::LidarCallback, this);
}

void FindGapNode::initializePublishers() {
	ROS_INFO("Initializing Find Gap publishers");
	// gapPub = nh.advertise<>("lidar_gaps", 10);
	centerPub = nh.advertise<geometry_msgs::Vector3>("gap_center", 10);
}

void FindGapNode::LidarCallback(const sensor_msgs::LaserScan& msg) {

}

int main(int argc, char** argv) {
	ros::init(argc, argv, "find_gap");
	ros::NodeHandle nh;
	FindGapNode node(&nh);

	ros::spin();

	return 0;
}
