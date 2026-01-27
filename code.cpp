#include <ESP8266WiFi.h>

const char* ssid = "Utkarsh_Robot";      
const char* password = "password1234";   

WiFiServer server(80); 

// Pin Definitions (Using IN3/IN4)
const int Left_IN3 = D1; 
const int Left_IN4 = D2;
const int Right_IN3 = D5;
const int Right_IN4 = D6;

// LED Status
const int statusLed = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 500; 

// Function Prototypes
void moveForward(); void moveBackward(); void turnLeft(); void turnRight(); void stopCar();

void setup() {
  Serial.begin(115200);
  pinMode(Left_IN3, OUTPUT); pinMode(Left_IN4, OUTPUT);
  pinMode(Right_IN3, OUTPUT); pinMode(Right_IN4, OUTPUT);
  pinMode(statusLed, OUTPUT);
  stopCar();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.println("Robot Ready at 192.168.4.1");
}

void loop() {
  // Heartbeat LED
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = (ledState == LOW) ? HIGH : LOW;
    digitalWrite(statusLed, ledState);
  }

  // Handle Client
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

// Movement Logic
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