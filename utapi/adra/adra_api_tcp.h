/* Copyright 2022 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#ifndef __ADRA_API_TCP_H__
#define __ADRA_API_TCP_H__

#include "adra/adra_api_base.h"
#include "common/socket_tcp.h"

class AdraApiTcp : public AdraApiBase {
 public:
  /**
   * AdraApiTcp is an interface class that controls the ADRA actuator through a EtherNet TCP. EtherNet-to-RS485 or
   * EtherNet-to-CAN module hardware is required to connect the computer and the actuator.
   *
   * @param   char           ip       IP address of the EtherNet module.
   * @param   int            port     TCP port of EtherNet module. The default value is 6001.
   * @param   int            bus_type 0 indicates the actuator that uses the RS485 port.
   *							                    1 indicates the actuator that uses the CAN port.
   *							                    Defaults to 0.
   */
  AdraApiTcp(char *ip, int port = 6001, int bus_type = BUS_TYPE::UTRC) {
    if (bus_type == BUS_TYPE::UTRC) {
      utrc_decode_ = new UtrcDecode(0xAA, 0x55, 128);
      socket_fp = new SocketTcp(ip, port, 16, utrc_decode_, 125, 45);
      if (socket_fp->is_error()) {
        printf("[Adra TCP] Error: SocketTcp failed, %s %d\n", ip, port);
        is_error_ = true;
        return;
      }
    } else if (bus_type == BUS_TYPE::UTCC) {
      utcc_decode_ = new UtccDecode(0xAA, 0x55, 128);

      socket_fp = new SocketTcp(ip, port, 16, utcc_decode_, 125, 45);

      if (socket_fp->is_error()) {
        printf("[Adra TCP] Error: SocketTcp failed, %s %d\n", ip, port);
        is_error_ = true;
        return;
      }
    }

    adrainit(bus_type, socket_fp, 1);
    sleep(1);

    connect_net_module();
  }

  ~AdraApiTcp(void) {
    if (socket_fp != NULL) {
      socket_fp->close_port();
      delete socket_fp;
    }
    if (utrc_decode_ != NULL) delete utrc_decode_;
    if (utcc_decode_ != NULL) delete utcc_decode_;
  }

  bool is_error(void) { return is_error_; }

  void into_usb_pm(void) {}

 private:
  UtrcDecode *utrc_decode_ = NULL;
  UtccDecode *utcc_decode_ = NULL;
  SocketTcp *socket_fp = NULL;
  bool is_error_ = false;
};

#endif
