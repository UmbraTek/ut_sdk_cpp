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

add_executable(demo3_motion_torque
	demo3_motion_torque.cpp
)
target_link_libraries(demo3_motion_torque utapi pthread rt m)

add_executable(demo4_get_param
	demo4_get_param.cpp
)
target_link_libraries(demo4_get_param utapi pthread rt m)

add_executable(demo5_motion_cpos
	demo5_motion_cpos.cpp
)
target_link_libraries(demo5_motion_cpos utapi pthread rt m)

add_executable(demo6_motion_ctau
	demo6_motion_ctau.cpp
)
target_link_libraries(demo6_motion_ctau utapi pthread rt m)

add_executable(demo7_motion_cpostau
	demo7_motion_cpostau.cpp
)
target_link_libraries(demo7_motion_cpostau utapi pthread rt m)

add_executable(demo8_motion_cposvel
	demo8_motion_cposvel.cpp
)
target_link_libraries(demo8_motion_cposvel utapi pthread rt m)

add_executable(demo9_motion_cpvt
	demo9_motion_cpvt.cpp
)
target_link_libraries(demo9_motion_cpvt utapi pthread rt m)

add_executable(demo11_cal_test
	demo11_cal_test.cpp
)
target_link_libraries(demo11_cal_test utapi pthread rt m)
