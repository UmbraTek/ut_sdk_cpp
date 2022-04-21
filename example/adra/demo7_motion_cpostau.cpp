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
  printf("./demo7_motion_cpostau arg1\n");
  printf("    [arg1] 1: Serial COM\n");
  printf("           2: Serial ACM\n");
  printf("           3: TCP\n");
  printf("           4: UDP\n");
}

void check_ret(int ret, const char* str) {
  if (ret == 0)
    printf("Good! successfully %s\n", str);
  else
    printf("Error! Failed %s %d\n", str, ret);
}

/**
 * Set the maximum interval of broadcast read commands.
 * Broadcast mode (one packet) sets 3 actuator target positions and feedforward torques.
 * The broadcast mode (a packet) gets the current position and current torque of the three actuators.
 * For better test results, make sure the actuator's current position is within ±100 radians.
 * Linux requires super user privileges to run code.
 */
int main(int argc, char* argv[]) {
  if (argc != 2 && argc != 3) {
    print_help();
    return 0;
  }

  int baud = 921600;
  char com[] = "/dev/ttyCOM0";
  char acm[] = "/dev/ttyACM0";
  char ip[] = "192.168.1.167";
  AdraApiBase* adra = NULL;

  switch (atoi(argv[1])) {
    case 1:
      if (argc == 3) {
        strcpy(com, "/dev/ttyCOM");
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
  int ret;

  for (int i = 0; i < number; i++) {
    ret = adra->into_motion_mode_pos(id[i]);  // Step 1: Set the motion mode to position mode.
    check_ret(ret, "into_motion_mode_pos");

    ret = adra->into_motion_enable(id[i]);  // Step 2: Enable the actuator.
    check_ret(ret, "into_motion_enable");

    // Step 3: Set the time to 200000 current loop cycles,
    // because the current loop is 20K, so it is a 10-second interval.
    ret = adra->set_iwdg_cyc(id[i], 200000);
    check_ret(ret, "set_iwdg_cyc");
  }
  sleep(1);

  float pos1[number] = {31.4, 62.8, 15.7};
  float pos2[number] = {-31.4, -62.8, -15.7};
  float tau1[number] = {0.1, 0.05, 0};
  float tau2[number] = {-0.1, -0.05, -0};
  int broadcast_num[number];
  float pos[number];
  float tau[number];
  int rets[number];

  while (1) {
    // Step 4: Sets the current positions and feedforward torques of the three actuators.
    ret = adra->set_cpostau_target(id[0], id[number - 1], pos1, tau1);
    check_ret(ret, "set_cpostau_target");

    // Step 5: Read the current position and torque of the three actuators.
    adra->get_cpostau_current(id[0], id[number - 1], broadcast_num, pos, tau, rets);
    printf("get_cpostau_current: pos: %f %f %f, tau: %f %f %f\n", pos[0], pos[1], pos[2], tau[0], tau[1], tau[2]);
    printf("get_cpostau_current: broadcast_num:%d %d %d, ret:%d %d %d\n", broadcast_num[0], broadcast_num[1], broadcast_num[2],
           rets[0], rets[1], rets[2]);
    sleep(5);

    ret = adra->set_cpostau_target(id[0], id[number - 1], pos2, tau2);
    check_ret(ret, "set_cpostau_target");

    adra->get_cpostau_current(id[0], id[number - 1], broadcast_num, pos, tau, rets);
    printf("get_cpostau_current: pos: %f %f %f, tau: %f %f %f\n", pos[0], pos[1], pos[2], tau[0], tau[1], tau[2]);
    printf("get_cpostau_current: broadcast_num:%d %d %d, ret:%d %d %d\n\n", broadcast_num[0], broadcast_num[1],
           broadcast_num[2], rets[0], rets[1], rets[2]);
    sleep(5);
  }

  return 0;
}
