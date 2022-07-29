/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

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

  speed = 30 / 57.296;
  acc = 3;
  float joint1[6] = {20 / 57.296, -30 / 57.296, 50 / 57.296, -10 / 57.296, 90 / 57.296, 40 / 57.296};
  float joint2[6] = {20 / 57.296, -10 / 57.296, 100 / 57.296, 20 / 57.296, 90 / 57.296, -20 / 57.296};
  float joint3[6] = {-20 / 57.296, -10 / 57.296, 100 / 57.296, 20 / 57.296, 90 / 57.296, -20 / 57.296};
  ret = ubot->moveto_joint_p2p(joint3, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);
  ret = ubot->moveto_joint_p2p(joint1, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);
  ret = ubot->moveto_joint_p2p(joint2, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);
  ret = ubot->moveto_joint_p2p(joint3, speed, acc, 0);
  printf("moveto_joint_p2p  : %d\n", ret);

  speed = 30 / 57.296;
  acc = 3;
  float pos1[6] = {653, 105, 427, 180 / 57.296, 0.0, 70 / 57.296};
  float pos2[6] = {518, 56, 486, 180 / 57.296, 0.0, 130 / 57.296};
  float pos3[6] = {433, -290, 486, 180 / 57.296, 0.0, 90 / 57.296};
  ret = ubot->moveto_cartesian_p2p(pos3, speed, acc, 0);
  printf("moveto_cartesian_p2p  : %d\n", ret);
  ret = ubot->moveto_cartesian_p2p(pos1, speed, acc, 0);
  printf("moveto_cartesian_p2p  : %d\n", ret);
  ret = ubot->moveto_cartesian_p2p(pos2, speed, acc, 0);
  printf("moveto_cartesian_p2p  : %d\n", ret);
  ret = ubot->moveto_cartesian_p2p(pos3, speed, acc, 0);
  printf("moveto_cartesian_p2p  : %d\n", ret);

  return 0;
}
