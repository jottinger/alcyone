#ifndef __SERIAL_H__
#define __SERIAL_H__ 1

#include <string>

class SerialDevice {
private:
  int fd;
  int baudRate;
  std::string device;
protected:
public:
  SerialDevice(std::string _device="/dev/ttyAMA0", int _baudRate=38400);
};

#endif
