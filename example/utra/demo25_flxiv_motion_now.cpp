/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utapi/utra/utra_flxiv_api.h"

int main(int argc, char *argv[]) {
  char ip[] = "192.168.1.34";
  UtraApiTcp *ubot = new UtraApiTcp(ip);
  UtraFlxiVApi *fixiv = new UtraFlxiVApi(ubot, 102);

  int ret = fixiv->set_motion_mode(1);
  printf("set_motion_mode: %d\n", ret);
  ret = fixiv->set_motion_enable(1);
  printf("set_motion_enable: %d\n", ret);

  sleep(3);

  ret = fixiv->set_motion_enable(0);
  printf("set_motion_enable: %d\n", ret);
  ret = fixiv->set_motion_mode(0);
  printf("set_motion_mode: %d\n", ret);

  return 0;
}
