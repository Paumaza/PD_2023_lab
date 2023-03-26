# INFORME PRACTICA 5

1. Describe la salida y explica el funcionamiento.

    L'objectiu d'aquest codi és identificar dispositius connectats a la ESP32 a través del bus I2C.
    
    S'inclouen les llibreries necessàries, al setup, s'inicia la comunicació I2C i sèrie i s'imprimeix un missatge en el monitor indicant que l'esscaneig de I2C ha començat.

    En la part del loop inicialment s'escaneja la direcció dels dispositius I2C connectats a la ESP32, i posteriorment s'inicia un bucle for des de 1 fins a 127, per passar per totes les possibles direccions, en cada iteració es realitza una transmissió I2C a la direcció previament guardada amb la funció Wire.beginTransmission(address), i es retorna el valor de la funció per poder saber si el dispositiu ha respost, es a dir, si hi ha un dispositiu connectat. En aquest cas una resposta de 0 es considera correcte i es mostra per pantalla la direcció del dispositiu.

    També tenim un control d'errors, on només s'activa si quan es fa la transmissió amb el dispositiu es retorna un valor de 4. Llavors es mostra per pantalla que hi ha un error i l'adreça de l'error a continuació.

    Finalment s'afegeix un valor al contador de dispositius, que ens serveix per determinar al final quants dispositius tenim connectats. Si aquest valor es de 0, s'imprimeix un missatge per pantalla que no s'han trobat disposituis, en cas contrari s'imprimeix el missatge "done".

2. Explicació del lector de temperatures
    L'objectiu d'aquest codi es medir al temperatura amb precisió, per realitzar aquesta pràctica hem necessitat incorporar una llibreria, #include <AHT10.h>. Amb el codi de la part anterior de la pràctica hem pogut trobar el port (en hexadecimal) on es troba el sensor de temperatura i li hem assginat a una variable (0x38). 

    A continuació dins del void SetUp hem iniciat el Serial per poder veure els resultats per pantalla, i amb una cobprovació del dispositiu hem fet un control d'errors per comprobar que el dispositiu de temperatura estigui ben connectat i amb la configuració correcta.

    Dins el loop, llegim la temperatura amb la funció readTemperature(); i la mostrem per pantalla amb el format corresponent i l'error possible. Si aquesta lectura dona un error es farà un reset del dipositiu de temperatura i es mostrarà per pantalla.

    Fem exactament el mateix per la humitat.

    Per finalitzar fem el mateix procediment per temperatura i humitat llegit 6 bytes enlloc de 12 com hem fet a la primera part. Aquesta configuració és possible ja que en la segona on es redueix a la meitat el número de bytes es reaprofiten els espais de memòria de la lectura inicial de la temperatura per fer la lectura en sèrie de la humitat, i per tant no es fa en paral·lel, com en la primera demostració.

    En tots els casos, com es pot veure a la datasheet, la temperatura i la humitat tenen un total de 20 bytes, cosa que provoca haver de compartir un bloc de 8 bytes on estan distribuides als primers 4 bytes la humitat i als ultims 4 la temperatura, havent de fer així algunes operacions per poder sumar els bytes entre si respectant el seu pes, és a dir, s'ha hagut de desplaçar una primera lectura 16 bytes a l'esquerra, una segona 8 bytes i de la última s'han hagut d'utilitzar només els priemrs 4.

    Per una altra banda aquesta operació s'ha hagut de fer al revés per la temperatura, eliminar 4 bytes, augmentar-ne la significancia i sumar els dos blocs següents de bytes amb la significancia respectiva.

    Hem connectat la pantalla LCD de dues línies però no hem aplicat el codi perquè la temperatura es vegi per pantalla, en tot cas el codi quedaria de la següent manera:

    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    ahtValue = aht10.readTemperature();
    lcd.print(ahtValue);
    lcd.print(" +-0.3C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    ahtValue = aht10.readHumidity();
    lcd.print(ahtValue);
    lcd.print(" +-2%");