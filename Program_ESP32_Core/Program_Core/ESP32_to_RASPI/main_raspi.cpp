#include <WiFi.h>
#include <HTTPClient.h>

// Replace these with your network and server details
const char* ssid = "Pena";
const char* password = "pasbatron";
const char* serverName = "http://192.168.1.18/esp32/update_data.php"; // URL of the PHP script

// Define GPIO pins
const int gpioPins[] = {32, 33, 25, 26, 27, 14, 12};

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize GPIO pins as inputs
  for (int i = 0; i < sizeof(gpioPins)/sizeof(gpioPins[0]); i++) {
    pinMode(gpioPins[i], INPUT);
  }
}

void loop() {
  HTTPClient http;
  String url = serverName;

  // Build URL with GPIO states
  url += "?gpio32=" + String(digitalRead(32)) +
         "&gpio33=" + String(digitalRead(33)) +
         "&gpio25=" + String(digitalRead(25)) +
         "&gpio26=" + String(digitalRead(26)) +
         "&gpio27=" + String(digitalRead(27)) +
         "&gpio14=" + String(digitalRead(14)) +
         "&gpio12=" + String(digitalRead(12));
  
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Response: " + payload);
  } else {
    Serial.println("Error: " + String(httpCode));
  }
  
  http.end();
  delay(10000); // Send data every 10 seconds
}
