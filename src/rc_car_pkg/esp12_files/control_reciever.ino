#include <ros.h>
#include <geometry_msgs/Twist.h>
 

ros::NodeHandle nh;
 
 
void movementControl(const geometry_msgs::Twist& msg)
{
  
 
}
 
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &movementControl);
 
void setup()
{
  nh.initNode();
  nh.subscribe(sub);
}
 
void loop()
{
  nh.spinOnce();
  delay(10);
}