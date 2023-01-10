#include <SoftwareSerial.h>
#include<Servo.h>
#include<ros.h>
#include<std_msgs/Int32.h>

//header file of software serial port
SoftwareSerial Serial1(2, 3); //define software serial port name as Serial1 and define pin2 as RX & pin3 as TX

int dist;                     //actual distance measurements of LiDAR
int strength;                 //signal strength of LiDAR
int check;                    //save check value
int i;
int uart[9];                   //save data measured by LiDAR
const int HEADER = 0x59;      //frame header of data package
int angle = 0;
Servo myservo;
float del = 5;
float curr_time, prev_time;
bool flag=0;
ros::NodeHandle nh;

std_msgs::Int32 msg1;
ros::Publisher scan("scan", &msg1);

void setup()
{
  nh.initNode();
  nh.advertise(scan);
  Serial.begin(57600);         //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);
  myservo.attach(9);//set bit rate of serial port connecting LiDAR with Arduino
  prev_time = millis();
}
//rosrun rosserial_python serial_node.py /dev/ttyUSB0

void loop() {
  
  if (Serial1.available())                //check if serial port has data input
  {
    if (Serial1.read() == HEADER)        //assess data package frame header 0x59
    {
      uart[0] = HEADER;
      if (Serial1.read() == HEADER)      //assess data package frame header 0x59
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)         //save data in array
        {
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))        //verify the received data as per protocol
        {
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
          msg1.data = dist;
          scan.publish(&msg1);
          Serial.print("dist = ");
          Serial.print(dist);                 //output measure distance value of LiDAR
          Serial.print('\t');         Serial.print("strength = ");
          Serial.print(strength);             //output signal strength value
          Serial.print('\t');
          Serial.print("Angle = ");
          Serial.print(angle);
          Serial.print('\n');
          
        }
      }
    }
  }

  
  if (millis() - prev_time >= del) {
    
  
  prev_time = millis();
  if (flag==0 && angle<=180){
    myservo.write(angle++);
  }
  if(angle>180){
    flag=1;
  }
  if(flag==1 && angle>=0){
    myservo.write(angle--);
  }
  if(angle<=0){
    flag=0;
  }

  }
  nh.spinOnce();
  }
