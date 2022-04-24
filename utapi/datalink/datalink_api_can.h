/* Copyright 2022 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#ifndef __DATALINK_API_CAN_H__
#define __DATALINK_API_CAN_H__

#include "common/socket_serial.h"
#include "common/socket_tcp.h"
#include "common/socket_udp.h"
#include "common/utcc_t.h"

typedef struct {
  uint16_t id;
  uint8_t len;
  uint8_t data[32];
} can_stream_t;

class DataLinkApiCan {
 public:
  /**
   * [connect_type description]
   *
   * @param   int    connect_type  1: Use TCP to transfer data.
   *                               2: Use UDP to transfer data.
   *                               3: Use USB to transfer data.
   * @param   char   argv1         If TCP/UDP is used, argv1 is IP address.
   *                               If USB is used, argv1 is USB virtual serial number.
   * @param   int    argv2         If TCP/UDP is used, argv2 is tcp port of the EtherNet module
   *                               If USB is used, argv2 is serial baud of the EtherNet module.
   * @param   int    argv3         If TCP/UDP is used, argv3 is udp port of the EtherNet module.
   *                               If USB is used, argv3 is NULL.
   * @param   int    is_reset      Defaults to 1. Whether to reset can be reset in the following situations.
   *                               1. If connection type is UDP and DataLink is connected to TCP after being powered on,
   *                                  reset is required.
   *                               2. If connection type is UDP and DataLink is not connected to TCP after being powered on,
   *                                  you do not need to reset.
   *                               3. If connection type is TCP and DataLink is connected to TCP or UDP after being powered on,
   *                                  reset is required.
   *                               4. If connection type is TCP and DataLink is not connected to TCP or UDP after being powered
   *                                  on, you do not need to reset.
   *                               5. If connection type is USB and DataLink is not connected to USB after being powered on,
   *                                  reset is required.
   *                               6. If connection type is USB and DataLink is connected to USB after being powered on,
   *                                  you do not need to reset.
   *                               Note: In any case, it is good to use reset, but the initialization time is about 3 seconds
   *                                     longer than that without reset.
   *                               Note: After DataLink is powered on and connected to USB, it needs to be powered on again to
   *                                     connect to TCP or UDP.
   * @param   int   baud           Set the baud rate of the EtherNet to CAN module to be the same as that of the actuator.
   *                               If the baud rate is set to 0xFFFFFFFF, the baud rate of the EtherNet to CAN module is
   *                               not set. The default value is 0xFFFFFFFF.
   *
   * @return  DataLinkApiRs485     [return description]
   */

  DataLinkApiCan(int connect_type, char* argv1, int argv2, int argv3, int is_reset = 1, int baud = 0xFFFFFFFF) {
    is_error_ = 0;

    if (connect_type == 1) {
      char* ip = argv1;
      int tcp_port = argv2;
      int udp_port = argv3;
      printf("[DataLCan] Connect To TCP, IP: %s, PORT[TCP UDP]: [%d %d]\n", ip, tcp_port, udp_port);

      if (is_reset) reset_net(ip, tcp_port, udp_port);
      connect_to_tcp(ip, tcp_port, baud);

    } else if (connect_type == 2) {
      char* ip = argv1;
      int tcp_port = argv2;
      int udp_port = argv3;
      printf("[DataLCan] Connect To UDP, IP: %s, PORT[TCP UDP]: [%d %d]\n", ip, tcp_port, udp_port);

      if (is_reset) reset_net(ip, tcp_port, udp_port);
      connect_to_udp(ip, udp_port, baud);

    } else if (connect_type == 3) {
      char* com = argv1;
      int baud = argv2;
      printf("[DataLCan] Connect To USB, COM: %s, Baud: %d\n", com, baud);

      connect_to_usb(com, baud);
      if (is_reset) into_usb_pm();
    } else {
      is_error_ = 1;
    }
  }

  ~DataLinkApiCan(void) {
    if (socket_fp_ != NULL) {
      socket_fp_->close_port();
      delete socket_fp_;
    }
    if (utcc_client_ != NULL) delete utcc_client_;
    if (utcc_decode_ != NULL) delete utcc_decode_;
  }

  /**
   * Gets the connection status of the DataLink.
   *
   * @return  bool    1: The connection fails.
   *                  0: The connection is successful.
   */
  bool is_error(void) { return is_error_; }

  void close(void) { return socket_fp_->close_port(); }

  /**
   * Clears received cached data.
   */
  void flush(void) { socket_fp_->flush(); }

  /**
     * Send data, Data is transmitted to CAN through TCP/UDP/USB in specific format.
     * Format: 0xAA(uint8_t) + CAN_ID(uint16_t) + CAN_LEN(uint8_t) + CAN_DATA(uint8_t*CAN_LEN) + MODBUS_CRC(uint16_t)
     *
     * @return  int     0: Successful
                       -1: Fails
     */
  int write(can_stream_t* can_stream) {
    tx_stream.data[0] = 0xAA;
    HexData::int16_to_hex_big(can_stream->id, &tx_stream.data[1]);
    tx_stream.data[3] = can_stream->len;
    memcpy(&tx_stream.data[4], can_stream->data, can_stream->len);
    tx_stream.len = 4 + can_stream->len + 2;

    uint16_t crc = Crc::modbus(tx_stream.data, tx_stream.len - 2);
    tx_stream.data[tx_stream.len - 2] = crc & 0xFF;
    tx_stream.data[tx_stream.len - 1] = (crc >> 8) & 0xFF;

    int ret = socket_fp_->write_frame(&tx_stream);
    return ret;
  }

  /**
   * Receiving data, Receives data from CAN in specific format.
   * Format: 0xAA(uint8_t) + CAN_ID(uint16_t) + CAN_LEN(uint8_t) + CAN_DATA(uint8_t*CAN_LEN) + MODBUS_CRC(uint16_t)
   *
   * @param   float  timeout_s  Block time (unit: second).
   *                            If set to 0, the system blocks for a long time until data is received.
   *
   * @return  int               0: data is received
   *                           -1: No data is received
   */
  int read(can_stream_t* can_stream, float timeout_s = 0) {
    while (1) {
      int ret = socket_fp_->read_frame(&rx_stream, timeout_s);
      if (ret == -1) return -1;

      uint16_t crc = Crc::modbus(rx_stream.data, rx_stream.len - 2);
      uint16_t crc2 = (rx_stream.data[rx_stream.len - 2] & 0xFF) + ((rx_stream.data[rx_stream.len - 1] & 0xFF) << 8);
      if (crc != crc2) {
        printf("[DataLCan] Error, The CRC check of received data is incorrect.\n");
        continue;
      }

      can_stream->id = HexData::hex_to_int16_big(&rx_stream.data[1]);
      can_stream->len = rx_stream.data[3];
      memcpy(can_stream->data, &rx_stream.data[4], can_stream->len);
      return 0;
    }
  }

 private:
  bool is_error_ = false;
  UtccClient* utcc_client_ = NULL;
  UtccDecode* utcc_decode_ = NULL;
  Socket* socket_fp_ = NULL;
  serial_stream_t tx_stream;
  serial_stream_t rx_stream;

  void connect_to_tcp(char* ip, int port, int baud) {
    utcc_decode_ = new UtccDecode(0xAA, 0x55, 128);
    socket_fp_ = new SocketTcp(ip, port, 16, utcc_decode_, 125, 45);
    if (socket_fp_->is_error()) {
      printf("[DataLCan] Error: SocketTcp, ip:%s, port:%d\n", ip, port);
      is_error_ = true;
      return;
    }

    socket_fp_->flush();
    utcc_client_ = new UtccClient(socket_fp_);
    int ret = utcc_client_->connect_device(baud);
    if (ret != 0) {
      printf("[DataLCan] Error: connect_net_module %d\n", ret);
      is_error_ = true;
    }
  }

  void connect_to_udp(char* ip, int port, int baud) {
    socket_fp_ = new SocketUdp(ip, port, 16, NULL, 125, 45);
    if (socket_fp_->is_error()) {
      printf("[DataLCan] Error: SocketUdp, ip:%s, port:%d\n", ip, port);
      is_error_ = true;
      return;
    }

    socket_fp_->flush();
    utcc_client_ = new UtccClient(socket_fp_);
    int ret = utcc_client_->connect_device(baud);
    if (ret != 0) {
      printf("[DataLCan] Error: connect_net_module %d\n", ret);
      is_error_ = true;
    }
  }

  void connect_to_usb(char* com, int baud) {
    utcc_decode_ = new UtccDecode(0xAA, 0x55, 128);
    socket_fp_ = new SocketSerial(com, baud, 16, utcc_decode_, 125, 45);
    if (socket_fp_->is_error()) {
      printf("[DataLCan] Error: SocketSerial, com:%s, baud:%d\n", com, baud);
      is_error_ = true;
      return;
    }

    socket_fp_->flush();
  }

  void into_usb_pm(void) {
    serial_stream_t data;
    memcpy(data.data, "# INTO-USB-PM\n", 14);
    data.len = 14;
    socket_fp_->write_frame(&data);
  }

  void reset_net(char ip[], int tcp_port, int udp_port) {
    utcc_t tx_utcc;
    tx_utcc.head = 0xAA;
    tx_utcc.id = 0x0055;
    tx_utcc.state = 0;
    tx_utcc.len = 0x08;
    tx_utcc.rw = 0;
    tx_utcc.cmd = 0x7F;
    tx_utcc.data[0] = 0x7F;
    tx_utcc.data[1] = 0x7F;
    tx_utcc.data[2] = 0x7F;
    tx_utcc.data[3] = 0x7F;
    tx_utcc.data[4] = 0x7F;
    tx_utcc.data[5] = 0x7F;
    tx_utcc.data[6] = 0x7F;
    serial_stream_t tx_stream_;
    tx_utcc.pack(&tx_stream_);

    printf("[DataLCan] Reset Net Step1: connect to tcp\n");
    int fp = LinuxCvl::socket_init((char*)" ", 0, 0);
    if (fp != -1) {
      struct sockaddr_in server_addr;
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(tcp_port);
      inet_aton(ip, &server_addr.sin_addr);
      int ret = connect(fp, (struct sockaddr*)&server_addr, sizeof(server_addr));
      if (ret == 0) {
        LinuxCvl::socket_send_data(fp, tx_stream_.data, tx_stream_.len);
      }
    }
    sleep(0.1);

    printf("[DataLCan] Reset Net Step2: connect to udp\n");
    fp = LinuxCvl::socketudp_init((char*)" ", 0, 0);
    if (fp > -1) {
      struct sockaddr_in addr_ = LinuxCvl::get_sockaddr(ip, udp_port);
      int ret = LinuxCvl::socketudp_send_data(fp, addr_, tx_stream_.data, tx_stream_.len);
    }
    sleep(3);
    is_error_ = 0;
  }
};

#endif
