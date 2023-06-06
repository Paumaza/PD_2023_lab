#include <Tone32.h>
#include <Ultrasonic.h>
#include <I2S.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <SPI.h>
#include <SD.h>
#include <SD_MMC.h>
#include <SPIFFS.h>
#include <FFat.h>

#define TRIGGER_PIN_FREQ 14  // GPIO pin connected to the frequency ultrasonic sensor's trigger pin
#define ECHO_PIN_FREQ 12     // GPIO pin connected to the frequency ultrasonic sensor's echo pin

#define TRIGGER_PIN_AMP 27   // GPIO pin connected to the amplitude ultrasonic sensor's trigger pin
#define ECHO_PIN_AMP 33      // GPIO pin connected to the amplitude ultrasonic sensor's echo pin

#define AMP_MAX_DISTANCE 100 // Maximum distance (in centimeters) for amplitude control
#define FREQ_MAX_DISTANCE 100 // Maximum distance (in centimeters) for frequency control

#define SPEAKER_PIN 22       // GPIO pin connected to the MAX98357A amplifier's input pin
#define LRC_PIN 25           // GPIO pin connected to the MAX98357A amplifier's LRC pin
#define BCLK_PIN 26          // GPIO pin connected to the MAX98357A amplifier's BCLK pin

#define BUZZER_CHANNEL 0


Ultrasonic ultrasonicFreq(TRIGGER_PIN_FREQ, ECHO_PIN_FREQ);
Ultrasonic ultrasonicAmp(TRIGGER_PIN_AMP, ECHO_PIN_AMP);


const int frequency = 440; // frequency of square wave in Hz
const int amplitude = 500; // amplitude of square wave
const int sampleRate = 8000; // sample rate in Hz
const int bps = 16;

const int halfWavelength = (sampleRate / frequency); // half wavelength of square wave

int sample = amplitude; // current sample value
int count = 0;

i2s_mode_t mode = ADC_DAC_MODE; // Audio amplifier is needed

void setup() {
  Serial.begin(115200);

  if (!I2S.begin(mode, sampleRate, bps)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }

  // pinMode(SPEAKER_PIN, OUTPUT);
  // pinMode(LRC_PIN, OUTPUT);
  // pinMode(BCLK_PIN, OUTPUT);

  I2S.setFsPin(LRC_PIN);
  I2S.setDataPin(SPEAKER_PIN);
  I2S.setSckPin(BCLK_PIN);
}

void loop() {
  float freqDistance = ultrasonicFreq.read(); // 5.80; // Convert the echo time to distance in centimeters
  float ampDistance = ultrasonicAmp.read(); // 5.80;   // Convert the echo time to distance in centimeters

  // Map the distance values to the desired range for frequency and amplitude
  int freq = map(freqDistance, 0, FREQ_MAX_DISTANCE, 100, 1000);
  Serial.print("Distance 1: ");
  Serial.println(freqDistance);
  Serial.print("Distance 2: ");
  Serial.println(ampDistance);

  int amp = map(ampDistance, 0, AMP_MAX_DISTANCE, 0, 255);

  Serial.print("Frequency: ");
  Serial.println(freq);
  Serial.print("Amplitude: ");
  Serial.println(amp);

  sample = amp * sin(2.0 * PI * freq * count / sampleRate);
  Serial.print("Sample: ");
  Serial.println(sample);

  // Generate the audio tone with the calculated frequency and amplitude
  // if (count % halfWavelength == 0 ) {
  //     // invert the sample every half wavelength count multiple to generate square wave
  //     sample = -1 * sample;
  //   }

  if(mode == I2S_PHILIPS_MODE || mode == ADC_DAC_MODE){ // write the same sample twice, once for Right and once for Left channel
    I2S.write(sample); // Right channel
    I2S.write(sample); // Left channel
    Serial.println("IN LR");
    }
  else if(mode == I2S_RIGHT_JUSTIFIED_MODE || mode == I2S_LEFT_JUSTIFIED_MODE){
    // write the same only once - it will be automatically copied to the other channel
    I2S.write(sample);
  }

  // increment the counter for the next sample
  count++;
}