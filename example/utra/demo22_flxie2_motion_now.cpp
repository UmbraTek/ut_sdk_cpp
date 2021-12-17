/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utapi/utra/utra_flxie_api.h"

int main(int argc, char *argv[]) {
  char ip[] = "192.168.1.34";
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
