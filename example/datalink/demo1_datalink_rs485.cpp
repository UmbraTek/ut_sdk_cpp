/* Copyright 2022 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/datalink/datalink_api_rs485.h"

void print_help(void) {
  printf("Select the communication interface\n");
  printf("./demo1_datalink_rs485 arg1\n");
  printf("    [arg1] 1: DataLink TCP To RS485\n");
  printf("           2: DataLink UDP To RS485\n");
  printf("           3: DataLink USB To RS485\n");
}

int main(int argc, char *argv[]) {
  // This example tests the EtherNet to RS485 module, sends the received RS485 data back.

  if (argc != 2) {
    print_help();
    return 0;
  }

  char ip[] = "192.168.1.168";
  char com[] = "/dev/ttyACM0";

  DataLinkApiRs485 *datalink = NULL;

  if (atoi(argv[1]) == 1) {
    datalink = new DataLinkApiRs485(1, ip, 6001, 5001, 1, 921600);
    if (datalink->is_error()) return 0;
  } else if (atoi(argv[1]) == 2) {
    datalink = new DataLinkApiRs485(2, ip, 6001, 5001, 1, 921600);
    if (datalink->is_error()) return 0;
  } else if (atoi(argv[1]) == 3) {
    datalink = new DataLinkApiRs485(3, com, 921600, 0, 1);
    if (datalink->is_error()) return 0;
  } else {
    print_help();
    return 0;
  }

  serial_stream_t data;
  while (1) {
    int ret = datalink->read(&data);
    if (ret != -1) {
      Print::hex("recv: ", data.data, data.len);
      datalink->write(&data);
    }
  }
}
