/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utra/utra_report_config.h"
#include "utra/utra_report_status.h"

/**
 * This is a demo to print the data of three real-time automatically reported ports.
 * run command:
 *    ./utra/demo01_report -i 192.168.1.xxx -a 6 -m 1
 *    ./utra/demo01_report -i 192.168.1.xxx -a 6 -m 2
 *    ./utra/demo01_report -i 192.168.1.xxx -a 6 -m 3
 *    -i: The address of the robot arm
 *    -a: The number of joint axes of the Arm
 *    -m: Automatic reporting mode
 */
int main(int argc, char *argv[]) {
  int axis = 6;
  int opt = 0;
  uint8_t mode = 1;
  char ip[64];
  std::string port_name = "192.168.1.14";

  while ((opt = getopt(argc, argv, "i:m:a:")) != -1) {
    switch (opt) {
      case 'i':
        strcpy(ip, std::string(optarg).data());
        break;

      case 'm':
        mode = atoi(optarg);
        break;

      case 'a':
        axis = atoi(optarg);
        break;
    }
  }

  switch (mode) {
    case 1:
      arm_report_status_t rx_data1;
      UtraReportStatus10Hz *utra_report1;
      utra_report1 = new UtraReportStatus10Hz(ip, axis);
      while (1) {
        if (utra_report1->is_update()) {
          utra_report1->get_data(&rx_data1);
          utra_report1->print_data(&rx_data1);
        } else {
          usleep(10000);
        }
      }
      break;

    case 2:
      arm_report_status_t rx_data2;
      UtraReportStatus100Hz *utra_report2;
      utra_report2 = new UtraReportStatus100Hz(ip, axis);
      while (1) {
        if (utra_report2->is_update()) {
          utra_report2->get_data(&rx_data2);
          utra_report2->print_data(&rx_data2);
        } else {
          usleep(1000);
        }
      }
      break;

    case 3:
      arm_report_config_t rx_data3;
      UtraReportConfig10Hz *utra_report3;
      utra_report3 = new UtraReportConfig10Hz(ip);
      while (1) {
        if (utra_report3->is_update()) {
          utra_report3->get_data(&rx_data3);
          utra_report3->print_data(&rx_data3);
        } else {
          usleep(10000);
        }
      }
      break;

    case 4:
      arm_report_status_t rx_data4;
      UtraReportStatusXXHz *utra_report4;
      utra_report4 = new UtraReportStatusXXHz(ip, axis);
      while (1) {
        if (utra_report4->is_update()) {
          utra_report4->get_data(&rx_data4);
          utra_report4->print_data(&rx_data4);
        } else {
          usleep(100);
        }
      }
      break;
  }

  return 0;
}
