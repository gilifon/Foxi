/*
  A simple Fox Hunting Transmitter
*/

#include <SPI.h>
#include "foxi_config.h"

Foxi foxi;
const byte data[] =  {0x00, 0xFF};

const String message = "HELLO I AM FOX1 1 1";
const unsigned int preSignaDelay = 1000;
const unsigned int postSignaDelay = 15000;

void setup() {
  Serial.begin(9600);
  foxi.setup();
}

void loop() {
  delay(preSignaDelay);
  foxi.begin();
  foxi.sendMessage();
  foxi.end();
  delay(postSignaDelay);
}

void Send(int rep)
{
  foxi.begin();
  foxi.sendCommand(data, sizeof(data) * 8, rep);
  foxi.end();
}

void Dit()
{
  Send(30); 
  delay(100);
}

void Dat()
{
  Send(90);
  delay(100);
}

void SendLetter(String letter)
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
    delay(400);
  }
  delay(200);
}

