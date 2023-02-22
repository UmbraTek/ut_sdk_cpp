/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

/**
 * This is a demo of movement in joint space.
 * run command: ./utra/demo09_motion_p2pb -i 192.168.1.xxx
 */
int main(int argc, char *argv[]) {
  int opt = 0;
  char ip[64];
  std::string port_name = "192.168.1.14";
  while ((opt = getopt(argc, argv, "i:m:")) != -1) {
    switch (opt) {
      case 'i':
        strcpy(ip, std::string(optarg).data());
        break;
    }
  }

  UtraApiTcp *ubot = new UtraApiTcp(ip);

  int ret = ubot->reset_err();
  printf("reset_err   : %d\n", ret);
  ret = ubot->set_motion_mode(0);
  printf("set_motion_mode   : %d\n", ret);
  ret = ubot->set_motion_enable(8, 1);
  printf("set_motion_enable : %d\n", ret);
  ret = ubot->set_motion_status(0);
  printf("set_motion_status : %d\n", ret);

  float speed = 30 / 57.296;
  float acc = 3;
  float joint[6] = {0, 0, 0, 0, 0, 0};
  ret = ubot->moveto_joint_p2p(joint, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);

  speed = 10 / 57.296;
  acc = 3;
  float joint1[6] = {20 / 57.296, -30 / 57.296, 50 / 57.296, -10 / 57.296, 90 / 57.296, 40 / 57.296};
  float joint2[6] = {20 / 57.296, -10 / 57.296, 100 / 57.296, 20 / 57.296, 90 / 57.296, -20 / 57.296};
  float joint3[6] = {-20 / 57.296, -10 / 57.296, 100 / 57.296, 20 / 57.296, 90 / 57.296, -20 / 57.296};
  ret = ubot->plan_sleep(5);
  printf("plan_sleep   :%d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint3, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint1, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint2, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint3, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint1, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint2, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);
  ret = ubot->moveto_joint_p2pb(joint3, speed, acc, 0, 0);
  printf("moveto_joint_p2pb  : %d\n", ret);

  return 0;
}
