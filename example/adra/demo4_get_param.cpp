/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/adra/adra_api_serial.h"

/**
 * This is demo to get the state and parameters of the actuator¡£
 * The actuator ID is 1 and RS485 baud rate is 921600
 * Linux requires super user privileges to run code.
 */
int main(int argc, char *argv[]) {
  int id = 1;
  int baud = 921600;
  const char com[] = "/dev/ttyUSB0";
  AdraApiSerial *adra = new AdraApiSerial(com, baud);

  char uuid[24];
  char version[24];
  int value_int[2];
  float value_fp;
  float value_nfp[2];
  uint8_t value_u8[2];
  int8_t value_int8[2];

  int ret = adra->get_uuid(id, uuid);
  printf("get_uuid         : %d, uuid    = %s\n", ret, uuid);
  ret = adra->get_sw_version(id, version);
  printf("get_sw_version   : %d, version = %s\n", ret, version);

  ret = adra->get_hw_version(id, version);
  printf("get_hw_version   : %d, version = %s\n", ret, version);
  ret = adra->get_multi_version(id, version);
  printf("get_multi_version: %d, version = %s\n", ret, version);
  ret = adra->get_mech_ratio(id, &value_fp);
  printf("get_mech_ratio   : %d, value = %f\n", ret, value_fp);
  printf("\n");

  ret = adra->get_elec_ratio(id, &value_fp);
  printf("get_elec_ratio: %d, value = %f\n", ret, value_fp);
  ret = adra->get_motion_dir(id, value_u8);
  printf("get_motion_dir: %d, value = %d\n", ret, value_u8[0]);
  ret = adra->get_temp_limit(id, &value_int8[0], &value_int8[1]);
  printf("get_temp_limit: %d, value = %d %d\n", ret, value_int8[0], value_int8[1]);
  ret = adra->get_volt_limit(id, &value_u8[0], &value_u8[1]);
  printf("get_volt_limit: %d, value = %d %d\n", ret, value_u8[0], value_u8[1]);
  ret = adra->get_curr_limit(id, &value_fp);
  printf("get_curr_limit: %d, value = %f\n", ret, value_fp);
  ret = adra->get_iwdg_cyc(id, &value_int[0]);
  printf("get_iwdg_cyc  : %d, value = %d\n", ret, value_int[0]);
  printf("\n");

  ret = adra->get_motion_mode(id, value_u8);
  printf("get_motion_mode  : %d, value = %d\n", ret, value_u8[0]);
  ret = adra->get_motion_enable(id, value_u8);
  printf("get_motion_enable: %d, value = %d\n", ret, value_u8[0]);
  ret = adra->get_brake_enable(id, value_u8);
  printf("get_brake_enable : %d, value = %d\n", ret, value_u8[0]);
  ret = adra->get_temp_driver(id, &value_fp);
  printf("get_temp_driver  : %d, value = %.1f\n", ret, value_fp);
  ret = adra->get_temp_motor(id, &value_fp);
  printf("get_temp_motor   : %d, value = %.1f\n", ret, value_fp);
  ret = adra->get_bus_volt(id, &value_fp);
  printf("get_bus_volt     : %d, value = %.1f\n", ret, value_fp);
  ret = adra->get_bus_curr(id, &value_fp);
  printf("get_bus_curr     : %d, value = %.1f\n", ret, value_fp);
  ret = adra->get_multi_volt(id, &value_fp);
  printf("get_multi_volt   : %d, value = %.1f\n", ret, value_fp);
  ret = adra->get_error_code(id, value_u8);
  printf("get_error_code   : %d, value = %d\n", ret, value_u8[0]);
  printf("\n");

  ret = adra->get_pos_limit_min(id, &value_fp);
  printf("get_pos_limit_min : %d, value = %f\n", ret, value_fp);
  ret = adra->get_pos_limit_max(id, &value_fp);
  printf("get_pos_limit_max : %d, value = %f\n", ret, value_fp);
  ret = adra->get_pos_limit_diff(id, &value_fp);
  printf("get_pos_limit_diff: %d, value = %f\n", ret, value_fp);
  ret = adra->get_vel_limit_min(id, &value_fp);
  printf("get_vel_limit_min : %d, value = %f\n", ret, value_fp);
  ret = adra->get_vel_limit_max(id, &value_fp);
  printf("get_vel_limit_max : %d, value = %f\n", ret, value_fp);
  ret = adra->get_vel_limit_diff(id, &value_fp);
  printf("get_vel_limit_diff: %d, value = %f\n", ret, value_fp);
  ret = adra->get_tau_limit_min(id, &value_fp);
  printf("get_tau_limit_min : %d, value = %f\n", ret, value_fp);
  ret = adra->get_tau_limit_max(id, &value_fp);
  printf("get_tau_limit_max : %d, value = %f\n", ret, value_fp);
  ret = adra->get_tau_limit_diff(id, &value_fp);
  printf("get_tau_limit_diff: %d, value = %f\n", ret, value_fp);
  printf("\n");

  ret = adra->get_pos_target(id, &value_fp);
  printf("get_pos_target : %d, value = %f\n", ret, value_fp);
  ret = adra->get_pos_current(id, &value_fp);
  printf("get_pos_current: %d, value = %f\n", ret, value_fp);
  ret = adra->get_vel_target(id, &value_fp);
  printf("get_vel_target : %d, value = %f\n", ret, value_fp);
  ret = adra->get_vel_current(id, &value_fp);
  printf("get_vel_current: %d, value = %f\n", ret, value_fp);
  ret = adra->get_tau_target(id, &value_fp);
  printf("get_tau_target : %d, value = %f\n", ret, value_fp);
  ret = adra->get_tau_current(id, &value_fp);
  printf("get_tau_current: %d, value = %f\n", ret, value_fp);

  ret = adra->get_pos_pidp(id, &value_nfp[0]);
  printf("get_pos_pid    : %d, pid_p = %f\n", ret, value_nfp[0]);
  ret = adra->get_vel_pidp(id, &value_nfp[0]);
  ret = adra->get_vel_pidi(id, &value_nfp[1]);
  printf("get_vel_pid    : %d, pid_p = %f, pid_p = %f\n", ret, value_nfp[0], value_nfp[1]);
  ret = adra->get_tau_pidp(id, &value_nfp[0]);
  ret = adra->get_tau_pidi(id, &value_nfp[1]);
  printf("get_tau_pid    : %d, pid_p = %f, pid_p = %f\n", ret, value_nfp[0], value_nfp[1]);

  ret = adra->get_pos_smooth_cyc(id, value_u8);
  printf("get_pos_smooth_cyc: %d, value = %d\n", ret, value_u8[0]);
  ret = adra->get_vel_smooth_cyc(id, value_u8);
  printf("get_vel_smooth_cyc: %d, value = %d\n", ret, value_u8[0]);
  ret = adra->get_tau_smooth_cyc(id, value_u8);
  printf("get_tau_smooth_cyc: %d, value = %d\n", ret, value_u8[0]);

  return 0;
}
