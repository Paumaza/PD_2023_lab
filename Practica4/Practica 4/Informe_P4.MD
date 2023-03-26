## Informe Pràctica 4

1. Informe de funcionament i sortida.
    D'entrada a classe es va crear prèviament la wifi per la pràctica, i per tant necesitem coneixer la SSID i la contrassenya de la xarxa epr connectar-nos.

    Amb aquesta informació la guardem en dues variables i li diem al servidor que faci servir el port 80, el port per defecte.

    Dins el SetUp, iniciem el Serial i mostrem un missatge epr pantalla dient que s'està realitzant la connexió, mentrestant iniciem la extensió Wifi amb WiFi.begin(ssid, password); per connectar-nos. i mentres no es connecti, ens mantenim a l'espera.

    Mostrem per pantalla quan es realitza ia connexió i la IP que ens ha assignat per poder-nos connectar després a través del navegador.

    Recordem que el WiFi generat a classe tenia un límit de 16 connexions i a vegades era possible que no es pogués connectar tothom ja que haviem de connectar l'ordinador i la ESP32 per tal de poder fer-hi proves, i per tant això reduia el numero de grups maxims que es podien connectar a 8.

    A continuaciuó es feia el loop amb una única funicó que es la de server.handleClient(); que bàsicament manté la connexió oberta amb el navegador per poder-hi treballar.

    A continuació o en un altre arxiu podem determinar el codi HTML que volem que es vegi a la pàgina que obrim en el servidor. S'ha de posar com un String en una variable per tal de passar-la a la funció del servidor de .send(); i que la pugui llegir.

    En aquesta funció de server.send(200,  "text/html", HTML); s'ha d'indicar el tipus de codi que has escrit, HTML en el nostre cas i passar-li el text que hem escrit perquè es visualitzi a la pàgina, aquest text ha d'estar en format HTML perquè així es visualitzi correctament.