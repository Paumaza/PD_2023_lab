## Exercici 1

1. Descibir la salida por el puerto serie 

La sortida del port serie es un missatge que diu Sound Generator que es repeteix cada cop que s'acabi la generació del so, esperara un segon i tornara a iniciar.

2. Explicar el funcionamiento 

En el setup s'inicialitzen els objectes necessaris per a la generació d'àudio: in és un objecte AudioFileSourcePROGMEM que es crea per accedir a la memòria de programa (PROGMEM) on es troba emmagatzemat el fitxer d'àudio AAC (sampleaac), aac és un objecte AudioGeneratorAAC utilitzat per a decodificar i reproduir el fitxer d'àudio, i out és un objecte AudioOutputI2S que envia l'àudio decodificat a través d'un bus I2S a un dispositiu de sortida d'àudio, com ara un altaveu.

En el loop es verifica si la generació d'àudio a través de l'objecte aac està en marxa (aac->isRunning()). Si és així, es crida al mètode loop() de aac per seguir decodificant i reproduint l'àudio. Si no està en marxa, es deté la reproducció amb aac->stop() i s'imprimeix un missatge al port sèrie. Després s'espera 1 segon amb la funció delay(1000) abans de continuar amb la propera iteració del loop.

## Exercici 2
1. La sortida pel port sèrie en aquest codi consisteix en imprimir diferents tipus d'informació d'àudio, com informació de metadades, informació de l'estació, títol de la transmissió, durada comercial, URL de la pàgina d'inici, etc. La informació es mostra amb etiquetes corresponents al seu tipus, com "info", "id3data", "station", "streaminfo", "streamtitle", "bitrate", "commercial", "icyurl", "lasthost" i "eof_speech". Juntament amb l'etiqueta, es mostra el valor de la informació corresponent.

2. El codi configura el dispositiu d'àudio i el connecta a la targeta SD per reproduir un fitxer d'àudio WAVE. Primer, es defineixen les entrades i sortides digitals utilitzades, i després es configuren i s'inicien les connexions de la SD i l'àudio. Després, s'estableix el volum de l'àudio a 10 (en una escala de 0 a 21) i es connecta l'objecte d'àudio amb la targeta SD i el fitxer d'àudio WAVE especificat. En el bucle principal, es crida el mètode "loop()" de l'objecte d'àudio per reproduir l'àudio. A més, es defineixen diverses funcions opcionals per imprimir informació detallada sobre l'àudio en el port sèrie en temps d'execució.