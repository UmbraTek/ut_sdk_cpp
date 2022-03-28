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
 * This example is to control the device to move to the specified position
 * The actuator ID is 1 and RS485 baud rate is 921600.
 * For better test results, make sure the actuator's current position is within ¡À100 radians.
 * Linux requires super user privileges to run code.
 */
int main(int argc, char *argv[]) {
  int id = 1;
  int baud = 921600;
  const char com[] = "/dev/ttyUSB0";
  AdraApiSerial *adra = new AdraApiSerial(com, baud);

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
