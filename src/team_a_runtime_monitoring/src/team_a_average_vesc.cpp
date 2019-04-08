#include "team_a_average_vesc.hpp"


AverageVescNode::AverageVescNode(ros::NodeHandle* nodeHandle) {
	ROS_INFO("Initializing Average Vesc Node");
	nh = *nodeHandle;
	velocitySum = 0;
	initializeSubscribers();
	initializePublishers();
}

void AverageVescNode::initializeSubscribers() {
	ROS_INFO("Initializing Subscribers");
	vescSub = nh.subscribe("/vesc/sensors/core", 10, &AverageVescNode::VescCallback, this);
}

void AverageVescNode::initializePublishers() {
	ROS_INFO("Initializing Publishers");
	velocityPub = nh.advertise<std_msgs::Float64>("average_velocity", 10);
}

void AverageVescNode::VescCallback(const vesc_msgs::VescStateStamped& msg) {
	//Store new velocity in queue
	velocityQueue.push(msg.state.speed);
	velocitySum += msg.state.speed;
	
	//Calculate average value of queue
	while (velocityQueue.size() > QUEUE_SIZE) {
		velocitySum -= velocityQueue.front();
		velocityQueue.pop();
	}
	double averageValue = velocitySum / velocityQueue.size();

	//ROS_INFO average value
	ROS_INFO("Adding velocity of %f makes the new average %f", msg.state.speed, averageValue);

	//Publish average value
	std_msgs::Float64 pubVal;
	pubVal.data = averageValue;
	velocityPub.publish(pubVal);
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "team_a_average_vesc");
	ros::NodeHandle nh;
	AverageVescNode node(&nh);

	ros::Rate rate = ros::Rate(5);
	while (ros::ok()) {
		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
