/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utapi/utra/utra_flxie_api.h"

/**
 * TThis is a demo to get the parameters, status and other information of FLXI E on the robot.
 * run command: ./utra/demo21_flxie2_get_param -i 192.168.1.xxx
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

  char uuid[24], version[24];
  int ret = fixie->get_uuid(uuid);
  printf("get_uuid: %d, uuid = %s\n", ret, uuid);
  ret = fixie->get_sw_version(version);
  printf("get_sw_version: %d, version = %s\n", ret, version);
  ret = fixie->get_hw_version(version);
  printf("get_hw_version: %d, version = %s\n", ret, version);
  printf("\n");

  int min, max;
  float value_fp32;
  ret = fixie->get_temp_limit(&min, &max);
  printf("get_temp_limit: %d, value = %d %d\n", ret, min, max);
  ret = fixie->get_volt_limit(&min, &max);
  printf("get_volt_limit: %d, value = %d %d\n", ret, min, max);
  ret = fixie->get_curr_limit(&value_fp32);
  printf("get_curr_limit: %d, value = %f\n", ret, value_fp32);
  printf("\n");

  uint8_t value_u8;
  ret = fixie->get_motion_mode(&value_u8);
  printf("get_motion_mode  : %d, value = %d\n", ret, value_u8);
  ret = fixie->get_motion_enable(&value_u8);
  printf("get_motion_enable: %d, value = %d\n", ret, value_u8);
  ret = fixie->get_temp_driver(&value_fp32);
  printf("get_temp_driver  : %d, value = %.1f\n", ret, value_fp32);
  ret = fixie->get_temp_motor(&value_fp32);
  printf("get_temp_motor   : %d, value = %.1f\n", ret, value_fp32);
  ret = fixie->get_bus_volt(&value_fp32);
  printf("get_bus_volt     : %d, value = %.1f\n", ret, value_fp32);
  ret = fixie->get_bus_curr(&value_fp32);
  printf("get_bus_curr     : %d, value = %.1f\n", ret, value_fp32);
  ret = fixie->get_error_code(&value_u8);
  printf("get_error_code   : %d, value = %d\n", ret, value_u8);
  printf("\n");

  ret = fixie->get_vel_limit_min(&value_fp32);
  printf("get_vel_limit_min : %d, value = %f\n", ret, value_fp32);
  ret = fixie->get_vel_limit_max(&value_fp32);
  printf("get_vel_limit_max : %d, value = %f\n", ret, value_fp32);
  ret = fixie->get_tau_limit_min(&value_fp32);
  printf("get_tau_limit_min : %d, value = %f\n", ret, value_fp32);
  ret = fixie->get_tau_limit_max(&value_fp32);
  printf("get_tau_limit_max : %d, value = %f\n", ret, value_fp32);
  printf("\n");

  ret = fixie->get_pos_target(&value_fp32);
  printf("get_pos_target : %d, value = %f\n", ret, value_fp32);
  ret = fixie->get_pos_current(&value_fp32);
  printf("get_pos_current: %d, value = %f\n", ret, value_fp32);
  ret = fixie->get_tau_target(&value_fp32);
  printf("get_tau_target : %d, value = %f\n", ret, value_fp32);
  ret = fixie->get_tau_current(&value_fp32);
  printf("get_tau_current: %d, value = %f\n", ret, value_fp32);

  float fp_list[4];
  ret = fixie->get_pos_pidp(&value_fp32);
  printf("get_pos_pid    : %d, pid_p = %f\n", ret, value_fp32);
  ret = fixie->get_tau_pidp(&fp_list[0]);
  ret = fixie->get_tau_pidi(&fp_list[1]);
  printf("get_tau_pid    : %d, pid_p = %f, pid_p = %f\n\n", ret, fp_list[0], fp_list[1]);

  ret = fixie->get_pos_smooth_cyc(&value_u8);
  printf("get_pos_smooth_cyc: %d, value = %d\n", ret, value_u8);
  ret = fixie->get_tau_smooth_cyc(&value_u8);
  printf("get_tau_smooth_cyc: %d, value = %d\n", ret, value_u8);

  float acc, b2, b3, h1, d;
  ret = fixie->get_pos_adrc_param(3, &acc);
  ret = fixie->get_pos_adrc_param(9, &b2);
  ret = fixie->get_pos_adrc_param(10, &b3);
  ret = fixie->get_pos_adrc_param(12, &h1);
  ret = fixie->get_pos_adrc_param(14, &d);
  printf("get_pos_adrc_param: %d, value = %f %f %f %f %f\n", ret, acc, b2, b3, h1, d);
  ret = fixie->get_tau_adrc_param(3, &acc);
  ret = fixie->get_tau_adrc_param(9, &b2);
  ret = fixie->get_tau_adrc_param(10, &b3);
  ret = fixie->get_tau_adrc_param(12, &h1);
  ret = fixie->get_tau_adrc_param(14, &d);
  printf("get_tau_adrc_param: %d, value = %f %f %f %f %f\n", ret, acc, b2, b3, h1, d);

  ret = fixie->get_senser(fp_list);
  printf("get_senser: %d, value = %f %f %f %f\n", ret, fp_list[0], fp_list[1], fp_list[2], fp_list[3]);

  return 0;
}
