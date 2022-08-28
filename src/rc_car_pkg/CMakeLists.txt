cmake_minimum_required(VERSION 3.0.2)
project(rc_car_pkg)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  rviz
  tf
  urdf
  xacro
  gazebo_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rc_car_pkg
#  CATKIN_DEPENDS geometry_msgs roscpp rospy rviz tf urdf xacro
#  DEPENDS system_lib
)


file(GLOB_RECURSE sources scripts/*.py)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(control_car script/control_car.cpp)
target_link_libraries(control_car ${catkin_LIBRARIES})

add_executable(receiver script/dummy_sub.cpp)
target_link_libraries(receiver ${catkin_LIBRARIES})