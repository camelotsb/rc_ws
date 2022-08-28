#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

// Create a callback function to be called when a message is received on the subscribed topic
void number_callback(const std_msgs::Int32::ConstPtr &msg)
{
    // Print data as proof we have received the data wirelessly
    if (msg->data == 1)
        ROS_INFO("%d\n", msg->data);
    else
        ROS_INFO("00\n");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "receiver");
    ros::NodeHandle node1_obj;

    // Create a dummy receiver object
    ros::Subscriber dummy_receiver = node1_obj.subscribe("/sample_signal", 200, number_callback);
    ros::spin();
    return 0;
}