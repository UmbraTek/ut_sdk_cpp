/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/adra/adra_api_serial.h"

void check_ret(int ret, const char* str) {
  if (ret == 0)
    printf("Good! successfully %s\n", str);
  else
    printf("Error! Failed %s %d\n", str, ret);
}

/**
 * Set the maximum interval of broadcast read commands.
 * Broadcast mode (one packet) sets 3 actuator target positions and feedforward torques.
 * The broadcast mode (a packet) gets the current position and current torque of the three actuators.
 * For better test results, make sure the actuator's current position is within ±100 radians.
 * Linux requires super user privileges to run code.
 */
int main(int argc, char* argv[]) {
  int baud = 921600;
  const char com[] = "/dev/ttyUSB0";
  AdraApiSerial* adra = new AdraApiSerial(com, baud);

  int number = 3;
  int id[number] = {1, 2, 3};
  int ret;

  for (int i = 0; i < number; i++) {
    ret = adra->into_motion_mode_pos(id[i]);  // Step 1: Set the motion mode to position mode.
    check_ret(ret, "into_motion_mode_pos");

    ret = adra->into_motion_enable(id[i]);  // Step 2: Enable the actuator.
    check_ret(ret, "into_motion_enable");

    // Step 3: Set the time to 200000 current loop cycles,
    // because the current loop is 20K, so it is a 10-second interval.
    ret = adra->set_iwdg_cyc(id[i], 200000);
    check_ret(ret, "set_iwdg_cyc");
  }
  sleep(1);

  float pos1[number] = {31.4, 62.8, 15.7};
  float pos2[number] = {-31.4, -62.8, -15.7};
  float tau1[number] = {0.1, 0.05, 0};
  float tau2[number] = {-0.1, -0.05, -0};
  int broadcast_num[number];
  float pos[number];
  float tau[number];
  int rets[number];

  while (1) {
    // Step 4: Sets the current positions and feedforward torques of the three actuators.
    ret = adra->set_cpostau_target(id[0], id[number - 1], pos1, tau1);
    check_ret(ret, "set_cpostau_target");

    // Step 5: Read the current position and torque of the three actuators.
    adra->get_cpostau_current(id[0], id[number - 1], broadcast_num, pos, tau, rets);
    printf("get_cpostau_current: pos: %f %f %f, tau: %f %f %f\n", pos[0], pos[1], pos[2], tau[0], tau[1], tau[2]);
    printf("get_cpostau_current: broadcast_num:%d %d %d, ret:%d %d %d\n", broadcast_num[0], broadcast_num[1], broadcast_num[2],
           rets[0], rets[1], rets[2]);
    sleep(5);

    ret = adra->set_cpostau_target(id[0], id[number - 1], pos2, tau2);
    check_ret(ret, "set_cpostau_target");

    adra->get_cpostau_current(id[0], id[number - 1], broadcast_num, pos, tau, rets);
    printf("get_cpostau_current: pos: %f %f %f, tau: %f %f %f\n", pos[0], pos[1], pos[2], tau[0], tau[1], tau[2]);
    printf("get_cpostau_current: broadcast_num:%d %d %d, ret:%d %d %d\n\n", broadcast_num[0], broadcast_num[1],
           broadcast_num[2], rets[0], rets[1], rets[2]);
    sleep(5);
  }

  return 0;
}
