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
  printf("./demo3_motion_torque arg1 arg2\n");
  printf("    [arg1] 1: Serial COM\n");
  printf("           2: Serial ACM\n");
  printf("           3: TCP\n");
  printf("           4: UDP\n");
  printf("    [arg2] 0: RS485\n");
  printf("           1: CAN\n");
}

void check_ret(int ret, const char *str) {
  if (ret == 0)
    printf("Good! successfully %s\n", str);
  else
    printf("Error! Failed %s %d\n", str, ret);
}

/**
 * This demo controls the actuator running at a constant torque in torque mode.
 * The actuator ID is 1 and RS485 baud rate is 921600
 * Linux requires super user privileges to run code.
 */
int main(int argc, char *argv[]) {
  if (argc != 3 && argc != 4) {
    print_help();
    return 0;
  }

  int id = 1;
  int baud = 921600;
  char com[] = "/dev/ttyCOM0";
  char acm[] = "/dev/ttyACM0";
  char ip[] = "192.168.1.167";
  AdraApiBase *adra = NULL;

  int bus_type = 0;
  if (atoi(argv[2]) == 0) {
    bus_type = BUS_TYPE::UTRC;
  } else if (atoi(argv[2]) == 1) {
    bus_type = BUS_TYPE::UTCC;
  } else {
    print_help();
    return 0;
  }

  switch (atoi(argv[1])) {
    case 1:
      if (argc == 4) {
        strcpy(com, "/dev/ttyCOM");
        strcat(com, argv[3]);
      }
      adra = new AdraApiSerial(com, baud, bus_type);
      if (adra->is_error()) return 0;
      break;

    case 2:
      if (argc == 4) {
        strcpy(acm, "/dev/ttyACM");
        strcat(acm, argv[3]);
      }
      adra = new AdraApiSerial(acm, baud, bus_type);
      if (adra->is_error()) return 0;
      adra->into_usb_pm();
      break;

    case 3:
      if (argc == 4) {
        strcpy(ip, "192.168.1.");
        strcat(ip, argv[3]);
      }
      adra = new AdraApiTcp(ip, 6001, bus_type);
      if (adra->is_error()) return 0;
      break;

    case 4:
      if (argc == 4) {
        strcpy(ip, "192.168.1.");
        strcat(ip, argv[3]);
      }
      adra = new AdraApiUdp(ip, 5001, bus_type);
      if (adra->is_error()) return 0;
      break;

    default:
      print_help();
      return 0;
  }

  int ret = adra->into_motion_mode_tau(id);  // Step 1: Set the motion mode to torque mode.
  check_ret(ret, "into_motion_mode_tau");

  ret = adra->into_motion_enable(id);  // Step 2: Enable the actuator.
  check_ret(ret, "into_motion_enable");
  sleep(1);

  while (1) {
    ret = adra->set_tau_target(id, 0.1);  // Step 3: Set the target torque of the actuator.
    check_ret(ret, "set_tau_target");
    sleep(5);

    ret = adra->set_tau_target(id, -0.1);
    check_ret(ret, "set_tau_target");
    sleep(5);
  }

  return 0;
}