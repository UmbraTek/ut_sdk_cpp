cmake_minimum_required(VERSION 3.5)
project(arm_controler)

include_directories("../../utapi")

add_executable(demo1_motion_position
	demo1_motion_position.cpp
)
target_link_libraries(demo1_motion_position utapi pthread rt m)

add_executable(demo2_motion_velocity
	demo2_motion_velocity.cpp
)
target_link_libraries(demo2_motion_velocity utapi pthread rt m)

add_executable(demo3_motion_current
	demo3_motion_current.cpp
)
target_link_libraries(demo3_motion_current utapi pthread rt m)

add_executable(demo4_get_param
	demo4_get_param.cpp
)
target_link_libraries(demo4_get_param utapi pthread rt m)
