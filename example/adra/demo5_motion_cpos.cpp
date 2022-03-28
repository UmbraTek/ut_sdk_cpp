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
 * Broadcast mode (one packet) sets 3 actuator target positions.
 * The actuator ID is 1 2 3 and RS485 baud rate is 921600
 * For better test results, make sure the actuator's current position is within ±100 radians.
 * Linux requires super user privileges to run code.
 */
int main(int argc, char *argv[]) {
  int baud = 921600;
  const char com[] = "/dev/ttyUSB0";
  AdraApiSerial *adra = new AdraApiSerial(com, baud);

  int number = 3;
  int id[number] = {1, 2, 3};
  int ret;

  for (int i = 0; i < number; i++) {
    ret = adra->into_motion_mode_pos(id[i]);  // Step 1: Set the motion mode to position mode.
    check_ret(ret, "into_motion_mode_pos");

    ret = adra->into_motion_enable(id[i]);  // Step 2: Enable the actuator.
    check_ret(ret, "into_motion_enable");
  }
  sleep(1);

  float pos1[number] = {31.4, 62.8, 15.7};
  float pos2[number] = {-31.4, -62.8, -15.7};
  while (1) {
    ret = adra->set_cpos_target(id[0], id[number - 1], pos1);  // Step 3: Set the target position of the actuators.
    check_ret(ret, "set_cpos_target");
    sleep(3);

    ret = adra->set_cpos_target(id[0], id[number - 1], pos2);
    check_ret(ret, "set_cpos_target");
    sleep(3);
  }

  return 0;
}
