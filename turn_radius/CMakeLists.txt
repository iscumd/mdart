cmake_minimum_required(VERSION 2.8.3)
project(turn_radius)

find_package(catkin REQUIRED COMPONENTS
  joy
  roscpp
  sensor_msgs
  message_generation
  std_msgs
)


add_message_files(
  FILES
  turn.msg
)

generate_messages(
  DEPENDENCIES
  sensor_msgs
  std_msgs
)

catkin_package(
CATKIN_DEPENDS 
	joy 
	roscpp 
	sensor_msgs 
	message_runtime 
	std_msgs
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(turn_radius src/turn_radius.cpp)
add_dependencies(turn_radius ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(turn_radius ${catkin_LIBRARIES})

