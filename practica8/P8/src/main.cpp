#include <Arduino.h>

void setup() {
  // UART0 terminal
  Serial.begin(115200);

  // UART2 periferic
  Serial2.begin(115200);
}

void loop() {
  // llegir  UART0 i escriure a UART2
  if (Serial.available()) {
    byte recibido = Serial.read();
    Serial2.write(recibido);
  }

  // llegir UART2 i escriure a UART0
  if (Serial2.available()) {
    byte recibido = Serial2.read();
    Serial.write(recibido);
  }
}
