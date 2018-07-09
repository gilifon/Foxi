#ifndef _FOXI_H
#define _FOXI_H

#include <Arduino.h>
#include <SPI.h>

// Fc/396.728515625=FREQ2 FREQ1 FREQ0
//433.000 = 1091426
//433.150 = 1091804
//433.300 = 1092182

//433.000
#define FOXI_FREQ2 0x10
#define FOXI_FREQ1 0xA7
#define FOXI_FREQ0 0x62

//433.150
//#define FOXI_FREQ2 0x10
//#define FOXI_FREQ1 0xA8
//#define FOXI_FREQ0 0xDC

//433.300
//#define FOXI_FREQ2 0x10
//#define FOXI_FREQ1 0xAA
//#define FOXI_FREQ0 0x56

#define FOXI_CHANNR   0x00
#define FOXI_DEVIATN  0x40 //26000000 / 131072 * (8) * 2 ^ 4 = 25,390625 KHz

#define FOXI_FREND0 0x17 //LODIV_BUF_CURRENT_TX = 2, PA_POWER = 7
#define FOXI_MCSM0  0x18
#define FOXI_FSCAL3 0xA9
#define FOXI_FSCAL2 0x2A
#define FOXI_FSCAL1 0x00
#define FOXI_FSCAL0 0x11
#define FOXI_FSTEST 0x59
#define FOXI_TEST2  0x81
#define FOXI_TEST1  0x35
#define FOXI_TEST0  0x0B
#define FOXI_PKTCTRL0 0x12
#define FOXI_ADDR 0x00
#define FOXI_PKTLEN 0xFF
#define FOXI_IOCFG0 0x2D
#define FOXI_IOCFG1 0x0B
#define FOXI_RF_MDMCFG4 0x08
#define FOXI_RF_MDMCFG3 0x40
#define FOXI_RF_MDMCFG2 0x00
#define FOXI_RF_MDMCFG1 0x22
#define FOXI_RF_MDMCFG0 0xF8
#define FOXI_RF_DEVIATN 0x10
#define CC1150_DEFVAL_IOCFG1  0x2E
#define CC1150_DEFVAL_IOCFG0  0x06
#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))
const unsigned int FOXIPaTable[8] = {0x6F, 0x26, 0x2E, 0x8C, 0x87, 0xCD, 0xC7, 0xC0};
const int FOXI_RF_Delay = 0; //microseconds

class Foxi
{
  public:
    void setup(void);
    void begin(void);
    void end(void);
    void setupRF();
    void setupRFT();
    void resetGDO();
    void sendCommand(byte* data, int length, int repetitions = 1);
    void sendMessage();
  private:
    void setupDefaultFOXIRegisters();
};

#endif //_FOXI_H
