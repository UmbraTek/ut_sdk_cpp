cmake_minimum_required(VERSION 3.5)
project(arm_controler)

include_directories("../../utapi")

add_executable(demo01_report
	demo01_report.cpp
)
target_link_libraries(demo01_report utapi pthread rt m)


add_executable(demo02_get_param
	demo02_get_param.cpp
)
target_link_libraries(demo02_get_param utapi pthread rt m)


add_executable(demo03_motion_joint_space_p2p
	demo03_motion_joint_space_p2p.cpp
)
target_link_libraries(demo03_motion_joint_space_p2p utapi pthread rt m)

add_executable(demo04_motion_tool_space_line
	demo04_motion_tool_space_line.cpp
)
target_link_libraries(demo04_motion_tool_space_line utapi pthread rt m)

add_executable(demo05_motion_tool_space_lineb
	demo05_motion_tool_space_lineb.cpp
)
target_link_libraries(demo05_motion_tool_space_lineb utapi pthread rt m)

add_executable(demo06_motion_tool_space_arc
	demo06_motion_tool_space_arc.cpp
)
target_link_libraries(demo06_motion_tool_space_arc utapi pthread rt m)

add_executable(demo08_motion_servo_joint
	demo08_motion_servo_joint.cpp
)
target_link_libraries(demo08_motion_servo_joint utapi pthread rt m)

add_executable(demo21_flxie2_get_param
	demo21_flxie2_get_param.cpp
)
target_link_libraries(demo21_flxie2_get_param utapi pthread rt m)


add_executable(demo22_flxie2_motion_now
	demo22_flxie2_motion_now.cpp
)
target_link_libraries(demo22_flxie2_motion_now utapi pthread rt m)


add_executable(demo23_flxie2_motion_que
	demo23_flxie2_motion_que.cpp
)
target_link_libraries(demo23_flxie2_motion_que utapi pthread rt m)


add_executable(demo24_flxiv_get_param
	demo24_flxiv_get_param.cpp
)
target_link_libraries(demo24_flxiv_get_param utapi pthread rt m)


add_executable(demo25_flxiv_motion_now
	demo25_flxiv_motion_now.cpp
)
target_link_libraries(demo25_flxiv_motion_now utapi pthread rt m)
