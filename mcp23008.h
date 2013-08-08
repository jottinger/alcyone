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

#ifndef __MCP23008_H__
#define __MCP23008_H__ 1

enum MODE {
    MODE_INPUT=0,
    MODE_OUTPUT=1
};

enum MCP_REGISTER {
    MCP_IODIR=0x00,
    MCP_IPOL=0x01,
    MCP_GPINTEN=0x02,
    MCP_DEFVAL=0x03,
    MCP_INTCON=0x04,
    MCP_IOCON=0x05,
    MCP_GPPU=0x06,
    MCP_INTF=0x07,
    MCP_INTCAP=0x08,
    MCP_GPIO=0x09,
    MCP_OLAT=0x0a
};

inline int decode(int value, int bit) {
    return (value&(1<<bit))>>bit;
}

class MCP23008 {
private:
    int address;
    int fd;
    int lastRead;
    std::recursive_mutex mutex;
protected:
    void initialize();
    void writeRegister(MCP_REGISTER register, int bit, int state);
public:
    MCP23008(int _address=0x00):address(_address|0x20),fd(0),lastRead(0) {
        // offset by 0x20 for the i2c address
        address=_address | 0x20;
        initialize();
    }
    void modeAll(MODE mode);
    int read();
    void writePin(int bit, int state);
    inline int readCached() {
        return lastRead;
    }
    inline int bit(int value, int bit) {
        return decode(value, bit);
    }
    void pinMode(int pin, MODE mode);
    int readPin(int pin);
};

#endif
