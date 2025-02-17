#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define pin connections for the joystick
const int Joystick_x = A0;  // Corrected analog input pins (A0, A1)
const int Joystick_y = A1;
const int Button = 2;

// Variables to store joystick and button states
int xVal = 0;
int yVal = 0;
bool SW = 0;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(Button, INPUT_PULLUP); // Button uses internal pull-up
  radio.begin();
  if (!radio.begin()) {
    Serial.println("NRF24L01 initialization failed!");
    while (1);
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); // Set as transmitter
}

void loop() {
  // Read joystick values
  xVal = analogRead(Joystick_x);
  yVal = analogRead(Joystick_y);
  SW = digitalRead(Button);
  bool invertedSW = !SW; // Invert button state (LOW when pressed)

  int dataToSend[3] = {xVal, yVal, invertedSW};

  // Send data and check success
  bool success = radio.write(&dataToSend, sizeof(dataToSend)); // Capture return value

  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(", Y: ");
  Serial.print(yVal);
  Serial.print(", SW: ");
  Serial.print(invertedSW);
  Serial.print(" - Transmission: ");
  Serial.println(success ? "Success" : "Failed");

  delay(100); // Short delay to stabilize transmission
}