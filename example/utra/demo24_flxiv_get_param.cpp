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

  char uuid[24], version[24];
  int ret = fixiv->get_uuid(uuid);
  printf("get_uuid: %d, uuid = %s\n", ret, uuid);
  ret = fixiv->get_sw_version(version);
  printf("get_sw_version: %d, version = %s\n", ret, version);
  ret = fixiv->get_hw_version(version);
  printf("get_hw_version: %d, version = %s\n", ret, version);
  printf(" ");

  int min, max;
  float value_fp32;
  ret = fixiv->get_temp_limit(&min, &max);
  printf("get_temp_limit: %d, value = %d %d\n", ret, min, max);
  ret = fixiv->get_volt_limit(&min, &max);
  printf("get_volt_limit: %d, value = %d %d\n", ret, min, max);
  printf(" ");

  uint8_t value_u8;
  ret = fixiv->get_motion_mode(&value_u8);
  printf("get_motion_mode  : %d, value = %d\n", ret, value_u8);
  ret = fixiv->get_motion_enable(&value_u8);
  printf("get_motion_enable: %d, value = %d\n", ret, value_u8);
  ret = fixiv->get_temp_driver(&value_fp32);
  printf("get_temp_driver  : %d, value = %.1f\n", ret, value_fp32);
  ret = fixiv->get_temp_motor(&value_fp32);
  printf("get_temp_motor   : %d, value = %.1f\n", ret, value_fp32);
  ret = fixiv->get_bus_volt(&value_fp32);
  printf("get_bus_volt     : %d, value = %.1f\n", ret, value_fp32);
  ret = fixiv->get_error_code(&value_u8);
  printf("get_error_code   : %d, value = %d\n", ret, value_u8);
  printf(" ");

  float value_fp32s[4];
  ret = fixiv->get_senser(value_fp32s);
  printf("get_senser   : %d, value = %f %f %f %f\n", ret, value_fp32s[0], value_fp32s[1], value_fp32s[2], value_fp32s[3]);
  printf(" ");

  return 0;
}
