/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

int main(int argc, char *argv[]) {
  char ip[] = "192.168.1.14";
  UtraApiTcp *utra = new UtraApiTcp(ip);

  int ret = utra->reset_err();
  printf("reset_err   : %d\n", ret);
  ret = utra->set_motion_mode(0);
  printf("set_motion_mode   : %d\n", ret);
  ret = utra->set_motion_enable(8, 1);
  printf("set_motion_enable : %d\n", ret);
  ret = utra->set_motion_status(0);
  printf("set_motion_status : %d\n", ret);

  float joint[6] = {0, 0, 0, 0, 0, 0};
  float speed = 0.1;
  float acc = 3;

  ret = utra->moveto_joint_p2p(joint, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);

  float joint1[6] = {1.248, 1.416, 1.155, -0.252, -1.248, -0.003};
  float joint2[6] = {0.990, 1.363, 1.061, -0.291, -0.990, -0.006};
  float joint3[6] = {1.169, 1.022, 1.070, 0.058, -1.169, -0.004};

  ret = utra->moveto_joint_p2p(joint3, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);
  ret = utra->moveto_joint_p2p(joint1, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);
  ret = utra->moveto_joint_p2p(joint2, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);
  ret = utra->moveto_joint_p2p(joint3, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);

  return 0;
}
