cmake_minimum_required(VERSION 3.5)
project(arm_controler)

include_directories("../../utapi")

add_executable(demo1_report
	demo1_report.cpp
)
target_link_libraries(demo1_report utapi pthread rt m)


add_executable(demo2_get_param
	demo2_get_param.cpp
)
target_link_libraries(demo2_get_param utapi pthread rt m)


add_executable(demo3_motion_joint_space_p2p
	demo3_motion_joint_space_p2p.cpp
)
target_link_libraries(demo3_motion_joint_space_p2p utapi pthread rt m)
