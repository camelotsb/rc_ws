#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ros.h>
#include <std_msgs/Int32.h>
// #include <std_msgs/String.h>

#define DEBUG 1
int ENB = D7;
int IN3 = D1;
int IN4 = D2;
int ENA = D8;
int IN1 = D3;
int IN2 = D4;
// rosrun rosserial_python serial_node.py tcp
// Set credentials to connect to the Wifi network
// Change if required
const char *ssid = "sundar";
const char *password = "Yellove4";

// const char *ssid = "sibi";
// const char *password = "12345678";

IPAddress server(192, 168, 137, 230); // Set the rosserial socket ROSCORE SERVER IP address

const uint16_t serverPort = 11411; // Set the rosserial socket server port

// connect to ROS server as as a client
void setupWiFi()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void cmd_velCallback( const std_msgs::Int32& msg){
  if (msg.data == 1){
  analogWrite(ENB, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
  else if (msg.data == -1){
  analogWrite(ENB, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }
  else if (msg.data == 0){
  analogWrite(ENB, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  }
}

void dir_selectionCallback(const std_msgs::Int32& msg1){
  if (msg1.data== 4){
    analogWrite(ENA, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (msg1.data == 6){
    analogWrite(ENA, 255);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else if (msg1.data == 5){ 
    analogWrite(ENA, 255);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}

ros::NodeHandle nh;
std_msgs::Int32 msg;
std_msgs::Int32 msg1;

ros::Subscriber<std_msgs::Int32> Sub("/cmd_vel", &cmd_velCallback );

ros::Subscriber<std_msgs::Int32> Sub1("/dir_selection", &dir_selectionCallback);

void setup()
{
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  if (DEBUG)
    Serial.begin(115200);
  setupWiFi();
  delay(2000);

  // ROS object constructors
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.subscribe(Sub);
  nh.subscribe(Sub1);
}

void loop()
{
  if (nh.connected())
  {
    Serial.println("Connected");
  }
  nh.spinOnce();
  delay(200);
}