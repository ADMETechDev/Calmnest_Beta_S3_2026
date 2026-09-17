#include <WiFi.h>
#include <ArduinoOTA.h>

// CalmNest ESP32 S3 minimum OTA proof firmware
// Validated setup: ESP32 by Espressif Systems core 3.3.0

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const char* otaHostname = "calmnest-s3";
const uint16_t otaPort = 3232;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("CALMNEST ESP32 S3 MINIMUM OTA TEST");

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.setHostname(otaHostname);
  ArduinoOTA.setPort(otaPort);
  ArduinoOTA.begin();

  Serial.println("OTA READY");
  Serial.print("OTA hostname: ");
  Serial.println(otaHostname);
  Serial.print("OTA port: ");
  Serial.println(otaPort);
}

void loop() {
  ArduinoOTA.handle();
  delay(2);
}
