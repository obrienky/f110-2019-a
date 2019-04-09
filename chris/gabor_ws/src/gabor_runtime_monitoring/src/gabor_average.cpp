#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "gabor_runtime_monitoring/Average.h"

class AverageState
{
	public:
		float average;
		void commandCallback(const geometry_msgs::Twist::ConstPtr& msg);
		AverageState();
};

AverageState::AverageState() : average(0)
{
}

void AverageState::commandCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	static int index = 0;
	static bool window_full = false;
	static double window[10] = {0,0,0,0,0,0,0,0,0,0};

	const double current_x_speed = msg->linear.x;

	window[index] = current_x_speed;

	double avg = 0;
	for(int i = 0; i<10; i++)
		avg += window[i];
	if(window_full)
		avg /= 10;
	else
		avg /= (index + 1);

	index++;
	if(index >= 10)
	{
		window_full = true;
		index = 0;
	}

	average = avg;
	ROS_INFO("New command speed recieved: %.2f | New average: %.2f", current_x_speed, average);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "turtle_listener");
	ros::NodeHandle n;
	AverageState avgState;

	ros::Subscriber sub = n.subscribe("turtle1/cmd_vel", 1000, &AverageState::commandCallback, &avgState);

	ros::NodeHandle p;
	ros::Publisher pub = p.advertise<gabor_runtime_monitoring::Average>("average_velocity", 1000);
	ros::Rate loop_rate(5);
	while(ros::ok())
	{
		gabor_runtime_monitoring::Average msg;
		msg.average = avgState.average;

		pub.publish(msg);

		ros::spinOnce();
		loop_rate.sleep();
	}


	return 0;
}
