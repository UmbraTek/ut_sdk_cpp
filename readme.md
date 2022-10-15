
## Overview
Umbratek C++ SDK, applicable products include: UTRA Arm Robot, OPTI Arm Robot, ADRA actuator, FIDO Quadruped Robot, FLXI E-Type Grippers, FLXI V-Type Grippers, DataLink Transceiver Module.

##  **Notes** 

*  The code test environment is ubuntu18.04, ubuntu20.04, ubuntu22.04.
*  Please follow the manual and pay attention to safety.

## Build

>  download

```
$ git clone https://github.com/UmbraTek/ut_sdk_cpp.git
```

>  build

```
$ cd ut_sdk_cpp/example
$ mkdir build
$ cmake ..
$ make -j4
```

## Example

* UTRA
	 [demo01_report.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo01_report.cpp) 

	 [demo02_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo02_get_param.cpp) 
	
	 [demo03_motion_joint_space_p2p.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo03_motion_joint_space_p2p.cpp) 
	
	 [demo04_motion_tool_space_line.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo04_motion_tool_space_line.cpp) 
	
	 [demo05_motion_tool_space_lineb.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo05_motion_tool_space_lineb.cpp) 
	
	 [demo06_motion_tool_space_arc.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo06_motion_tool_space_arc.cpp) 
	
	 [demo08_motion_servo_joint.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo08_motion_servo_joint.cpp) 
	
	 [demo21_flxie2_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo21_flxie2_get_param.cpp) 
	
	 [demo22_flxie2_motion_now.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo22_flxie2_motion_now.cpp) 
	
	 [demo23_flxie2_motion_que.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo23_flxie2_motion_que.cpp) 
	
	 [demo24_flxiv_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo24_flxiv_get_param.cpp) 
	
	 [demo25_flxiv_motion_now.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo25_flxiv_motion_now.cpp) 
	
	 [demo31_rs485_pass_now.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo31_rs485_pass_now.cpp) 
	
	 [demo32_rs485_pass_que.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo32_rs485_pass_que.cpp) 
	
* ADRA

    [demo1_motion_position.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo1_motion_position.cpp) 

    [demo2_motion_velocity.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo2_motion_velocity.cpp) 

    [demo3_motion_torque.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo3_motion_torque.cpp) 

    [demo4_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo4_get_param.cpp) 

    [demo5_motion_cpos.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo5_motion_cpos.cpp) 

    [demo6_motion_ctau.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo6_motion_ctau.cpp) 

    [demo7_motion_cpostau.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo7_motion_cpostau.cpp) 

* DataLink

    [demo1_datalink_rs485.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/datalink/demo1_datalink_rs485.cpp) 

    [demo2_datalink_can.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/datalink/demo2_datalink_can.cpp) 

##  manual 

 Please see the [wiki](https://umbratek.com/wiki/en/#!index.md)

