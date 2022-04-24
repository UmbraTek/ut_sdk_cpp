/* Copyright 2022 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/datalink/datalink_api_can.h"

void print_help(void) {
  printf("Select the communication interface\n");
  printf("./demo2_datalink_can arg1\n");
  printf("    [arg1] 1: DataLink TCP To CAN\n");
  printf("           2: DataLink UDP To CAN\n");
  printf("           3: DataLink USB To CAN\n");
}

int main(int argc, char *argv[]) {
  // This example tests the EtherNet to CAN module, sends the received CAN data back.

  if (argc != 2) {
    print_help();
    return 0;
  }

  char ip[] = "192.168.1.166";
  char com[] = "/dev/ttyACM0";

  DataLinkApiCan *datalink = NULL;

  if (atoi(argv[1]) == 1) {
    datalink = new DataLinkApiCan(1, ip, 6001, 5001, 1, 1000000);
    if (datalink->is_error()) return 0;
  } else if (atoi(argv[1]) == 2) {
    datalink = new DataLinkApiCan(2, ip, 6001, 5001, 1, 1000000);
    if (datalink->is_error()) return 0;
  } else if (atoi(argv[1]) == 3) {
    datalink = new DataLinkApiCan(3, com, 921600, 0, 1);
    if (datalink->is_error()) return 0;
  } else {
    print_help();
    return 0;
  }

  can_stream_t can_stream;
  while (1) {
    int ret = datalink->read(&can_stream);
    if (ret != -1) {
      printf("recv: id:%d len:%d ", can_stream.id, can_stream.len);
      Print::hex("data: ", can_stream.data, can_stream.len);
      datalink->write(&can_stream);
    }
  }
}
