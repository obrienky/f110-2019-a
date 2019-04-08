#include "kurtz_average.hpp"


AverageVelocityNode::AverageVelocityNode(ros::NodeHandle* nodeHandle) {
	ROS_INFO("Initializing Average Velocity Node");
	nh = *nodeHandle;
	velocitySum = 0;
	initializeSubscribers();
	initializePublishers();
}

void AverageVelocityNode::initializeSubscribers() {
	ROS_INFO("Initializing Subscribers");
	cmdSub = nh.subscribe("/turtle1/cmd_vel", 10, &AverageVelocityNode::velocityCallback, this);
}

void AverageVelocityNode::initializePublishers() {
	ROS_INFO("Initializing Publishers");
	velocityPub = nh.advertise<std_msgs::Float64>("average_velocity", 10);
}

void AverageVelocityNode::velocityCallback(const geometry_msgs::Twist& msg) {
	//Store new velocity in queue
	velocityQueue.push(msg.linear.x);
	velocitySum += msg.linear.x;
	
	//Calculate average value of queue
	while (velocityQueue.size() > QUEUE_SIZE) {
		velocitySum -= velocityQueue.front();
		velocityQueue.pop();
	}
	double averageValue = velocitySum / velocityQueue.size();

	//ROS_INFO average value
	ROS_INFO("Adding velocity of %f makes the new average %f", msg.linear.x, averageValue);

	//Publish average value
	std_msgs::Float64 pubVal;
	pubVal.data = averageValue;
	velocityPub.publish(pubVal);
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "kurtz_average");
	ros::NodeHandle nh;
	AverageVelocityNode node(&nh);

	ros::Rate rate = ros::Rate(5);
	while (ros::ok()) {
		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
