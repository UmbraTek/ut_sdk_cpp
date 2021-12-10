/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utra/utra_report_config.h"
#include "utra/utra_report_status.h"

int main(int argc, char *argv[]) {
  int opt = 0;
  uint8_t mode = 1;
  char ip[64];
  std::string port_name = "192.168.1.89";

  while ((opt = getopt(argc, argv, "i:m:")) != -1) {
    switch (opt) {
      case 'i':
        strcpy(ip, std::string(optarg).data());
        break;

      case 'm':
        mode = atoi(optarg);
        break;
    }
  }

  switch (mode) {
    case 1:
      arm_report_status_t rx_data1;
      UtraReportStatus10Hz *utra_report1;
      utra_report1 = new UtraReportStatus10Hz(ip, 6);
      while (1) {
        if (utra_report1->is_update()) {
          utra_report1->get_data(&rx_data1);
          utra_report1->print_data(&rx_data1);
        }
      }
      break;

    case 2:
      arm_report_status_t rx_data2;
      UtraReportStatus100Hz *utra_report2;
      utra_report2 = new UtraReportStatus100Hz(ip, 6);
      while (1) {
        if (utra_report2->is_update()) {
          utra_report2->get_data(&rx_data2);
          utra_report2->print_data(&rx_data2);
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
        }
      }
      break;
  }

  return 0;
}
