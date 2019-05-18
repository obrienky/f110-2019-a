#include "rosdogs_find_gap.hpp"
#include <math.h>

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
    float cone_ang = M_PI_2;        //one sided angle of scans considered
    int scan_num = 5;               //number of passes for search

    //finds the starting and ending indicies to scan from -90 deg to +90 deg
    int num_scans = (msg.angle_max - msg.angle_min)/msg.angle_increment; //num of scans in msg
    float pi_ratio = (msg.angle_max - msg.angle_min)/M_PI_2;             //ratio of scans in 90 deg
    int start = num_scans*(.5 - pi_ratio);
    int end = num_scans*(.5 + pi_ratio);     //start and end indicies
    
    float size_max = 0;                                     //the max gap arc length
    float radius_max = 0;                                   //radius of max gap
    int gap_start = 0;
    for(int i=0; i<=num_scans; i++){                         //loop over number of scan checks
        float radius = (float)(i/num_scans)*(msg.range_max - msg.range_min);     //radius of current check
        int gap_size = 0;                                   //init gap_size for this radius
        for(int j=start; j<=end; j++){                      //step through laserscans
            if(msg.ranges[j] >= radius) {gap_size++;}        //if scan over gap size, inc
            else{                                           //if scan less than gap
                if((float)gap_size*radius >= size_max){     //if arclength is greater than max
                    size_max = (float)gap_size*radius;      //save max arclength
                    radius_max = radius;                     //save radius of max
                    gap_start = j;
                }//if
                gap_size = 0;                               //reset gap size
            }//else
        }//for(j) 
    }//for(i)
    
    int offset = (int)size_max/(radius_max/2) + gap_start;      //centered index of gap
    float offset_angle = msg.angle_min + offset*msg.angle_increment;
    geometry_msgs::Vector3 center = geometry_msgs::Vector3();
    center.x = radius_max*cos(offset_angle);
    center.y = radius_max*sin(offset_angle);
    center.z = 0;
    
    centerPub.publish(center);

}//lidar callback

int main(int argc, char** argv) {
	ros::init(argc, argv, "find_gap");
	ros::NodeHandle nh;
	FindGapNode node(&nh);

	ros::spin();

	return 0;
}

RadialGap::RadialGap(float start, float end, float r){
    th_start = start;
    th_end = end;
    radius = r;
    float th_cent = th_end - th_start;
    float x = r*cos(th_cent);
    float y = r*cos(th_cent);
    center.x = x;
    center.y = y;
    center.z = 0;
};

RadialGap::~RadialGap(){}
