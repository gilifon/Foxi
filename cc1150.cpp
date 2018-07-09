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

int i = 0;
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

void CC1150::sendMessage() {
  i = 0;
  enableMisoInterrupt();
}

uint8_t currentGDO0;
void CC1150::Flip(bool isTone) {
  if (isTone)
  {
    if (currentGDO0 == LOW && i % 8 < 7) {

    }
    else if (currentGDO0 == LOW && i % 8 == 7) {
      digitalWriteFast2(GDO0, HIGH);
      currentGDO0 = HIGH;
    }
    else if (currentGDO0 == HIGH && i % 8 < 7) {

    }
    else if (currentGDO0 == HIGH && i % 8 == 7) {
      digitalWriteFast2(GDO0, LOW);
      currentGDO0 = LOW;
    }
  }
  else //noTone
  {
    if (currentGDO0 == HIGH)
    {
      digitalWriteFast2(GDO0, LOW);
      currentGDO0 = LOW;
    }
  }
}
void CC1150::enableMisoInterrupt() {
  pinMode(GDO0, OUTPUT);        // sets the digital pin as output

  currentGDO0 = LOW;
  digitalWriteFast2(GDO0, LOW);

  generateFakeInterrupts();
}
void CC1150::generateFakeInterrupts() {
  noInterrupts();

  Flip(true); //queue the first bit, because the code below waits for the first RISING edge to queue the next
//  SendLetter(" ");
//  SendLetter("C");
//  SendLetter("Q");
//  SendLetter(" ");
//  SendLetter("C");
//  SendLetter("Q");
//  SendLetter(" ");
//  SendLetter("C");
//  SendLetter("Q");
//  SendLetter(" ");
//  SendLetter("4");
//  SendLetter("Z");
//  SendLetter("1");
//  SendLetter("K");
//  SendLetter("D");
//  SendLetter(" ");
//  SendLetter("K");
  
  SendLetter(" ");
  SendLetter("H");
  SendLetter("E");
  SendLetter("L");
  SendLetter("L");
  SendLetter("O");
  SendLetter(" ");
  SendLetter("I");
  SendLetter(" ");
  SendLetter("A");
  SendLetter("M");
  SendLetter(" ");
  SendLetter("F");
  SendLetter("O");
  SendLetter("X");
  SendLetter("1");
  SendLetter(" ");
  SendLetter("1");
  SendLetter(" ");
  SendLetter("1");
  disableMisoInterrupt();
  select();  // disable the transmission of new data (caller should issue a command to the CC1150 after transmission of data)
  interrupts();
}

void CC1150::beep(bool isTone) {
  int previousMiso = -1;
  int currentMiso = -1;
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
        i++;
        Flip(isTone);
      }
      previousMiso = currentMiso;
    }
  }
  while (i < 512);
  // wait for the last clock to become high so the last queued bit is also sent
  while (digitalReadFast2(SPI_MISO) == LOW);
  i = 0;
}

void CC1150::disableMisoInterrupt() {
  pinMode(GDO0, INPUT);        // sets the digital pin as output
}

void CC1150::Dit()
{
  beep(true);
  beep(false);
}

void CC1150::Dat()
{
  beep(true);
  beep(true);
  beep(true);
  beep(false);
}

void CC1150::SendLetter(String letter)
{
  if (letter == "A")
  {
    Dit(); Dat();
  }
  else if (letter == "B")
  {
    Dat(); Dit(); Dit(); Dit();
  }
  else if (letter == "C")
  {
    Dat(); Dit(); Dat(); Dit();
  }
  else if (letter == "D")
  {
    Dat(); Dit(); Dit();
  }
  else if (letter == "E")
  {
    Dit();
  }
  else if (letter == "F")
  {
    Dit(); Dit(); Dat(); Dit();
  }
  else if (letter == "G")
  {
    Dat(); Dat(); Dit();
  }
  else if (letter == "H")
  {
    Dit(); Dit(); Dit(); Dit();
  }
  else if (letter == "I")
  {
    Dit(); Dit();
  }
  else if (letter == "J")
  {
    Dit(); Dat(); Dat(); Dat();
  }
  else if (letter == "K")
  {
    Dat(); Dit(); Dat();
  }
  else if (letter == "L")
  {
    Dit(); Dat(); Dit(); Dit();
  }
  else if (letter == "M")
  {
    Dat(); Dat();
  }
  else if (letter == "N")
  {
    Dat(); Dit();
  }
  else if (letter == "O")
  {
    Dat(); Dat(); Dat();
  }
  else if (letter == "P")
  {
    Dit(); Dat(); Dat(); Dit();
  }
  else if (letter == "Q")
  {
    Dat(); Dat(); Dit(); Dat();
  }
  else if (letter == "R")
  {
    Dit(); Dat(); Dit();
  }
  else if (letter == "S")
  {
    Dit(); Dit(); Dit();
  }
  else if (letter == "T")
  {
    Dat();
  }
  else if (letter == "U")
  {
    Dit(); Dit(); Dat();
  }
  else if (letter == "V")
  {
    Dit(); Dit(); Dit(); Dat();
  }
  else if (letter == "W")
  {
    Dit(); Dat(); Dat();
  }
  else if (letter == "X")
  {
    Dat(); Dit(); Dit(); Dat();
  }
  else if (letter == "Y")
  {
    Dat(); Dit(); Dat(); Dat();
  }
  else if (letter == "Z")
  {
    Dat(); Dat(); Dit(); Dit();
  }
  else if (letter == "0")
  {
    Dat(); Dat(); Dat(); Dat(); Dat();
  }
  else if (letter == "1")
  {
    Dit(); Dat(); Dat(); Dat(); Dat();
  }
  else if (letter == "2")
  {
    Dit(); Dit(); Dat(); Dat(); Dat();
  }
  else if (letter == "3")
  {
    Dit(); Dit(); Dit(); Dat(); Dat();
  }
  else if (letter == "4")
  {
    Dit(); Dit(); Dit(); Dit(); Dat();
  }
  else if (letter == "5")
  {
    Dit(); Dit(); Dit(); Dit(); Dit();
  }
  else if (letter == "6")
  {
    Dat(); Dit(); Dit(); Dit(); Dit();
  }
  else if (letter == "7")
  {
    Dat(); Dat(); Dit(); Dit(); Dit();
  }
  else if (letter == "8")
  {
    Dat(); Dat(); Dat(); Dit(); Dit();
  }
  else if (letter == "9")
  {
    Dat(); Dat(); Dat(); Dat(); Dit();
  }
  else if (letter == " ")
  {
    beep(false);
  }
  beep(false); beep(false); beep(false);
}
