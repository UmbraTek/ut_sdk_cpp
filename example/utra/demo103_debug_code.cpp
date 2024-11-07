/* Copyright 2021 UmbraTek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "utapi/utra/utra_api_tcp.h"

/**
 * run command: ./utra/demo103_debug_code -i 192.168.1.xxx
 * if (code == 102) set_errcode(ERROR_CODE::DRV_SPI, 9002);
 * if (code == 107) set_errcode(ERROR_CODE::BATT_LOW, 9007);
 * if (code == 108) set_errcode(ERROR_CODE::ENCODER_DIF, 9008);
 * if (code == 109) set_errcode(ERROR_CODE::ENCODER_ERR, 9009);
 * if (code == 110) set_errcode(ERROR_CODE::ENCODER_REG, 9010);

 * if (code == 116) set_errcode(ERROR_CODE::ENC_FUSION1, 9016);
 * if (code == 117) set_errcode(ERROR_CODE::ENC_FUSION2, 9017);
 * if (code == 118) set_errcode(ERROR_CODE::MU_SPI, 9018);
 * if (code == 119) set_errcode(ERROR_CODE::MU_STATUS, 9019);

 * if (code == 121) set_errcode(ERROR_CODE::DRV_FAULT, 9021);
 * if (code == 122) set_errcode(ERROR_CODE::MUL_CHECK, 9022);
 * if (code == 123) set_errcode(ERROR_CODE::TEMP_OVER, 9023);
 * if (code == 124) set_errcode(ERROR_CODE::VBUS_OVER, 9024);

 * if (code == 131) set_errcode(ERROR_CODE::POS_FOLLOWING, 9031);
 * if (code == 132) set_errcode(ERROR_CODE::GVEL_OVER, 9032);
 * if (code == 133) set_errcode(ERROR_CODE::POWER_OVER, 9033);
 * if (code == 134) set_errcode(ERROR_CODE::SPOS_OVER, 9034);
 * if (code == 135) set_errcode(ERROR_CODE::SVEL_OVER, 9035);
 * if (code == 136) set_errcode(ERROR_CODE::STAU_OVER, 9036);
 * if (code == 137) set_errcode(ERROR_CODE::POS_LIMIT, 9037);
 * if (code == 138) set_errcode(ERROR_CODE::TAU_LIMIT, 9038);
 * if (code == 139) set_errcode(ERROR_CODE::POS_FOLLOWING2, 9039);

 * if (code == 140) set_errcode(ERROR_CODE::ADDR, 9040);
 * if (code == 141) set_errcode(ERROR_CODE::VALUE_OVER, 9041);
 * if (code == 142) set_errcode(ERROR_CODE::IWDG_UBOT, 9042);
 * if (code == 151) set_errcode(ERROR_CODE::POS_ERR_Z2X2, 9051);
 */
int main(int argc, char *argv[]) {
  int opt = 0;
  char ip[64];
  std::string port_name = "192.168.1.14";
  while ((opt = getopt(argc, argv, "i:m:")) != -1) {
    switch (opt) {
      case 'i':
        strcpy(ip, std::string(optarg).data());
        break;
    }
  }

  UtraApiTcp *ubot = new UtraApiTcp(ip);
  int ret = 0;

  ret = ubot->set_debug_code(6, 151);
  printf("set_debug_code   : %d\n", ret);

  return 0;
}
