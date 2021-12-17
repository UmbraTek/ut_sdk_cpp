/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

int main(int argc, char *argv[]) {
  char ip[] = "192.168.1.175";
  UtraApiTcp *ubot = new UtraApiTcp(ip);

  int ret = ubot->reset_err();
  printf("reset_err   : %d\n", ret);
  ret = ubot->set_motion_mode(0);
  printf("set_motion_mode   : %d\n", ret);
  ret = ubot->set_motion_enable(8, 1);
  printf("set_motion_enable : %d\n", ret);
  ret = ubot->set_motion_status(0);
  printf("set_motion_status : %d\n", ret);

  float joint[6] = {0, 0, 0, 0, 0, 0};
  float speed = 0.1;
  float acc = 3;

  ret = ubot->moveto_joint_p2p(joint, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);

  int count = 6;
  float joint1[6] = {1.248, 1.416, 1.155, -0.252, -1.248, -0.003};
  float joint2[6] = {0.990, 1.363, 1.061, -0.291, -0.990, -0.006};
  float joint3[6] = {1.169, 1.022, 1.070, 0.058, -1.169, -0.004};
  float joint4[6] = {1.248, 1.416, 1.155, -0.252, -1.248, -0.003};
  float joint5[6] = {0.990, 1.363, 1.061, -0.291, -0.990, -0.006};
  float joint6[6] = {1.169, 1.022, 1.070, 0.058, -1.169, -0.004};
  float time[count] = {2, 2, 2, 2, 2, 2};

  float frames[count * 6] = {0};
  memcpy(&frames[0], joint1, sizeof(joint1));
  memcpy(&frames[6], joint2, sizeof(joint2));
  memcpy(&frames[12], joint3, sizeof(joint3));
  memcpy(&frames[18], joint4, sizeof(joint4));
  memcpy(&frames[24], joint5, sizeof(joint5));
  memcpy(&frames[30], joint6, sizeof(joint6));

  ret = ubot->moveto_servo_joint(3, frames, time);
  printf("moveto_servo_joint  : %d\n", ret);

  return 0;
}
