/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utapi/utra/utra_flxie_api.h"

int main(int argc, char *argv[]) {
  char ip[] = "192.168.1.14";
  UtraApiTcp *utra = new UtraApiTcp(ip);
  UtraFlxiE2Api *fixi = new UtraFlxiE2Api(utra, 101);

  int ret = fixi->set_motion_mode(1);
  printf("set_motion_mode: %d\n", ret);
  ret = fixi->set_motion_enable(1);
  printf("set_motion_enable: %d\n", ret);

  ret = fixi->set_pos_target(0);
  printf("set_pos_target: %d\n", ret);
  sleep(3);
  ret = fixi->set_pos_target(20);
  printf("set_pos_target: %d\n", ret);

  return 0;
}
