/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/adra/adra_api_serial.h"

void check_ret(int ret, const char *str) {
  if (ret == 0)
    printf("Good! successfully %s\n", str);
  else
    printf("Error! Failed %s %d\n", str, ret);
}

int main(int argc, char *argv[]) {
  const char com[] = "/dev/ttyUSB0";
  int baud = 921600;
  int id = 1;

  AdraApiSerial *adra = new AdraApiSerial(com, baud);

  int ret = adra->into_motion_mode_vel(id);
  check_ret(ret, "into_motion_mode_vel");

  ret = adra->into_motion_enable(id);
  check_ret(ret, "into_motion_enable");
  sleep(1);

  while (1) {
    ret = adra->set_vel_target(id, 31.4);
    check_ret(ret, "set_vel_target");
    sleep(10);

    ret = adra->set_vel_target(id, -31.4);
    check_ret(ret, "set_vel_target");
    sleep(10);
  }

  return 0;
}
