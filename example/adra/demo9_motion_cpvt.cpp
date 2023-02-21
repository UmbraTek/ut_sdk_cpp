/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/adra/adra_api_serial.h"
#include "utapi/adra/adra_api_tcp.h"
#include "utapi/adra/adra_api_udp.h"

void print_help(void) {
  printf("Select the communication interface and protocol type\n");
  printf("./demo9_motion_cpvt arg1\n");
  printf("    [arg1] 1: Serial COM\n");
  printf("           2: Serial ACM\n");
  printf("           3: TCP\n");
  printf("           4: UDP\n");
}

void check_ret(int ret, const char *str) {
  if (ret == 0)
    printf("Good! successfully %s\n", str);
  else
    printf("Error! Failed %s %d\n", str, ret);
}

/**
 * This demo is using broadcast mode to get the current position, velocity and torque of 3 actuators (one packet).
 * This function only supports actuators with RS485 ports.
 * The actuator ID is 1 2 3 and RS485 baud rate is 921600
 * Linux requires super user privileges to run code.
 * run command(USB-To-RS485 + COM:/dev/ttyUSB0): sudo ./adra/demo9_motion_cpvt 1 0
 * run command(EtherNet-To-RS485 + IP:192.168.1.16): ./adra/demo9_motion_cpvt 3 16
 */
int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    print_help();
    return 0;
  }

  int baud = 921600;
  char com[] = "/dev/ttyUSB0";
  char acm[] = "/dev/ttyACM0";
  char pcie[] = "/dev/ttyUT0";
  char ip[] = "192.168.1.168";
  AdraApiBase *adra = NULL;

  switch (atoi(argv[1])) {
    case 1:
      if (argc == 3) {
        strcpy(com, "/dev/ttyUSB");
        strcat(com, argv[2]);
      }
      adra = new AdraApiSerial(com, baud, BUS_TYPE::UTRC);
      if (adra->is_error()) return 0;
      break;

    case 2:
      if (argc == 3) {
        strcpy(acm, "/dev/ttyACM");
        strcat(acm, argv[2]);
      }
      adra = new AdraApiSerial(acm, baud, BUS_TYPE::UTRC);
      if (adra->is_error()) return 0;
      adra->into_usb_pm();
      break;

    case 3:
      if (argc == 3) {
        strcpy(ip, "192.168.1.");
        strcat(ip, argv[2]);
      }
      adra = new AdraApiTcp(ip, 6001, BUS_TYPE::UTRC);
      if (adra->is_error()) return 0;
      break;

    case 4:
      if (argc == 3) {
        strcpy(ip, "192.168.1.");
        strcat(ip, argv[2]);
      }
      adra = new AdraApiUdp(ip, 5001, BUS_TYPE::UTRC);
      if (adra->is_error()) return 0;
      break;

    default:
      print_help();
      return 0;
  }

  int number = 3;
  int id[number] = {1, 2, 3};
  float vels[number] = {100, -60, 20};
  int filter_param[number] = {999, 100, 1};
  int ret;

  for (int i = 0; i < number; i++) {
    ret = adra->into_motion_mode_vel(id[i]);  // Step 1: Set the motion mode to velocity mode.
    check_ret(ret, "into_motion_mode_vel");
    sleep(0.5);
    ret = adra->into_motion_enable(id[i]);  // Step 2: Enable the actuator.
    check_ret(ret, "into_motion_enable");
    sleep(0.5);
    ret = adra->set_vel_output_filter_param(id[i], filter_param[i]);  // Step 3: Set the filter param.
    check_ret(ret, "set_vel_output_filter_param");
    sleep(0.5);
    ret = adra->set_vel_target(id[i], vels[i]);  // Step 4: Set the target velocity.
    check_ret(ret, "set_vel_target");
    sleep(0.5);
  }
  sleep(1);

  int broadcast_num[number];
  float pos[number];
  float vel[number];
  float tau[number];
  int rets[number];

  while (1) {
    adra->get_cpvt_current(id[0], id[number - 1], broadcast_num, pos, vel, tau, rets);
    printf("get_cpostau_current: %d %d %d\n", rets[0], rets[1], rets[2]);
    printf("get_cpostau_current: pos: %f %f %f, vel: %f %f %f, tau: %f %f %f\n", pos[0], pos[1], pos[2], vel[0], vel[1], vel[2],
           tau[0], tau[1], tau[2]);

    LinuxCvl::rt_sleep_us(100000);
  }

  return 0;
}
