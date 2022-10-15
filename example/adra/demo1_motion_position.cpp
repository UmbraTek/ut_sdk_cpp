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
  printf("./demo1_motion_position arg1 arg2\n");
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
 * This demo is to control the device to move to the specified position
 * The actuator ID is 1 and RS485 baud rate is 921600.
 * For better test results, make sure the actuator's current position is within ±100 radians.
 * Linux requires super user privileges to run code.
 * run command(USB-To-RS485 + COM:/dev/ttyUSB0): sudo ./adra/demo1_motion_position 1 0 0
 * run command(EtherNet-To-RS485 + IP:192.168.1.16): ./adra/demo1_motion_position 3 0 16
 */
int main(int argc, char *argv[]) {
  if (argc != 3 && argc != 4) {
    print_help();
    return 0;
  }

  int id = 1;
  int baud = 921600;
  char com[] = "/dev/ttyUSB0";
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
        strcpy(com, "/dev/ttyUSB");
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

  int ret = adra->into_motion_mode_pos(id);  // Step 1: Set the motion mode to position mode.
  check_ret(ret, "into_motion_mode_pos");

  ret = adra->into_motion_enable(id);  // Step 2: Enable the actuator.
  check_ret(ret, "into_motion_enable");
  sleep(1);

  while (1) {
    ret = adra->set_pos_target(id, 50);  // Step 3: Set the target position of the actuator.
    check_ret(ret, "set_pos_target");
    sleep(3);

    ret = adra->set_pos_target(id, -50);
    check_ret(ret, "set_pos_target");
    sleep(3);
  }

  return 0;
}
