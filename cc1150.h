// based on code written by @CyberGibbons
// https://github.com/cybergibbons/Response_CC1150

#ifndef _CC1150_H
#define _CC1150_H

#include <Arduino.h>
#include <SPI.h>

#define SPI_SS   10
#define SPI_MOSI 11
#define SPI_MISO 12
#define SPI_SCK  13
#define GDO0	 2  //9(Pro Mini), 2(Nano)

#define CC1150_IOCFG1       0x01
#define CC1150_IOCFG0       0x02
#define CC1150_FIFOTHR      0x03
#define CC1150_SYNC1        0x04
#define CC1150_SYNC0        0x05
#define CC1150_PKTLEN       0x06
#define CC1150_PKTCTRL0     0x08
#define CC1150_ADDR			    0x09
#define CC1150_CHANNR       0x0A
#define CC1150_FREQ2        0x0D
#define CC1150_FREQ1        0x0E
#define CC1150_FREQ0        0x0F
#define CC1150_MDMCFG4      0x10
#define CC1150_MDMCFG3      0x11
#define CC1150_MDMCFG2      0x12
#define CC1150_MDMCFG1      0x13
#define CC1150_MDMCFG0      0x14
#define CC1150_DEVIATN      0x15
#define CC1150_MCSM1        0x17
#define CC1150_MCSM0        0x18
#define CC1150_FREND0       0x22
#define CC1150_FSCAL3       0x23
#define CC1150_FSCAL2       0x24
#define CC1150_FSCAL1       0x25
#define CC1150_FSCAL0       0x26
#define CC1150_FSTEST       0x29
#define CC1150_PTEST        0x2A
#define CC1150_TEST2        0x2C
#define CC1150_TEST1        0x2D
#define CC1150_TEST0        0x2E
#define CC1150_SRES         0x30
#define CC1150_SFSTXON      0x31
#define CC1150_SXOFF        0x32
#define CC1150_SCAL         0x33
#define CC1150_STX          0x35
#define CC1150_SIDLE        0x36
#define CC1150_SPWD         0x39
#define CC1150_SNOP         0x3D
#define CC1150_PARTNUM          0x30
#define CC1150_VERSION          0x31
#define CC1150_MARCSTATE        0x35
#define CC1150_PKTSTATUS        0x38
#define CC1150_VCO_VC_DAC       0x39
#define CC1150_TXBYTES          0x3A
#define CC1150_PATABLE          0x3E
#define CC1150_PATABLE_BURST    CC1150_PATABLE + 0x40
#define WRITE_BURST             0x40
#define READ_SINGLE             0x80
#define READ_BURST              0xC0
#define CC1150_CONFIG_REGISTER  READ_SINGLE
#define CC1150_STATUS_REGISTER  READ_BURST

#define CC1150_FREQ2_DEFAULT    0x1E
#define CC1150_FREQ1_DEFAULT    0xC4
#define CC1150_FREQ0_DEFAULT    0xEC

typedef void (*voidFuncPtr)(void);

class CC1150
{
  public:
    // general setup and loop functions
    void setup(void);
    void begin(void);
    void end(void);

    // manipulate registers
    void writeRegister(unsigned int address, unsigned int data);
    void writeBurstRegister(unsigned int address, unsigned int *data, unsigned int length);
    unsigned int readRegister(unsigned int address, unsigned int registerType);

    // custom commands
    void send_command(unsigned int command);
    void sendSerialData(byte* data, int numberOfBits, int delay, int repetitions = 1);
    void sendMessage();

    // commands
    void transmit(void);
    void idle(void);
    void powerdown(void);
    void reset(void);

  private:
    // SPI helper functions
    void waitMiso(void);
    void select(void);
    void deselect(void);
    void beep(bool isTone);
    void SendLetter(String s);
    void Dit(void);
    void Dat(void);

    // functions to send serial data
    void Flip(bool isTone);
    inline void enableMisoInterrupt(void);
    void generateFakeInterrupts(void);
    inline void disableMisoInterrupt(void);

    // local variables
    int dataLengthBits;
    int delayAfterSerialWrite; //wait X microseconds (us) after changing GDO0
    byte* dataBuffer;
    volatile int  dataIndexBits;
    volatile byte mask;
    volatile int  bufferIndex;
    volatile int repetitionCounter;
};

#endif //_CC1150_H
