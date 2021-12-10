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

  float pos1[6] = {-0.0, -360.0, 800.0, 1.58, 0.0, 0.0};
  float pos2[6] = {-8.0, -560.0, 600.0, 1.58, 0.0, 0.0};
  float pos3[6] = {-180.0, -560.0, 600.0, 1.58, 0.0, 0.0};
  speed = 50.0;
  acc = 100.0;

  ret = utra->plan_sleep(5);
  printf("move_sleep    :%d\n", (ret));
  ret = utra->moveto_cartesian_lineb(pos1, speed, acc, 5, 0);
  printf("moveto_cartesian_lineb   :%d\n", (ret));
  ret = utra->moveto_cartesian_lineb(pos2, speed, acc, 5, 50);
  printf("moveto_cartesian_lineb   :%d\n", ret);
  ret = utra->moveto_cartesian_lineb(pos3, speed, acc, 5, 100);
  printf("moveto_cartesian_lineb   :%d\n", ret);
  ret = utra->moveto_cartesian_lineb(pos1, speed, acc, 5, 125);
  printf("moveto_cartesian_lineb   :%d\n", ret);

  return 0;
}
