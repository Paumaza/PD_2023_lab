# Ejercicio practico 1  bucle de comunicacion uart2

#include <Arduino.h>

void setup() {
  ## UART0 terminal
  Serial.begin(115200);

  ## UART2 periferic
  Serial2.begin(115200);
}

void loop() {
  ## llegir  UART0 i escriure a UART2
  if (Serial.available()) {
    byte recibido = Serial.read();
    Serial2.write(recibido);
  }

  
  ## llegir UART2 i escriure a UART0
  if (Serial2.available()) {
    byte recibido = Serial2.read();
    Serial.write(recibido);
  }
}

Entrada (rxd0): Aquesta entrada és la UART 0, que es configura com a terminal. Podem escriure dades des del teclat o una altra font d'entrada, que es llegirà en UART.

Sortida (txd0): Aquesta sortida és la UART 0, que es configura com a terminal. El programa escriurà dades a UART perquè apareguin a la pantalla.

Entrada (rxd2): Aquesta entrada és la UART 2, que es configura com a dispositiu extern. El programa llegirà les dades que s'envien a través de UART.

Sortida (txd2): Aquesta sortida és la UART 2, que es configura com a dispositiu extern. El programa enviarà les dades que ha llegit de l'entrada rxd0 a través de UART.