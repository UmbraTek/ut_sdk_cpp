/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utapi/utra/utra_flxie_api.h"

/**
 * This is a demo of controlling a FLXI E on robot.
 * The command to control the FLXI E takes effect immediately whether the robot is moving or not.
 * run command: ./utra/demo22_flxie2_motion_now -i 192.168.1.xxx
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
  UtraFlxiE2Api *fixie = new UtraFlxiE2Api(ubot, 101);

  int ret = fixie->set_motion_mode(1);
  printf("set_motion_mode: %d\n", ret);
  ret = fixie->set_motion_enable(1);
  printf("set_motion_enable: %d\n", ret);

  ret = fixie->set_pos_target(0);
  printf("set_pos_target: %d\n", ret);
  sleep(3);
  ret = fixie->set_pos_target(20);
  printf("set_pos_target: %d\n", ret);

  return 0;
}
