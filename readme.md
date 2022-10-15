
## Overview
Umbratek C++ SDK, applicable products include: UTRA Arm Robot, OPTI Arm Robot, ADRA actuator, FIDO Quadruped Robot, FLXI E-Type Grippers, FLXI V-Type Grippers, DataLink Transceiver Module.

All c/ C ++ apis do not duplicate comments, because the naming and construction are the same as the python api, so please also check the python api comments 

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
	 
[UTRA/OPTI SDK Programming Guide](https://github.com/UmbraTek/ut_sdk_cpp/tree/master/utapi/utra/readme.md)
	
	| Demo                                                         | Describe                                                     |
	| ------------------------------------------------------------ | ------------------------------------------------------------ |
	| [demo01_report.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo01_report.cpp) | This is a demo to print the data of three real-time automatically reported ports. |
	| [demo02_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo02_get_param.cpp) | This is a demo to get ubot parameters, status and other information run command. |
	| [demo03_motion_joint_space_p2p.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo03_motion_joint_space_p2p.cpp) | This is a demo of movement in joint space.                   |
	| [demo04_motion_tool_space_line.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo04_motion_tool_space_line.cpp) | This is a demo of movement in Tool space.                    |
	| [demo05_motion_tool_space_lineb.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo05_motion_tool_space_lineb.cpp) | This is a demo of movement in Tool space with an arc blending transition. |
	| [demo06_motion_tool_space_arc.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo06_motion_tool_space_arc.cpp) | This is a demo of circular motion in tool space.             |
	| [demo08_motion_servo_joint.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo08_motion_servo_joint.cpp) | This is a demo of servo motion in joint space                |
	| [demo21_flxie2_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo21_flxie2_get_param.cpp) | This is a demo to get the parameters, status and other information of FLXI E on the robot. |
	| [demo22_flxie2_motion_now.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo22_flxie2_motion_now.cpp) | This is a demo of controlling a FLXI E on robot. The command to control the FLXI E takes effect immediately whether the robot is moving or not. |
	| [demo23_flxie2_motion_que.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo23_flxie2_motion_que.cpp) | This is a demo of a robot controlling the FLXI E on robot.The command to control FLXI E will wait for the preceding robot motion command to be executed before taking effect. |
	| [demo24_flxiv_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo24_flxiv_get_param.cpp) | This is a demo to get the parameters, status and other information of FLXI V on the robot. |
	| [demo25_flxiv_motion_now.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo25_flxiv_motion_now.cpp) | This is a demo of controlling a FLXI V on robot. The command to control the FLXI V takes effect immediately whether the robot is moving or not. |
	| [demo31_rs485_pass_now.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo31_rs485_pass_now.cpp) | This is a demo of pass-through data to rs485 at the end of the manipulator.The command to pass-through data takes effect immediately whether the robot is moving or not. |
	| [demo32_rs485_pass_que.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/utra/demo32_rs485_pass_que.cpp) | This is a demo of pass-through data to rs485 at the end of the manipulator.The command to pass-through data will wait for the preceding robot motion command to be executed before taking effect. |

* OPTI

  [UTRA/OPTI SDK Programming Guide](https://github.com/UmbraTek/ut_sdk_cpp/tree/master/utapi/utra/readme.md)

  The opti manipulator can refer to the utra demo and api. All the demos and instructions of the opti series and utra series are universal. It only needs to be noted that the target position of the movement needs to be modified according to different models, because the movement range of each model of the manipulator is not the same.


* ADRA

    

    | Demo                                                         | Describe                                                     |
    | ------------------------------------------------------------ | ------------------------------------------------------------ |
    | [demo1_motion_position.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo1_motion_position.cpp) | This demo is to control the device to move to the specified position. |
    | [demo2_motion_velocity.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo2_motion_velocity.cpp) | This demo controls the actuator running at a constant speed in speed mode. |
    | [demo3_motion_torque.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo3_motion_torque.cpp) | This demo controls the actuator running at a constant torque in torque mode. |
    | [demo4_get_param.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo4_get_param.cpp) | This is demo to get the state and parameters of the actuator. |
    | [demo5_motion_cpos.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo5_motion_cpos.cpp) | This is a demo of setting the target positions of 3 actuators simultaneously in broadcast mode (one packet). |
    | [demo6_motion_ctau.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo6_motion_ctau.cpp) | This is a demo of setting the target torque of 3 actuators simultaneously in broadcast mode (one packet). |
    | [demo7_motion_cpostau.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo7_motion_cpostau.cpp) | This is a demo of setting the maximum interval of broadcast read commands and setting the target positions and feedforward torques of 3 actuators simultaneously in broadcast mode (one packet). |
    | [demo8_motion_cposvel.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/adra/demo8_motion_cposvel.cpp) | This is a demo of setting the maximum interval of broadcast read commands and setting the target positions and target speed of 3 actuators simultaneously in broadcast mode (one packet). |

* DataLink

    | Demo                                                         | Describe                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
    | [demo1_datalink_rs485.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/datalink/demo1_datalink_rs485.cpp) | This example tests the EtherNet to RS485 module, sends the received RS485 data back. |
    | [demo2_datalink_can.cpp](https://github.com/UmbraTek/ut_sdk_cpp/blob/master/example/datalink/demo2_datalink_can.cpp) | This example tests the EtherNet to CAN module, sends the received CAN data back. |

##  manual 

 Please see the [wiki](https://umbratek.com/wiki/en/#!index.md)

