/*
* https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
* Arduino Nano
* Library: RF24 by TMRH20
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  if (!radio.begin()) {
    Serial.println("NRF24L01 initialization failed!");
    while (1);
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int receivedData[3]; // Array to store received data
    radio.read(&receivedData, sizeof(receivedData));
    // Print received X, Y, Z values
    Serial.print("X: ");
    Serial.print(receivedData[0]);
    Serial.print(", Y: ");
    Serial.print(receivedData[1]);
    Serial.print(", SW: ");
    Serial.println(receivedData[2]);
  }
}