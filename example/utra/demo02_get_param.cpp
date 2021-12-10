/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "common/print.h"
#include "utapi/utra/utra_api_tcp.h"

int main(int argc, char *argv[]) {
  char ip[] = "192.168.1.175";

  UtraApiTcp *ubot = new UtraApiTcp(ip);

  uint8_t axis = 0;
  uint8_t uuid[18] = {0};
  uint8_t version[21] = {0};
  uint8_t value_u8[24];
  int value_int;
  float value_fp[12];

  int ret = ubot->get_uuid(uuid);
  printf("get_uuid       : %d, uuid    = %s\n", ret, uuid);
  ret = ubot->get_sw_version(version);
  printf("get_sw_version : %d, version = %s\n", ret, version);
  ret = ubot->get_hw_version(version);
  printf("get_hw_version : %d, version = %s\n", ret, version);
  ret = ubot->get_axis(&axis);
  printf("get_axis       : %d, axis = %d\n", ret, axis);
  printf("\n");

  ret = ubot->get_motion_mode(value_u8);
  printf("get_motion_mode  : %d, mode = %d\n", ret, value_u8[0]);
  ret = ubot->get_motion_enable(&value_int);
  printf("get_motion_enable: %d, value = %d\n", ret, value_int);
  ret = ubot->get_brake_enable(&value_int);
  printf("get_brake_enable : %d, value = %d\n", ret, value_int);
  ret = ubot->get_error_code(value_u8);
  printf("get_error_code   : %d, value = %d %d\n", ret, value_u8[0], value_u8[1]);
  ret = ubot->get_servo_msg(value_u8);
  Print::nvect("get_servo_msg    :", value_u8, axis * 2);
  ret = ubot->get_motion_status(value_u8);
  printf("get_motion_status: %d, value = %d\n", ret, value_u8[0]);
  ret = ubot->get_cmd_num(&value_int);
  printf("get_cmd_num      : %d, value = %d\n", ret, value_int);
  printf("\n");

  ret = ubot->get_tcp_jerk(value_fp);
  printf("get_tcp_jerk    : %d, value = %f\n", ret, value_fp[0]);
  ret = ubot->get_tcp_maxacc(value_fp);
  printf("get_tcp_maxacc  : %d, value = %f\n", ret, value_fp[0]);
  ret = ubot->get_joint_jerk(value_fp);
  printf("get_joint_jerk  : %d, value = %f\n", ret, value_fp[0]);
  ret = ubot->get_joint_maxacc(value_fp);
  printf("get_joint_maxacc: %d, value = %f\n", ret, value_fp[0]);
  ret = ubot->get_tcp_offset(value_fp);
  Print::nvect("get_tcp_offset  : ", value_fp, 6);
  ret = ubot->get_tcp_load(value_fp);
  Print::nvect("get_tcp_load    : ", value_fp, 4);
  ret = ubot->get_gravity_dir(value_fp);
  Print::nvect("get_gravity_dir : ", value_fp, 3);
  ret = ubot->get_collis_sens(value_u8);
  printf("get_collis_sens : %d, value = %d\n", ret, value_u8[0]);
  ret = ubot->get_teach_sens(value_u8);
  printf("get_teach_sens  : %d, value = %d\n", ret, value_u8[0]);
  ret = ubot->get_tcp_target_pos(value_fp);
  Print::nvect("get_tcp_target_pos   : ", value_fp, 6);
  ret = ubot->get_joint_target_pos(value_fp);
  Print::nvect("get_joint_target_pos :", value_fp, axis);

  return 0;
}
