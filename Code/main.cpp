#include <ESP8266WiFi.h>

// --- WI-FI CONFIGURATION ---
const char* ssid = "Utkarsh_Robot";      
const char* password = "password1234";   

WiFiServer server(80); 

// --- PIN DEFINITIONS (NodeMCU D-Pins) ---
// DRIVER 1 (Left Side) - Connected to IN3 & IN4
const int Left_IN3 = D1; 
const int Left_IN4 = D2;
a
// DRIVER 2 (Right Side) - Connected to IN3 & IN4
const int Right_IN3 = D5;
const int Right_IN4 = D6;

// --- LED BLINK VARIABLES (Non-Blocking) ---
const int statusLed = LED_BUILTIN;  // The blue light on the NodeMCU
int ledState = LOW;             // Current state of LED
unsigned long previousMillis = 0;   // Stores last time LED was updated
const long interval = 500;          // Blink speed (500ms = 0.5 seconds)

// --- FUNCTION PROTOTYPES ---
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopCar();

void setup() {
  Serial.begin(115200);

  // Set Motor Pins as OUTPUT
  pinMode(Left_IN3, OUTPUT);
  pinMode(Left_IN4, OUTPUT);
  pinMode(Right_IN3, OUTPUT);
  pinMode(Right_IN4, OUTPUT);
  
  // Set LED Pin as OUTPUT
  pinMode(statusLed, OUTPUT);

  stopCar();

  // Start Wi-Fi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.begin();

  Serial.println("Robot Wi-Fi Started!");
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP());
}

void loop() {
  // --- 1. HANDLE LED BLINKING (The Heartbeat) ---
  // This uses a timer so it doesn't slow down the motors
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you blinked

    // If the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(statusLed, ledState);
  }

  // --- 2. CHECK FOR APP COMMANDS ---
  WiFiClient client = server.accept();
  
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char command = client.read();
        
        if (command == 'F') moveForward();
        else if (command == 'B') moveBackward();
        else if (command == 'L') turnLeft();
        else if (command == 'R') turnRight();
        else if (command == 'S') stopCar();
      }
    }
    client.stop();
  }
}

// --- MOVEMENT FUNCTIONS ---

void moveForward() {
  digitalWrite(Left_IN3, HIGH); digitalWrite(Left_IN4, LOW); 
  digitalWrite(Right_IN3, HIGH); digitalWrite(Right_IN4, LOW); 
}

void moveBackward() {
  digitalWrite(Left_IN3, LOW); digitalWrite(Left_IN4, HIGH); 
  digitalWrite(Right_IN3, LOW); digitalWrite(Right_IN4, HIGH); 
}

void turnLeft() {
  digitalWrite(Left_IN3, LOW); digitalWrite(Left_IN4, HIGH); 
  digitalWrite(Right_IN3, HIGH); digitalWrite(Right_IN4, LOW); 
}

void turnRight() {
  digitalWrite(Left_IN3, HIGH); digitalWrite(Left_IN4, LOW); 
  digitalWrite(Right_IN3, LOW); digitalWrite(Right_IN4, HIGH); 
}

void stopCar() {
  digitalWrite(Left_IN3, LOW); digitalWrite(Left_IN4, LOW);
  digitalWrite(Right_IN3, LOW); digitalWrite(Right_IN4, LOW);
}