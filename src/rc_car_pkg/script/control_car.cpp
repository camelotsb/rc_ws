#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "control_car");
    ros::NodeHandle node_obj;
    ros::Publisher control_car_publisher = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Rate loop_rate(10);
    geometry_msgs::Twist msg;
    // msg.linear.x=0;
    while (ros::ok())
    {
        msg.linear.x = 1;
        ROS_INFO("Publishing\n");
        control_car_publisher.publish(msg);
        loop_rate.sleep();
    }
    return 0;
}