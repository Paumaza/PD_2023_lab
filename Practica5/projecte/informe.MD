# INFORME PRACTICA 5

1. Describe la salida y explica el funcionamiento.

    L'objectiu d'aquest codi és identificar dispositius connectats a la ESP32 a través del bus I2C.
    
    S'inclouen les llibreries necessàries, al setup, s'inicia la comunicació I2C i sèrie i s'imprimeix un missatge en el monitor indicant que l'esscaneig de I2C ha començat.

    En la part del loop inicialment s'escaneja la direcció dels dispositius I2C connectats a la ESP32, i posteriorment s'inicia un bucle for des de 1 fins a 127, per passar per totes les possibles direccions, en cada iteració es realitza una transmissió I2C a la direcció previament guardada amb la funció Wire.beginTransmission(address), i es retorna el valor de la funció per poder saber si el dispositiu ha respost, es a dir, si hi ha un dispositiu connectat. En aquest cas una resposta de 0 es considera correcte i es mostra per pantalla la direcció del dispositiu.

    També tenim un control d'errors, on només s'activa si quan es fa la transmissió amb el dispositiu es retorna un valor de 4. Llavors es mostra per pantalla que hi ha un error i l'adreça de l'error a continuació.

    Finalment s'afegeix un valor al contador de dispositius, que ens serveix per determinar al final quants dispositius tenim connectats. Si aquest valor es de 0, s'imprimeix un missatge per pantalla que no s'han trobat disposituis, en cas contrari s'imprimeix el missatge "done".