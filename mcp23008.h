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
protected:
    void initialize();
    void writeRegister(MCP_REGISTER register, int bit, int state);
public:
    MCP23008(int _address=0x00) {
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