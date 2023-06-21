#include <WiFi.h>
#include <ESPAsyncWebServer.h>
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

// Server
const char* ssid     = "PauMaza";
const char* password = "j3130Z-56";

// Set web server port number to 80
AsyncWebServer server(80);

// Initialize LCD screen object
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

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


void handleRootRequest(AsyncWebServerRequest* request) {
  String html = "<html><head>";
  html += "<link rel='stylesheet' type='text/css' href='/styles.css'>";
  html += "<style>";
  html += "body {font-family: Arial, sans-serif;}";
  html += "h1 {text-align: center;}";
  html += "h2 {margin-top: 20px;}";
  html += "#parking-spot {width: 500px; height: 500px; background-color: lightgray; margin: 20px auto;}";
  html += "#best-fit {margin-top: 20px; font-weight: bold;}";
  html += "</style>";
  html += "<script>";
  html += "document.addEventListener('DOMContentLoaded', function() {";
  html += "const carWidthInput = document.getElementById('car-width');";
  html += "const carLengthInput = document.getElementById('car-length');";
  html += "const calculateButton = document.getElementById('calculate-button');";
  html += "const bestFitContainer = document.getElementById('best-fit');";
  html += "const parkingSpot = document.getElementById('parking-spot');";
  html += "calculateButton.addEventListener('click', function() {";
  html += "const carWidth = parseInt(carWidthInput.value);";
  html += "const carLength = parseInt(carLengthInput.value);";
  html += "// Make an AJAX request to the server to calculate the best fit";
  html += "// You can use fetch() or XMLHttpRequest to send the request";
  html += "// Example response data (replace this with the actual response from the server)";
  html += "const responseData = {";
  html += "floor: 2,";
  html += "spot: 3";
  html += "};";
  html += "// Display the best fit result";
  html += "bestFitContainer.textContent = `Best Fit: Floor ${responseData.floor}, Spot ${responseData.spot}`;";
  html += "// Update the top-down view of the parking spot";
  html += "updateParkingSpot(carWidth, carLength);";
  html += "});";
  html += "function updateParkingSpot(carWidth, carLength) {";
  html += "// Clear the parking spot container";
  html += "parkingSpot.innerHTML = '';";
  html += "// Calculate the size of the parking spot based on the car dimensions";
  html += "const parkingSpotWidth = carWidth + 100;";
  html += "const parkingSpotHeight = carLength + 100;";
  html += "// Set the dimensions of the parking spot container";
  html += "parkingSpot.style.width = `${parkingSpotWidth}px`;";
  html += "parkingSpot.style.height = `${parkingSpotHeight}px`;";
  html += "// Add the car representation to the parking spot container";
  html += "const carElement = document.createElement('div');";
  html += "carElement.classList.add('car');";
  html += "carElement.style.width = `${carWidth}px`;";
  html += "carElement.style.height = `${carLength}px`;";
  html += "parkingSpot.appendChild(carElement);";
  html += "}";
  html += "});";
  html += "</script>";
  html += "</head><body>";
  html += "<h1>Front Distance:</h1>";
  html += "<p>" + String(getDistance(frontTriggerPin, frontEchoPin)) + " cm</p>";
  html += "<h1>Back Distance:</h1>";
  html += "<p>" + String(getDistance(backTriggerPin, backEchoPin)) + " cm</p>";
  html += "<h1>Car Size Fit:</h1>";
  html += "<p>Floor 1: " + String((floor1SpotWidth >= carWidth && floor1SpotLength >= carLength) ? 1 : 0) + "</p>";
  html += "<p>Floor 2: " + String((floor2SpotWidth >= carWidth && floor2SpotLength >= carLength) ? 1 : 0) + "</p>";
  html += "<p>Floor 3: " + String((floor3SpotWidth >= carWidth && floor3SpotLength >= carLength) ? 1 : 0) + "</p>";
  html += "<h2>Enter Car Dimensions:</h2>";
  html += "<input type='number' id='car-width' placeholder='Car Width'>";
  html += "<input type='number' id='car-length' placeholder='Car Length'>";
  html += "<button id='calculate-button'>Calculate Best Fit</button>";
  html += "<h2 id='best-fit'></h2>";
  html += "<div id='parking-spot'></div>";
  html += "</body></html>";

  request->send(200, "text/html", html);
}

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

  WiFi.begin(ssid, password);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// this will display the Ip address which should be entered into your browser

  server.on("/", HTTP_GET, handleRootRequest);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}


void loop() {
  // Server
  //server.serveStatic("/index.html");

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