/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"
#include "utra/utra_report_config.h"
#include "utra/utra_report_status.h"

int main(int argc, char *argv[]) {
  int axis = 7;

  char ip[32] = "192.168.1.37";

  printf("==>a1\n");
  arm_report_status_t rx_data1;
  UtraReportStatus10Hz *utra_report1;
  utra_report1 = new UtraReportStatus10Hz(ip, axis);
  printf("==>a2\n");
  sleep(1);
  printf("==>a3\n");
  delete utra_report1;
  printf("==>a4\n");

  sleep(1);
  UtraReportStatus100Hz *utra_report2;
  printf("==>b1\n");
  utra_report2 = new UtraReportStatus100Hz(ip, axis);
  printf("==>b2\n");
  sleep(1);
  printf("==>b3\n");
  delete utra_report2;
  printf("==>b4\n");

  sleep(1);
  UtraReportConfig10Hz *utra_report3;
  printf("==>c1\n");
  utra_report3 = new UtraReportConfig10Hz(ip);
  printf("==>c2\n");
  sleep(1);
  printf("==>c3\n");
  delete utra_report3;
  printf("==>c4\n");

  sleep(1);
  printf("==>d1\n");
  UtraApiTcp *ubot = new UtraApiTcp(ip);
  printf("==>d2\n");
  sleep(1);
  printf("==>d3\n");
  delete ubot;
  printf("==>d4\n");

  sleep(1);
  printf("==>d1\n");
  ubot = new UtraApiTcp(ip);
  printf("==>d2\n");
  sleep(1);
  printf("==>d3\n");
  delete ubot;
  printf("==>d4\n");

  return 0;
}
