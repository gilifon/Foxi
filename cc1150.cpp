#include "cc1150.h"
#include "digitalWriteFast.h"

void CC1150::send_command(unsigned int command) {
  select();
  SPI.transfer(command);
  deselect();
}
void CC1150::writeRegister(unsigned int address, unsigned int data) {
  select();
  SPI.transfer(address);
  SPI.transfer(data);
  deselect();
}
void CC1150::writeBurstRegister(unsigned int address, unsigned int *data, unsigned int length) {
  uint8_t i;
  select();
  SPI.transfer(address);
  for (i = 0; i < length; i++) {
    SPI.transfer(data[i]);
  }
  deselect();
}
unsigned int CC1150::readRegister(unsigned int address, unsigned int registerType) {
  unsigned int result;
  unsigned int addr = address | registerType;
  select();
  SPI.transfer(addr);
  result = SPI.transfer(0x00);
  deselect();
  return result;
}
void CC1150::transmit(void) {
  send_command(CC1150_STX);
}
void CC1150::idle(void) {
  send_command(CC1150_SIDLE);
}
void CC1150::powerdown(void) {
  send_command(CC1150_SPWD);
}
void CC1150::reset(void) {
  select();
  SPI.transfer(CC1150_SRES);
  waitMiso();
  deselect();
}
inline void CC1150::select(void) {
  digitalWrite(SS, LOW);
}
inline void CC1150::deselect(void) {
  digitalWrite(SS, HIGH);
}
inline void CC1150::waitMiso(void) {
  while (digitalRead(SPI_MISO) == HIGH);
}
void CC1150::begin(void) {
  SPI.begin();
}
void CC1150::end(void) {
  SPI.end();
}
void CC1150::setup(void) {
  delay(100); // wait for the CC1150 to power-up (
}
void CC1150::sendSerialData(byte* data, int numberOfBits, int delay, int repetitions) {
  repetitionCounter = repetitions;
  dataIndexBits = 0;
  mask = 10000000; //reset mask
  bufferIndex = 0;
  dataLengthBits = numberOfBits;
  delayAfterSerialWrite = delay;
  dataBuffer = data;
  // listen for clock (interrupt) on MISO
  enableMisoInterrupt();
  while (dataIndexBits < dataLengthBits * repetitionCounter) {
    // wait for the next interrupt to clock out remaining data
  }
  disableMisoInterrupt();
  dataBuffer = NULL;
}
uint8_t currentGDO0;

void CC1150::ISR_MISO() {
  if (dataIndexBits < dataLengthBits * repetitionCounter) { // check if there is any more data to send
    byte bufferValue = dataBuffer[bufferIndex];
    
    if (bufferValue & mask) {
      if (currentGDO0 != HIGH) {
        digitalWriteFast2(GDO0, HIGH);
        currentGDO0 = HIGH;
      }
    }
    else {
      if (currentGDO0 != LOW) {
        digitalWriteFast2(GDO0, LOW);
        currentGDO0 = LOW;
      }
    }

    mask >>= 1;

    if (mask == 0)
    {
      mask = 10000000; //reset mask
      bufferIndex = (bufferIndex + 1) % (dataLengthBits / 8); //goto next byte in the data-array
    }

    dataIndexBits++; //increase bits send
  }
}
void CC1150::enableMisoInterrupt() {
  pinMode(GDO0, OUTPUT);        // sets the digital pin as output

  currentGDO0 = LOW;
  digitalWriteFast2(GDO0, LOW);

  generateFakeInterrupts();
}
void CC1150::generateFakeInterrupts() {
  int previousMiso = -1;
  int currentMiso = -1;

  noInterrupts();

  ISR_MISO(); //queue the first bit, because the code below waits for the first RISING edge to queue the next

  do
  {
    currentMiso = digitalReadFast2(SPI_MISO);

    if (currentMiso != previousMiso)
    {
      //wait for Miso to be high, then the RISING edge has taken place
      //and we can clock in new data
      if (currentMiso == HIGH)
      {
        if (delayAfterSerialWrite > 0)
        {
          // extra delay to make the RISING edge fall nicely in the middle of the data
          delayMicroseconds(delayAfterSerialWrite);
        }
        ISR_MISO();
      }
      previousMiso = currentMiso;
    }
  }
  while (dataIndexBits < dataLengthBits * repetitionCounter);
  // wait for the last clock to become high so the last queued bit is also sent
  while (digitalReadFast2(SPI_MISO) == LOW);
  select();  // disable the transmission of new data (caller should issue a command to the CC1150 after transmission of data)
  interrupts();
}
void CC1150::disableMisoInterrupt() {
  pinMode(GDO0, INPUT);        // sets the digital pin as output
}
