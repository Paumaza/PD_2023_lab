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

# Ejercicio practico 2  (optativo) modulo GPS

Perque el codi funcionés hem hagut d'afegir les llibreries corresponents, TinyGPS i SoftwareSerial de Arduino

El GPS es connecta als pins 4 i 3, que són RX i TX en la interfície SoftwareSerial.

En el setup, s'inicialitza la connexió sèrie i es crea una instància de la interfície SoftwareSerial. En el loop, es comprova si s'ha rebut una nova seqüència de dades des del GPS a través de la interfície SoftwareSerial. Si s'ha rebut una nova seqüència de dades, s'extreuen les coordenades de latitud, longitud, edat i número de satèl·lits i s'envien a la consola sèrie per a la seva visualització. A continuació, es crida a stats() per obtenir informació estadística sobre la seqüència de dades rebuda.

La sortida de consola del programa mostra les coordenades de latitud i longitud, el número de satèl·lits i la precisió de la senyal GPS. A més, també es mostren estadístiques de la seqüència de dades rebuda, incloent el número de caràcters rebuts, el número de sentències rebudes i el número d'errors de suma de comprovació.