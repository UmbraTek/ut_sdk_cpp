cmake_minimum_required(VERSION 3.5)
project(demo_datalink)

include_directories("../../utapi")

add_executable(demo1_datalink_rs485
	demo1_datalink_rs485.cpp
)
target_link_libraries(demo1_datalink_rs485 utapi pthread)


add_executable(demo2_datalink_can
	demo2_datalink_can.cpp
)
target_link_libraries(demo2_datalink_can utapi pthread)
