#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "Pena";
const char* password = "pasbatron";

// URL server PHP Anda
const char* serverName = "http://127.0.0.1/raspi/insert/insert_data.php";

void setup() {
  Serial.begin(115200);
  
  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Menyiapkan URL
    http.begin(serverName);
    
    // Menyiapkan data POST
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "sensor1=23.45&sensor2=54.32";
    
    // Mengirimkan request POST
    int httpResponseCode = http.POST(httpRequestData);
    
    // Mengecek response dari server
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    
    // Menutup koneksi
    http.end();
  }
  
  // Tunggu sebelum mengirim data lagi
  delay(60000); // 1 menit
}
