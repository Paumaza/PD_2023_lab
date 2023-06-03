#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <NewPing.h>
#include <SPI.h>
#include <Audio.h>
#include <SD.h>
#include <FS.h>
#include <AudioOutputI2S.h>

// Replace with your network credentials
const char* ssid = "iPhone de: Pau";
const char* password = "Paumaza12";

// Replace with the IP address and port of your computer running the OSC server
const char* oscAddress = "192.168.1.100";
const int oscPort = 12345;

// Ultrasonic sensor 1 pins
const int TRIGGER1_PIN = 12;
const int ECHO1_PIN = 14;

// Ultrasonic sensor 2 pins
const int TRIGGER2_PIN = 25;
const int ECHO2_PIN = 26;

// Thresholds for adjusting the range
const int RANGE_MIN = 10;    // Minimum range in centimeters
const int RANGE_MAX = 200;   // Maximum range in centimeters

// Frequency modulation settings
const int FREQ_MIN = 200;    // Minimum frequency in Hz
const int FREQ_MAX = 2000;   // Maximum frequency in Hz

// Amplitude modulation settings
const int AMP_MIN = 0;       // Minimum amplitude
const int AMP_MAX = 255;     // Maximum amplitude

// Variables for storing sensor readings
int distance1 = 0;
int distance2 = 0;
int frequency = 0;
int amplitude = 0;

const int I2S_SCK = 21;
const int I2S_WS = 19;
const int I2S_SD = 22;

// Ultrasonic sensor objects
NewPing sonar1(TRIGGER1_PIN, ECHO1_PIN, RANGE_MAX);
NewPing sonar2(TRIGGER2_PIN, ECHO2_PIN, RANGE_MAX);

AudioOutputI2S audioOutput;

int getUltrasonicDistance(NewPing& sonar) {
  delay(50); // Delay before taking a measurement
  int distance = sonar.ping_cm(); // Measure the distance in centimeters
  return distance;
}

void sendOSC(const char* address, int value) {
  WiFiUDP udp;
  udp.beginPacket(oscAddress, oscPort);
  OSCBundle bundle;
  OSCMessage msg(address);
  msg.add(value);
  bundle.add(msg);
  bundle.send(udp);
  udp.endPacket();
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize audio output
  i2s_begin(I2S_SCK, I2S_WS, I2S_SD);
}

void loop() {
  // Read distance from ultrasonic sensor 1
  distance1 = getUltrasonicDistance(sonar1);
  if (distance1 < RANGE_MIN) {
    distance1 = RANGE_MIN;
  } else if (distance1 > RANGE_MAX) {
    distance1 = RANGE_MAX;
  }

  // Read distance from ultrasonic sensor 2
  distance2 = getUltrasonicDistance(sonar2);
  if (distance2 < RANGE_MIN) {
    distance2 = RANGE_MIN;
  } else if (distance2 > RANGE_MAX) {
    distance2 = RANGE_MAX;
  }

  // Map the sensor readings to frequency and amplitude values
  frequency = map(distance1, RANGE_MIN, RANGE_MAX, FREQ_MIN, FREQ_MAX);
  amplitude = map(distance2, RANGE_MIN, RANGE_MAX, AMP_MIN, AMP_MAX);

  // Send OSC message with frequency and amplitude values
  sendOSC("/theremin/frequency", frequency);
  sendOSC("/theremin/amplitude", amplitude);

  // Generate the audio sample
  float phaseIncrement = 2 * PI * frequency / 44100.0;
  for (int i = 0; i < 44100; i++) {
    float sample = sin(i * phaseIncrement) * amplitude;

    // Output the sample to the amplifier
    i2s_write_sample(I2S_SD, sample);
  



  // Print sensor readings and mapped values
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  Serial.print("Distance 2: ");
  Serial.println(distance2);
  Serial.print("Frequency: ");
  Serial.println(frequency);
  Serial.print("Amplitude: ");
  Serial.println(amplitude);

  delay(100);
}