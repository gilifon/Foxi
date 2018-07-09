#include "foxi_config.h"
#include "cc1150.h"

CC1150 cc1150;
bool rftSetup; //is the RF or the RFT header send to the CC1150?

void Foxi::setup(void) {
  cc1150.setup();
}

void Foxi::begin(void) {
  cc1150.begin();
}

void Foxi::end(void) {
  cc1150.end();
}

void Foxi::sendCommand(byte* data, int length, int repetitions) {

  setupRF();
  cc1150.sendSerialData(data, length, FOXI_RF_Delay, repetitions );
  resetGDO();
}

void Foxi::sendMessage() {

  setupRF();
  cc1150.sendMessage();
  resetGDO();
}

void Foxi::setupRF() {
  cc1150.reset();
  cc1150.writeRegister(CC1150_IOCFG0, CC1150_DEFVAL_IOCFG1);
  cc1150.writeRegister(CC1150_MDMCFG4 , FOXI_RF_MDMCFG4);
  cc1150.writeRegister(CC1150_MDMCFG3 , FOXI_RF_MDMCFG3);
  cc1150.writeRegister(CC1150_MDMCFG2 , FOXI_RF_MDMCFG2);
  cc1150.writeRegister(CC1150_MDMCFG1 , FOXI_RF_MDMCFG1);
  cc1150.writeRegister(CC1150_MDMCFG0 , FOXI_RF_MDMCFG0);
  cc1150.writeRegister(CC1150_CHANNR, FOXI_CHANNR);
  cc1150.writeRegister(CC1150_DEVIATN, FOXI_RF_DEVIATN);
  setupDefaultFOXIRegisters();
  cc1150.writeRegister(CC1150_IOCFG0, FOXI_IOCFG0);
  cc1150.writeRegister(CC1150_IOCFG1, FOXI_IOCFG1);

  cc1150.transmit();

  // added extra duplicate (?) code
  cc1150.idle();
  cc1150.idle();
  cc1150.transmit();
  rftSetup = false;
}

void Foxi::setupDefaultFOXIRegisters() {
  cc1150.writeRegister(CC1150_FREQ2 , FOXI_FREQ2);
  cc1150.writeRegister(CC1150_FREQ1 , FOXI_FREQ1);
  cc1150.writeRegister(CC1150_FREQ0 , FOXI_FREQ0);
  cc1150.writeRegister(CC1150_FREND0, FOXI_FREND0);
  cc1150.writeRegister(CC1150_MCSM0, FOXI_MCSM0);
  cc1150.writeRegister(CC1150_FSCAL3, FOXI_FSCAL3);
  cc1150.writeRegister(CC1150_FSCAL2, FOXI_FSCAL2);
  cc1150.writeRegister(CC1150_FSCAL1, FOXI_FSCAL1);
  cc1150.writeRegister(CC1150_FSCAL0, FOXI_FSCAL0);
  cc1150.writeRegister(CC1150_FSTEST, FOXI_FSTEST);
  cc1150.writeRegister(CC1150_TEST2, FOXI_TEST2);
  cc1150.writeRegister(CC1150_TEST1, FOXI_TEST1);
  cc1150.writeRegister(CC1150_TEST0, FOXI_TEST0);
  cc1150.writeRegister(CC1150_PKTCTRL0, FOXI_PKTCTRL0);
  cc1150.writeRegister(CC1150_ADDR, FOXI_ADDR);
  cc1150.writeRegister(CC1150_PKTLEN, FOXI_PKTLEN);
  cc1150.writeBurstRegister(CC1150_PATABLE_BURST, (unsigned int*)FOXIPaTable, 8);
  cc1150.idle();
  cc1150.idle();
  cc1150.idle();
}

void Foxi::resetGDO() {
  cc1150.idle();
  cc1150.writeRegister(CC1150_IOCFG0, CC1150_DEFVAL_IOCFG1);
  cc1150.writeRegister(CC1150_IOCFG1, CC1150_DEFVAL_IOCFG1);
  cc1150.idle();
  cc1150.powerdown();
}
