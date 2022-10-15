/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

/**
 * This is a demo of movement in Tool space.
 * run command: ./utra/demo04_motion_linear -i 192.168.1.xxx
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
  ret = ubot->moveto_home_p2p(speed, acc, 0);
  printf("moveto_home_p2p  : %d\n", ret);

  float joint[6] = {0 / 57.296, -30 / 57.296, 50 / 57.296, -10 / 57.296, 90 / 57.296, 0 / 57.296};
  ret = ubot->moveto_joint_p2p(joint, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);

  speed = 120.0;
  acc = 100.0;
  float pos1[6] = {418, 56, 186, 3.14, 0.0, 1.5};
  float pos2[6] = {418, -256, 186, 3.14, 0.0, 1.5};
  float pos3[6] = {418, -256, 486, 3.14, 0.0, 1.5};
  ret = ubot->moveto_cartesian_line(pos1, speed, acc, 0);
  printf("moveto_cartesian_line   :%d\n", (ret));
  ret = ubot->moveto_cartesian_line(pos2, speed, acc, 0);
  printf("moveto_cartesian_line   :%d\n", ret);
  ret = ubot->moveto_cartesian_line(pos3, speed, acc, 0);
  printf("moveto_cartesian_line   :%d\n", ret);

  float joint1[6] = {170.5 / 57.296, 3.5 / 57.296, -125.6 / 57.296, -39.1 / 57.296, -90 / 57.296, -9.5 / 57.296};
  float joint2[6] = {133.8 / 57.296, 13.1 / 57.296, -114.3 / 57.296, -37.3 / 57.296, -90 / 57.296, -46.2 / 57.296};
  float joint3[6] = {133.8 / 57.296, 3 / 57.296, -75.9 / 57.296, 11.1 / 57.296, -90 / 57.296, -46.2 / 57.296};
  ret = ubot->moveto_joint_line(joint1, speed, acc, 0);
  printf("moveto_joint_line   :%d\n", (ret));
  ret = ubot->moveto_joint_line(joint2, speed, acc, 0);
  printf("moveto_joint_line   :%d\n", (ret));
  ret = ubot->moveto_joint_line(joint3, speed, acc, 0);
  printf("moveto_joint_line   :%d\n", (ret));

  return 0;
}
