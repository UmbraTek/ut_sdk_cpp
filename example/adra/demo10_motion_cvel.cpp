/* Copyright 2024 UmbraTek Inc. All Rights Reserved.
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
  printf("./demo10_motion_cvel arg1\n");
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
 * This is a demo of setting the target speed of 3 actuators simultaneously in broadcast mode (one packet).
 * This function only supports actuators with RS485 ports.
 * The actuator ID is 1 2 3 and RS485 baud rate is 921600
 * Linux requires super user privileges to run code.
 * run command(USB-To-RS485 + COM:/dev/ttyUSB0): sudo ./adra/demo10_motion_cvel 1 0
 * run command(EtherNet-To-RS485 + IP:192.168.1.16): ./adra/demo10_motion_cvel 3 16
 */
int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    print_help();
    return 0;
  }

  int baud = 921600;
  char com[] = "/dev/ttyUSB0";
  char acm[] = "/dev/ttyACM0";
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
  int ret;

  for (int i = 0; i < number; i++) {
    ret = adra->into_motion_mode_vel(id[i]);  // Step 1: Set the motion mode to speed mode.
    check_ret(ret, "into_motion_mode_vel");
    sleep(0.5);
    ret = adra->into_motion_enable(id[i]);  // Step 2: Enable the actuator.
    check_ret(ret, "into_motion_enable");
    sleep(0.5);
  }
  sleep(1);

  float vel1[number] = {50, 100, 150};
  float vel2[number] = {-50, -100, -150};
  while (1) {
    ret = adra->set_cvel_target(id[0], id[number - 1], vel1);  // Step 3: Set the target speed of the actuators.
    check_ret(ret, "set_cvel_target");
    sleep(3);

    ret = adra->set_cvel_target(id[0], id[number - 1], vel2);
    check_ret(ret, "set_cvel_target");
    sleep(3);
  }

  return 0;
}
