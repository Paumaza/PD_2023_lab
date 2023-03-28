## Ejercicio Practico 1  LECTURA/ESCRITURA  DE MEMORIA SD

1. Descibir la salida por el puerto serie 
La sortida del port sèrie és una impressió a la pantalla connectada del contingut de l'arxiu txt.

2. Explicar el funcionamiento 
a la funció setup s'inicialitza la comunicació sèrie i el lector de la tarjeta sd, hi ha un control d'errors que t'avisa si no es pot iniciar el lector. A continuació s'obre l'arxiu txt i es mostra per pantalla, si no es pot llegir apareix un missatge d'error, al final es tanca l'arxiu txt.

## Ejercicio 2

1. Descibir la salida por el puerto serie 
La sortida es la impressió de l'identificarod únic (UID), de la tarjeta que ha llegit el lector en format hexadecimal.

2. Explicar el funcionamiento 
En el Setup s'inicia la comunicació sèrie, el bus SPI i el lector, després d'imprimeix un missatge que diu que ja esta llest per llegir tarjetes.
Dins la funció loop es comprova si hi ha una tarjeta,si es troba la tarjeta, es llegeix i mostra per pantalla el UID, aquest s'imprimeix amb un bucle for ja que el UID es llegeix d'un en un, i per acabar es finalitza la lectura de la tarjeta i torna a iniciar el loop.