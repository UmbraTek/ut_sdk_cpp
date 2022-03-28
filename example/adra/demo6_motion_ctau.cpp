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
 * Broadcast mode (one packet) sets 3 actuator target torque.
 * The actuator ID is 1 2 3 and RS485 baud rate is 921600
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
    ret = adra->into_motion_mode_tau(id[i]);  // Step 1: Set the motion mode to torque mode.
    check_ret(ret, "into_motion_mode_tau");

    ret = adra->into_motion_enable(id[i]);  // Step 2: Enable the actuator.
    check_ret(ret, "into_motion_enable");
  }
  sleep(1);

  float tau1[number] = {0.1, 0.05, 0};
  float tau2[number] = {-0.1, -0.05, -0};
  while (1) {
    ret = adra->set_ctau_target(id[0], id[number - 1], tau1);  // Step 3: Set the target torque of the actuators.
    check_ret(ret, "set_ctau_target");
    sleep(2);

    ret = adra->set_ctau_target(id[0], id[number - 1], tau2);
    check_ret(ret, "set_ctau_target");
    sleep(2);
  }

  return 0;
}
