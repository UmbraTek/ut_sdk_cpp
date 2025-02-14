/* Copyright 2021 Umbratek Inc. All Rights Reserved.
 *
 * Licensed
 *
 * Author: Jimy Zhang <jimy.zhang@umbratek.com> <jimy92@163.com>
 ============================================================================*/
#include "socket_serial.h"

#include "print.h"

SocketSerial::SocketSerial(const char *port, int baud, int rxque_max, SerialDecode *decode, int rxlen_max, int priority) {
  int ret = init_serial(port, baud);
  if (ret != 0) {
    printf("[SockeSer] Error serial init failed, ret = %d\n", ret);
    is_error_ = true;
    return;
  }

  is_error_ = false;
  rx_que_ = new BlockDeque<serial_stream_t>(rxque_max);
  decode_ = decode;
  rxlen_max_ = rxlen_max;
  if (decode_ == NULL)
    is_decode_ = false;
  else
    is_decode_ = true;

  flush();
  recv_task_ =
      new RtPeriodicMemberFun<SocketSerial>(0.00003, "recv_task", 1024 * 1024, priority, &SocketSerial::recv_proc, this);
  recv_task_->start();
}

SocketSerial::~SocketSerial(void) {
  is_error_ = true;
  if (recv_task_ != NULL) {
    close_port();
    recv_task_->stop();
    delete recv_task_;
  }
  if (rx_que_ != NULL) delete rx_que_;
}

bool SocketSerial::is_ok(void) { return !is_error_; }
bool SocketSerial::is_error(void) { return is_error_; }

void SocketSerial::close_port(void) {
  is_error_ = true;
  close(fp_);
}

void SocketSerial::flush(bool is_decode) {
  is_decode_ = is_decode;
  rx_que_->flush();
  if (decode_ != NULL && is_decode_) decode_->flush();
}

void SocketSerial::flush(int slave_id, int master_id, int rxlen_max) {
  is_decode_ = true;
  rx_que_->flush();
  if (decode_ != NULL) decode_->flush(slave_id, master_id, rxlen_max);
}

int SocketSerial::write_frame(serial_stream_t *data) {
  if (is_error_) return -1;
  if (write(fp_, data->data, data->len) != data->len) return -1;
  // Print::hex("[SockSeri] write: ", data->data, data->len);
  return 0;
}

int SocketSerial::read_frame(serial_stream_t *data, float timeout_s) {
  if (is_error_) return -1;
  return rx_que_->pop(data, timeout_s);
}

void SocketSerial::recv_proc(void) {
  while (is_error_ == false) {
    bzero(rx_stream_.data, rxlen_max_);
    rx_stream_.len = read(fp_, rx_stream_.data, rxlen_max_);
    if (is_error_) return;
    if (rx_stream_.len >= 0) {
      if (decode_ != NULL && is_decode_) {
        decode_->parse_put(rx_stream_.data, rx_stream_.len, rx_que_);
      } else {
        rx_que_->push_back(&rx_stream_);
      }
      // Print::hex("[SockSeri] recv: ", rx_stream_.data, rx_stream_.len);
    }
  }
}

#if 0
#include <fcntl.h>
#include <termios.h>

int SocketSerial::init_serial(const char *port, int baud) {
  fp_ = open((const char *)port, O_RDWR | O_NOCTTY | O_NDELAY);
  if (-1 == fp_) return -1;

  int flags = fcntl(fp_, F_GETFL, 0);
  flags &= ~O_NONBLOCK;
  if (fcntl(fp_, F_SETFL, flags) < 0) {
    printf("[SockeSer] fcntl failed.\n");
    return -1;
  }

  speed_t speed = B115200;
  bool is_non_standard_baus = false;
  switch (baud) {
    case 110:
      speed = B110;
      break;
    case 300:
      speed = B300;
      break;
    case 600:
      speed = B600;
      break;
    case 1200:
      speed = B1200;
      break;
    case 2400:
      speed = B2400;
      break;
    case 4800:
      speed = B4800;
      break;
    case 9600:
      speed = B9600;
      break;
    case 19200:
      speed = B19200;
      break;
    case 38400:
      speed = B38400;
      break;
    case 57600:
      speed = B57600;
      break;
    case 115200:
      speed = B115200;
      break;
    case 230400:
      speed = B230400;
      break;
    case 460800:
      speed = B460800;
      break;
    case 921600:
      speed = B921600;
      break;
    case 1000000:
      speed = B1000000;
      break;
    case 2500000:
      speed = B2500000;
    case 3000000:
      speed = B3000000;
    case 3500000:
      speed = B3500000;
    case 4000000:
      speed = B4000000;
      break;
    default:
      speed = B38400;
      is_non_standard_baus = true;
      break;
  }

  struct termios options;
  struct termios oldtio;
  bzero(&options, sizeof(options));
  bzero(&oldtio, sizeof(oldtio));

  int ret = tcgetattr(fp_, &oldtio);
  if (ret != 0) return -2;

  options.c_cflag |= CLOCAL | CREAD;
  options.c_cflag &= ~CSIZE;

  //  set tty speed
  if (0 != cfsetispeed(&options, speed)) return -3;
  if (0 != cfsetospeed(&options, speed)) return -4;
  options.c_cflag |= CS8;      // data bits 8
  options.c_cflag &= ~PARENB;  // parity = N , Clear parity enable
  options.c_iflag &= ~INPCK;   // parity = N , Enable parity checking
  options.c_cflag &= ~CSTOPB;  // stop bits=1

  int hardflow = 0;
  if (hardflow) {
    options.c_cflag |= CRTSCTS;
  } else {
    options.c_cflag &= ~CRTSCTS;
  }

  options.c_cc[VTIME] = 100;  // Time-out value (tenths of a second) [!ICANON].
  options.c_cc[VMIN] = 1;     // Minimum number of bytes read at once [!ICANON].
  tcflush(fp_, TCIFLUSH);
  ret = tcsetattr(fp_, TCSANOW, &options);
  if (ret != 0) return -5;

  return 0;
}

#else

#include <asm/termbits.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int SocketSerial::init_serial(const char *port, int baud) {
  fp_ = open((const char *)port, O_RDWR | O_NOCTTY | O_NDELAY);
  if (-1 == fp_) return -1;

  struct termios2 tio {};
  if (0 != ioctl(fp_, TCGETS2, &tio)) {  // Read the configuration
    close(fp_);
    return -2;
  }

  tio.c_iflag &= ~(IGNBRK);  // Ignore break condition
  tio.c_iflag &= ~(BRKINT);  // Send a SIGINT when a break condition is detected
  tio.c_iflag &= ~(PARMRK);  // Mark parity errors
  tio.c_iflag &= ~(ISTRIP);  // Strip parity bits
  tio.c_iflag &= ~(INLCR);   // Map NL to CR
  tio.c_iflag &= ~(IGNCR);   // Ignore CR
  tio.c_iflag &= ~(ICRNL);   // Map CR to NL
  tio.c_iflag &= ~(IXON);    // Enable software flow control (outgoing)
  // tio.c_iflag |= (INPCK);    // Enable parity check
  tio.c_iflag |= (IGNPAR);  // Ignore parity errors

  tio.c_oflag &= ~OPOST;  // Turn off the output flag

  tio.c_lflag &= ~(ECHO);
  tio.c_lflag &= ~(ECHONL);
  tio.c_lflag &= ~(ICANON);  // Enable canonical input (else raw)
  tio.c_lflag &= ~(ISIG);
  tio.c_lflag &= ~(IEXTEN);  // Enable extended functions

  tio.c_cflag &= ~(CBAUD);
  tio.c_cflag |= (BOTHER);
  tio.c_cflag |= CLOCAL | CREAD;  // Local connection and acceptance enable
  tio.c_cflag &= ~CSIZE;          // Clear the data bit setting
  tio.c_cflag |= CS8;             // data bits 8
  tio.c_cflag &= ~PARENB;         // parity = N , Clear parity enable
  tio.c_cflag &= ~CSTOPB;         // stop bits=1
  tio.c_cflag &= ~CRTSCTS;        // Hardware flow control is disable

  tio.c_ispeed = baud;
  tio.c_ospeed = baud;
  tio.c_cc[VMIN] = 100;  // Specifies the amount of time, in n*100ms, to wait to read the first character
  tio.c_cc[VTIME] = 1;   // Specifies the minimum number of characters to read
  if (0 != ioctl(fp_, TCSETS2, &tio)) return -3;

  return 0;
}
#endif

// g++ linux/port/serial.cpp common/crc16.cpp linux/thread.cc -o serial123 -I./ -lpthread
/*
int main(int argc, char *argv[]) {
  SocketSerial serial_port("/dev/ttyUSB0", 115200, 20, 32);  //

  serial_stream_t rx_data;
  while (true) {
    int ret = serial_port.read_frame(&rx_data);
    // int ret;
    printf("rx:%d, ret:%d\n", rx_data.len, ret);
    for (int i = 0; i < rx_data.len; i++) printf("0x%x ", rx_data.data[i]);
    printf("\n");

    serial_port.write_frame(&rx_data);
  }
}*/
