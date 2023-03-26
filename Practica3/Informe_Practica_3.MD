Por ejemplo: puede tener un microcontrolador que lee un sensor de temperatura, lo muestra en una pantalla LCD y lo envía a la nube.
Puede hacer los tres sincrónicamente, uno tras otro. Pero, ¿qué sucede si está utilizando una pantalla de tinta electrónica que tarda unos segundos en actualizarse? 
Ja que la pantalla tarda uns segons en actualitzar-se, totes les tasques es realitzen abans que es pugui actualitzar la pantalla, i per tant, que el programa acabi d’executar-se sense haver mostrat cap valor per la pantalla.


## Ejercicio Práctico 1
Descriure la sortida del port sèrie i comentar el funcionament:


void toggleLED(void * parameter){
 for(;;){ // infinite loop
   // Turn the LED on
   digitalWrite(led1, HIGH);
   // Pause the task for 500ms
   vTaskDelay(500 / portTICK_PERIOD_MS);
   // Turn the LED off
   digitalWrite(led1, LOW);
   // Pause the task again for 500ms
   vTaskDelay(500 / portTICK_PERIOD_MS);
 }
 // delete a task when finish, this will never happen because this is infinity loop*/
 vTaskDelete( NULL );
}
S’inicia una tasca amb un bucle infinit i una ordre d’eliminació al final, la qual mai es dóna ja que no surt del bucle infinit.
La tasca en si el que fa és engegar el LED, esperar 500ms o mig segon utilitzant la funció de vTaskDelay, apagar el led i tornar a esperar mig segon per tornar a iniciar el bucle infinit.



void setup() {
 pinMode(led1, OUTPUT);
 Serial.begin(115200);
 xTaskCreate(
   toggleLED,    // Function that should be called
   "Toggle LED",   // Name of the task (for debugging)
   1000,            // Stack size (bytes)
   NULL,            // Parameter to pass
   1,               // Task priority
   NULL             // Task handle
 );
}
En el SetUp, iniciem el Serial per poder-lo fer servir després, iniciem també el LED en el pin que hi hem assignat (23 en el nostre cas) i creem la Tasca.
Aquesta creació de la tasca apunta a la funció creada amb anterioritat toggleLED, se li dóna un nom “Toggle LED”, i la resta de paràmetres els deixem per defecte a un stack size de 1000, una prioritat de 1 i els paràmetres per passar i el task handle a “NULL”

void loop() {
 Serial.println("this is ESP32 Task");
 delay(1000);
}
Creació del loop infinit. Al qual li demanem que ens imprimeix per pantalla “this is  ESP32 task” cada segon. on posteriorment s’ha demanat la funció que cada mig segon s'encengui i led i després s’apagui en un altre mig segon. 

## Ejercicio Práctico 2
Creació de tasca d’engegat del LED
Bool LED = False;

void LEDon(void * LED){
 for(;;){ // infinite loop
   // Turn the LED on
   if(!LED){
digitalWrite(led1, HIGH);
LED = True;}
   // Pause the task for 500ms
   vTaskDelay(300 / portTICK_PERIOD_MS);
 }
 // delete a task when finish, this will never happen because this is infinity loop*/
 vTaskDelete( NULL );
}

Creació de tasca d’apagat del LED
void LEDoff(void * LED){
 for(;;){ // infinite loop
   // Turn the LED off*/
   if(LED){
digitalWrite(led1, LOW);
LED = False;}
   // Pause the task for 500ms
   vTaskDelay(800 / portTICK_PERIOD_MS);
 }
 // delete a task when finish, this will never happen because this is infinity loop*/
 vTaskDelete( NULL );
}


SetUp
void setup() {
 pinMode(led1, OUTPUT);
 Serial.begin(115200);
 
xTaskCreate(
   LEDon,    // Function that should be called
   "LED on",   // Name of the task (for debugging)
   1000,            // Stack size (bytes)
   LED,            // Parameter to pass
   1,               // Task priority
   NULL             // Task handle
 );
xTaskCreate(
   LEDoff,    // Function that should be called
   "LED off",   // Name of the task (for debugging)
   1000,            // Stack size (bytes)
   LED,            // Parameter to pass
   1,               // Task priority
   NULL             // Task handle
 );

}

Loop
void loop() {
 Serial.println("these are two ESP32 Task");
 delay(1000);
}

