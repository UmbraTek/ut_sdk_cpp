/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

/**
 * This is a demo of servo motion in joint space
 * run command: ./utra/demo08_motion_servo -i 192.168.1.xxx
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

  int count = 3;
  float joint1[6] = {20 / 57.296, -30 / 57.296, 50 / 57.296, -10 / 57.296, 90 / 57.296, 40 / 57.296};
  float joint2[6] = {20 / 57.296, -10 / 57.296, 100 / 57.296, 20 / 57.296, 90 / 57.296, -20 / 57.296};
  float joint3[6] = {-20 / 57.296, -10 / 57.296, 100 / 57.296, 20 / 57.296, 90 / 57.296, -20 / 57.296};
  float time[count] = {20, 20, 20};

  float frames[count * 6] = {0};
  memcpy(&frames[0], joint1, sizeof(joint1));
  memcpy(&frames[6], joint2, sizeof(joint2));
  memcpy(&frames[12], joint3, sizeof(joint3));

  ret = ubot->moveto_servo_joint(3, frames, time);
  printf("moveto_servo_joint  : %d\n", ret);

  float pos1[6] = {418, 56, 186, 3.14, 0.0, 1.5};
  float pos2[6] = {418, -256, 186, 3.14, 0.0, 1.5};
  float pos3[6] = {418, -256, 486, 3.14, 0.0, 1.5};
  float time2[3] = {20, 20, 20};
  float pose[18];
  for (int j = 0; j < 6; j++) pose[0 + j] = pos1[j];
  for (int j = 0; j < 6; j++) pose[6 + j] = pos2[j];
  for (int j = 0; j < 6; j++) pose[12 + j] = pos3[j];

  ret = ubot->plan_sleep(5);
  ret = ubot->moveto_cartesian_servo(3, pose, time2);
  printf("moveto_cartesian_servo  : %d\n", ret);
  ret = ubot->moveto_cartesian_servo(3, pose, time2);
  printf("moveto_cartesian_servo  : %d\n", ret);
  ret = ubot->moveto_cartesian_servo(3, pose, time2);
  printf("moveto_cartesian_servo  : %d\n", ret);

  return 0;
}
