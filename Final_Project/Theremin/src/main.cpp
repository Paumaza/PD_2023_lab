#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>

// Replace with your network credentials
const char* ssid = "iPhone de: Pau";
const char* password = "Paumaza12";

// Replace with the IP address and port of your computer running the OSC server
const char* oscAddress = "192.168.1.100";
const int oscPort = 12345;

// Ultrasonic sensor pins
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 14;

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
int distance = 0;
int frequency = 0;
int amplitude = 0;

int getUltrasonicDistance() {
  // Generate a pulse to trigger the ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the duration of the pulse from the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance based on the speed of sound (343.2 meters/second)
  // and the duration of the pulse
  int distance = duration * 0.03432 / 2;

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

  // Initialize ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Read distance from ultrasonic sensor
  distance = getUltrasonicDistance();
  if (distance < RANGE_MIN) {
    distance = RANGE_MIN;
  } else if (distance > RANGE_MAX) {
    distance = RANGE_MAX;
  }

  // Map the sensor reading to frequency and amplitude values
  frequency = map(distance, RANGE_MIN, RANGE_MAX, FREQ_MIN, FREQ_MAX);
  amplitude = map(distance, RANGE_MIN, RANGE_MAX, AMP_MIN, AMP_MAX);

  // Send OSC message with frequency and amplitude values
  sendOSC("/theremin/frequency", frequency);
  sendOSC("/theremin/amplitude", amplitude);

  // Print sensor reading and mapped values
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Frequency: ");
  Serial.println(frequency);
  Serial.print("Amplitude: ");
  Serial.println(amplitude);

  delay(100);
}