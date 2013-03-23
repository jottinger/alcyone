#ifndef __MCP23008_H__
#define __MCP23008_H__ 1

enum MODE { INPUT=0, OUTPUT=1 };

class MCP23008 {
private:
  int address;
protected:
  void initialize();
public:
  MCP23008(int _address=0x00) {
    // offset by 0x20 for the i2c address
    address=_address | 0x20;
    initialize();
  }
  void modeAll(MODE mode);
  
};

#endif