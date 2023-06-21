#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins for the ultrasonic sensors
const int frontTriggerPin = 18;
const int frontEchoPin = 19;
const int backTriggerPin = 12;
const int backEchoPin = 14;

// LCD screen dimensions
const int lcdColumns = 16;
const int lcdRows = 2;

// I2C address of the LCD screen
const int lcdAddress = 0x27;

// Ultrasonic sensor maximum range in centimeters
const int maxRange = 400;

// Car dimensions
const int carWidth = 200;  // In centimeters
const int carLength = 500; // In centimeters

// Parking spot dimensions (example values)
const int floor1SpotWidth = 250;  // In centimeters
const int floor1SpotLength = 500; // In centimeters
const int floor2SpotWidth = 300;  // In centimeters
const int floor2SpotLength = 600; // In centimeters
const int floor3SpotWidth = 350;  // In centimeters
const int floor3SpotLength = 700; // In centimeters

// Initialize LCD screen object
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

void setup() {
  Serial.begin(115200);
  pinMode(frontTriggerPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(backTriggerPin, OUTPUT);
  pinMode(backEchoPin, INPUT);

  Wire.begin(21, 22);

  // Initialize LCD screen
  lcd.begin(lcdColumns, lcdRows);
  lcd.backlight();
}

float getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

void displayOnLCD(const String& text, int column, int row) {
  lcd.setCursor(column, row);
  lcd.print(text);
}

void loop() {
  // Get front and back distances
  float frontDistance = getDistance(frontTriggerPin, frontEchoPin);
  float backDistance = getDistance(backTriggerPin, backEchoPin);

  // Calculate car size fit on each floor
  int floor1Fit = (floor1SpotWidth >= carWidth && floor1SpotLength >= carLength) ? 1 : 0;
  int floor2Fit = (floor2SpotWidth >= carWidth && floor2SpotLength >= carLength) ? 1 : 0;
  int floor3Fit = (floor3SpotWidth >= carWidth && floor3SpotLength >= carLength) ? 1 : 0;

  // Clear LCD screen
  lcd.clear();

  // Display front distance
  displayOnLCD("Front:", 0, 0);
  displayOnLCD(String(frontDistance) + " cm", 0, 1);
  delay(1000);

  // Display back distance
  displayOnLCD("Back:", 0, 0);
  displayOnLCD(String(backDistance) + " cm", 0, 3);
  delay(1000);

  // Display car size fit
  displayOnLCD("Car Size Fit:", 0, 0);
  displayOnLCD("Floor 1: " + String(floor1Fit), 0, 1);
  delay(1000);
  displayOnLCD("Floor 2: " + String(floor2Fit), 0, 1);
  delay(1000);
  displayOnLCD("Floor 3: " + String(floor3Fit), 0, 1);

  lcd.clear();

  // You can add additional logic here to determine the best fit based on the given criteria

  delay(1000); // Adjust the delay as per your needs
}
