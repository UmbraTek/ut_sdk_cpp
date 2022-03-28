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

/**
 * This demo controls the actuator running at a constant speed in speed mode.
 * The actuator ID is 1 and RS485 baud rate is 921600.
 * Linux requires super user privileges to run code.
 */
int main(int argc, char *argv[]) {
  int id = 1;
  int baud = 921600;
  const char com[] = "/dev/ttyUSB0";
  AdraApiSerial *adra = new AdraApiSerial(com, baud);

  int ret = adra->into_motion_mode_vel(id);  // Step 1: Set the motion mode to speed mode.
  check_ret(ret, "into_motion_mode_vel");

  ret = adra->into_motion_enable(id);  // Step 2: Enable the actuator.
  check_ret(ret, "into_motion_enable");
  sleep(1);

  while (1) {
    ret = adra->set_vel_target(id, 50);  // Step 3: Set the target speed of the actuator.
    check_ret(ret, "set_vel_target");
    sleep(5);

    ret = adra->set_vel_target(id, -50);
    check_ret(ret, "set_vel_target");
    sleep(5);
  }

  return 0;
}
