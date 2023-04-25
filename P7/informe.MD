1. Descibir la salida por el puerto serie 

La sortida del port serie es un missatge que diu Sound Generator que es repeteix cada cop que s'acabi la generació del so, esperara un segon i tornara a iniciar.

2. Explicar el funcionamiento 

En el setup s'inicialitzen els objectes necessaris per a la generació d'àudio: in és un objecte AudioFileSourcePROGMEM que es crea per accedir a la memòria de programa (PROGMEM) on es troba emmagatzemat el fitxer d'àudio AAC (sampleaac), aac és un objecte AudioGeneratorAAC utilitzat per a decodificar i reproduir el fitxer d'àudio, i out és un objecte AudioOutputI2S que envia l'àudio decodificat a través d'un bus I2S a un dispositiu de sortida d'àudio, com ara un altaveu.

En el loop es verifica si la generació d'àudio a través de l'objecte aac està en marxa (aac->isRunning()). Si és així, es crida al mètode loop() de aac per seguir decodificant i reproduint l'àudio. Si no està en marxa, es deté la reproducció amb aac->stop() i s'imprimeix un missatge al port sèrie. Després s'espera 1 segon amb la funció delay(1000) abans de continuar amb la propera iteració del loop.