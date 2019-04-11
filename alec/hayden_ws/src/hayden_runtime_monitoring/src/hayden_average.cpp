#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "hayden_runtime_monitoring/Average.h"

class AverageNode{

	// Public class for simplicity
	public:
		float avg;
		void Callback(const geometry_msgs::Twist::ConstPtr& msg);
		AverageNode();
};

// Initialize avg to 0
AverageNode::AverageNode() : avg(0){}

// Function to calculate sliding window average of turtlesim speed
void AverageNode::Callback(const geometry_msgs::Twist::ConstPtr& msg){

	double average = 0;
	static double window[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	static bool fullWindow = false;
	static int index = 0;
	// Initialize currSpeed with param
	const double currSpeed = msg->linear.x;

	window[index] = currSpeed;

	for(int i = 0; i < 10; i++)
		average += window[i];
	if(fullWindow)
		average /= 10;
	else
		average /= (index + 1);
	index++;
	if(index >= 10){
		fullWindow = true;
		index = 0;
}

	avg = average; // most recent average calculation;
	ROS_INFO("Current Speed: %.2f	Average Speed: %.2f", currSpeed, avg);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "talker");
	//cout<<"Hello World\n";

	// Setup subscription
	ros::NodeHandle s;
	AverageNode node;
	ros::Subscriber listen = s.subscribe("turtle1/cmd_vel", 1000, &AverageNode::Callback, &node);

	// Set up publishing
	ros::NodeHandle p;
	ros::Publisher talk = p.advertise<hayden_runtime_monitoring::Average>("avg_vel", 1000);
	ros::Rate loop(5);

	while(ros::ok()){
		hayden_runtime_monitoring::Average msg;
		msg.avg = node.avg;

		talk.publish(msg);
		ros::spinOnce();
		loop.sleep();
	}


	return 0;
}
