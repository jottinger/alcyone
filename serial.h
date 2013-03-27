/*
    Copyright 2012- by Joseph B. Ottinger.

    This file is part of Alcyone.

    Alcyone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Alcyone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Alcyone.  If not, see <http://www.gnu.org/licenses/>.
*/

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
  void send(unsigned char value);
  unsigned char read();
};

#endif
