cmake_minimum_required(VERSION 3.5)
project(arm_controler)

include_directories("../../utapi")

add_executable(demo01_report demo01_report.cpp)
target_link_libraries(demo01_report utapi pthread rt m)

add_executable(demo02_get_param demo02_get_param.cpp)
target_link_libraries(demo02_get_param utapi pthread rt m)

add_executable(demo03_motion_p2p demo03_motion_p2p.cpp)
target_link_libraries(demo03_motion_p2p utapi pthread rt m)

add_executable(demo04_motion_linear demo04_motion_linear.cpp)
target_link_libraries(demo04_motion_linear utapi pthread rt m)

add_executable(demo05_motion_linear_blending demo05_motion_linear_blending.cpp)
target_link_libraries(demo05_motion_linear_blending utapi pthread rt m)

add_executable(demo06_motion_circle demo06_motion_circle.cpp)
target_link_libraries(demo06_motion_circle utapi pthread rt m)

add_executable(demo08_motion_servo demo08_motion_servo.cpp)
target_link_libraries(demo08_motion_servo utapi pthread rt m)

add_executable(demo09_motion_p2pb demo09_motion_p2pb.cpp)
target_link_libraries(demo09_motion_p2pb utapi pthread rt m)

add_executable(demo21_flxie2_get_param demo21_flxie2_get_param.cpp)
target_link_libraries(demo21_flxie2_get_param utapi pthread rt m)

add_executable(demo22_flxie2_motion_now demo22_flxie2_motion_now.cpp)
target_link_libraries(demo22_flxie2_motion_now utapi pthread rt m)

add_executable(demo23_flxie2_motion_que demo23_flxie2_motion_que.cpp)
target_link_libraries(demo23_flxie2_motion_que utapi pthread rt m)

add_executable(demo24_flxiv_get_param demo24_flxiv_get_param.cpp)
target_link_libraries(demo24_flxiv_get_param utapi pthread rt m)

add_executable(demo25_flxiv_motion_now demo25_flxiv_motion_now.cpp)
target_link_libraries(demo25_flxiv_motion_now utapi pthread rt m)


add_executable(demo103_debug_code demo103_debug_code.cpp)
target_link_libraries(demo103_debug_code utapi pthread rt m)

add_executable(demo104_debug demo104_debug.cpp)
target_link_libraries(demo104_debug utapi pthread rt m)
