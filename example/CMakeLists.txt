cmake_minimum_required(VERSION 3.5)
project(arm_controler)

include_directories("./")
include_directories("../")
include_directories("../utapi")

add_subdirectory(../utapi utapi)
add_subdirectory(./adra)
add_subdirectory(./utra)
add_subdirectory(./datalink)
