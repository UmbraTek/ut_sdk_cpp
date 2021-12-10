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

  char uuid[24], version[24];
  int ret = fixi->get_uuid(uuid);
  printf("get_uuid: %d, uuid = %s\n", ret, uuid);
  ret = fixi->get_sw_version(version);
  printf("get_sw_version: %d, version = %s\n", ret, version);
  ret = fixi->get_hw_version(version);
  printf("get_hw_version: %d, version = %s\n", ret, version);
  printf(" ");

  int min, max;
  float value_fp32;
  ret = fixi->get_temp_limit(&min, &max);
  printf("get_temp_limit: %d, value = %d %d\n", ret, min, max);
  ret = fixi->get_volt_limit(&min, &max);
  printf("get_volt_limit: %d, value = %d %d\n", ret, min, max);
  ret = fixi->get_curr_limit(&value_fp32);
  printf("get_curr_limit: %d, value = %f\n", ret, value_fp32);
  printf(" ");

  uint8_t value_u8;
  ret = fixi->get_motion_mode(&value_u8);
  printf("get_motion_mode  : %d, value = %d\n", ret, value_u8);
  ret = fixi->get_motion_enable(&value_u8);
  printf("get_motion_enable: %d, value = %d\n", ret, value_u8);
  ret = fixi->get_temp_driver(&value_fp32);
  printf("get_temp_driver  : %d, value = %.1f\n", ret, value_fp32);
  ret = fixi->get_temp_motor(&value_fp32);
  printf("get_temp_motor   : %d, value = %.1f\n", ret, value_fp32);
  ret = fixi->get_bus_volt(&value_fp32);
  printf("get_bus_volt     : %d, value = %.1f\n", ret, value_fp32);
  ret = fixi->get_bus_curr(&value_fp32);
  printf("get_bus_curr     : %d, value = %.1f\n", ret, value_fp32);
  ret = fixi->get_error_code(&value_u8);
  printf("get_error_code   : %d, value = %d\n", ret, value_u8);
  printf(" ");

  ret = fixi->get_vel_limit_min(&value_fp32);
  printf("get_vel_limit_min : %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_vel_limit_max(&value_fp32);
  printf("get_vel_limit_max : %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_tau_limit_min(&value_fp32);
  printf("get_tau_limit_min : %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_tau_limit_max(&value_fp32);
  printf("get_tau_limit_max : %d, value = %f\n", ret, value_fp32);
  printf(" ");

  ret = fixi->get_pos_target(&value_fp32);
  printf("get_pos_target : %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_pos_current(&value_fp32);
  printf("get_pos_current: %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_vel_current(&value_fp32);
  printf("get_vel_current: %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_tau_target(&value_fp32);
  printf("get_tau_target : %d, value = %f\n", ret, value_fp32);
  ret = fixi->get_tau_current(&value_fp32);
  printf("get_tau_current: %d, value = %f\n", ret, value_fp32);

  float fp_list[2];
  ret = fixi->get_pos_pidp(&value_fp32);
  printf("get_pos_pid    : %d, pid_p = %f\n", ret, value_fp32);
  ret = fixi->get_vel_pidp(&fp_list[0]);
  ret = fixi->get_vel_pidi(&fp_list[1]);
  printf("get_vel_pid    : %d, pid_p = %f, pid_p = %f\n", ret, fp_list[0], fp_list[1]);
  ret = fixi->get_tau_pidp(&fp_list[0]);
  ret = fixi->get_tau_pidi(&fp_list[1]);
  printf("get_tau_pid    : %d, pid_p = %f, pid_p = %f\n\n", ret, fp_list[0], fp_list[1]);

  ret = fixi->get_pos_smooth_cyc(&value_u8);
  printf("get_pos_smooth_cyc: %d, value = %d\n", ret, value_u8);
  ret = fixi->get_vel_smooth_cyc(&value_u8);
  printf("get_vel_smooth_cyc: %d, value = %d\n", ret, value_u8);
  ret = fixi->get_tau_smooth_cyc(&value_u8);
  printf("get_tau_smooth_cyc: %d, value = %d\n", ret, value_u8);

  return 0;
}
