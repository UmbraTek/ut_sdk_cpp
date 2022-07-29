/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utapi/utra/utra_flxie_api.h"

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
  sleep(3);

  int ret = ubot->reset_err();
  printf("reset_err   : %d\n", ret);
  ret = ubot->set_motion_mode(0);
  printf("set_motion_mode   : %d\n", ret);
  ret = ubot->set_motion_enable(8, 1);
  printf("set_motion_enable : %d\n", ret);
  ret = ubot->set_motion_status(0);
  printf("set_motion_status : %d\n", ret);

  ret = ubot->move_sleep(1);
  printf("move_sleep : %d\n", ret);
  ret = fixie->set_motion_mode(1, false);
  printf("set_motion_mode: %d\n", ret);
  ret = fixie->set_motion_enable(1, false);
  printf("set_motion_enable: %d\n", ret);

  ret = fixie->set_pos_target(0, false);
  printf("set_pos_target: %d\n", ret);
  ret = ubot->move_sleep(5);
  printf("move_sleep :%d\n", ret);

  ret = fixie->set_pos_target(20, false);
  printf("set_pos_target: %d\n", ret);
  ret = ubot->move_sleep(10);
  printf("move_sleep :%d\n", ret);

  ret = fixie->set_pos_target(0, false);
  printf("set_pos_target: %d\n", ret);

  return 0;
}
