#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv)
{
	/** 
	 * ros::init() uses argc and argv
	 * third argument is name of node 
	 */
	ros::init(argc, argv, "talker");

	//This will initialize the node and allow communications
	ros::NodeHandle n;

	//This will tell the master node what topic to publish on
	//advertise returns an object that be published to with publish()
	//1000 is size of message buffer
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

	ros::Rate loop_rate(10);
	int count = 0;
	while(ros::ok())
	{
		//message object to publish
		std_msgs::String msg;

		//construct data
		std::stringstream ss;
		ss << "hello world " << count;

		//set the data member of the message object to our string
		msg.data = ss.str();
		
		ROS_INFO("%s", msg.data.c_str());
		
		//Pass the std_msgs::String object to the Publisher object with a publish call
		chatter_pub.publish(msg);
		ros::spinOnce();

		//sleep until loop rate says timer is done
		loop_rate.sleep();
		++count;
	}
	return 0;
}


