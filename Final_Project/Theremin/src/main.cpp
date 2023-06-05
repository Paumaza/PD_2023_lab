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
#define FREQ_MAX_DISTANCE 50 // Maximum distance (in centimeters) for frequency control

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

short sample = amplitude; // current sample value
int count = 0;

i2s_mode_t mode = I2S_PHILIPS_MODE; // I2S decoder is needed
// i2s_mode_t mode = ADC_DAC_MODE; // Audio amplifier is needed

// Mono channel input
// This is ESP specific implementation -
//   samples will be automatically copied to both channels inside I2S driver
//   If you want to have true mono output use I2S_PHILIPS_MODE and interlay
//   second channel with 0-value samples.
//   The order of channels is RIGH followed by LEFT
//i2s_mode_t mode = I2S_RIGHT_JUSTIFIED_MODE; // I2S decoder is needed

void setup() {
  Serial.begin(115200);

  if (!I2S.begin(mode, sampleRate, bps)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }

  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(LRC_PIN, OUTPUT);
  pinMode(BCLK_PIN, OUTPUT);

  // Initialize ToneAC library
  // ToneAC.begin(SPEAKER_PIN);
}

void loop() {
  float freqDistance = ultrasonicFreq.read() / 58.0; // Convert the echo time to distance in centimeters
  float ampDistance = ultrasonicAmp.read() / 58.0;   // Convert the echo time to distance in centimeters
  Serial.print("read ultrasonic sensor ok");

  // Map the distance values to the desired range for frequency and amplitude
  int freq = map(freqDistance, 0, FREQ_MAX_DISTANCE, 100, 1000);
  int amp = map(ampDistance, 0, AMP_MAX_DISTANCE, 0, 255);
  Serial.print("Distance 1: ");
  Serial.println(freqDistance);
  Serial.print("Distance 2: ");
  Serial.println(ampDistance);
  Serial.print("Frequency: ");
  Serial.println(freq);
  Serial.print("Amplitude: ");
  Serial.println(amp);

  // Generate the audio tone with the calculated frequency and amplitude
  if (count % halfWavelength == 0 ) {
      // invert the sample every half wavelength count multiple to generate square wave
      sample = -1 * sample;
    }

  if(mode == I2S_PHILIPS_MODE || mode == ADC_DAC_MODE){ // write the same sample twice, once for Right and once for Left channel
    I2S.write(sample); // Right channel
    I2S.write(sample); // Left channel
    }
  else if(mode == I2S_RIGHT_JUSTIFIED_MODE || mode == I2S_LEFT_JUSTIFIED_MODE){
    // write the same only once - it will be automatically copied to the other channel
    I2S.write(sample);
  }

  // increment the counter for the next sample
  count++;
}
