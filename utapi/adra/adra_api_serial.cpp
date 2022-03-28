/* Copyright 2020 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "adra/adra_api_serial.h"

/**
 * AdraApiSerial is an interface class that controls the ADRA actuator through a serial port. USB-to-RS485 or USB-to-CAN module
 * hardware is required to connect the computer and the actuator.
 * Please see the manual: https://umbratek.com/wiki/en/#!adra/adra_api_c.md
 *
 * @param   char           com   USB serial port, The default port on Linux is "/dev/ttyUSB0".
 * @param   int            baud  Baud rate of serial communication.
 *
 * @return  AdraApiSerial        [return description]
 */
AdraApiSerial::AdraApiSerial(const char* com, int baud) {
  utrc_decode_ = new UtrcDecode(0xAA, 0x55, 128);
  socket_serial_ = new SocketSerial(com, baud, 16, utrc_decode_, 128, 45);
  if (socket_serial_->is_error()) {
    printf("[AdraApiS] Error: socket_file open failed, %s\n", com);
    return;
  }

  adrainit(BUS_TYPE::UTRC, socket_serial_, 1);
  sleep(1);
}

AdraApiSerial::~AdraApiSerial(void) {
  if (socket_serial_ != NULL) {
    socket_serial_->close_port();
    delete socket_serial_;
  }
  if (utrc_decode_ != NULL) delete utrc_decode_;
}