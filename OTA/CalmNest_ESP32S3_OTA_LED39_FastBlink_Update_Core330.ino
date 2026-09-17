#include <WiFi.h>
#include <ArduinoOTA.h>

// CalmNest ESP32 S3 OTA + LED_EN fast blink update proof
// Working test configuration confirmed on 2026-09-17
// ESP32 by Espressif Systems core: 3.3.0

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const char* otaHostname = "calmnest-s3";
#define OTA_PORT 3232

#define LED_PIN 39

bool ledState = false;
unsigned long previousBlinkMillis = 0;
const unsigned long blinkInterval = 250;

unsigned long previousStatusMillis = 0;
const unsigned long statusInterval = 5000;

void connectWiFi() {
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if (millis() - startTime > 20000) {
      Serial.println();
      Serial.println("WiFi connection timeout");
      return;
    }
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void setupOTA() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("OTA not started because WiFi is disconnected");
    return;
  }

  ArduinoOTA.setHostname(otaHostname);
  ArduinoOTA.setPort(OTA_PORT);

  // OTA password intentionally disabled for this engineering test.
  // Add authentication before production use.

  ArduinoOTA.onStart([]() {
    Serial.println();
    Serial.println("OTA UPDATE STARTED");
    digitalWrite(LED_PIN, HIGH);
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    static int previousPercent = -1;
    int percent = (progress * 100U) / total;
    if (percent != previousPercent && percent % 10 == 0) {
      Serial.print("OTA progress: ");
      Serial.print(percent);
      Serial.println("%");
      previousPercent = percent;
    }
  });

  ArduinoOTA.onEnd([]() {
    Serial.println();
    Serial.println("OTA UPDATE COMPLETE");
    Serial.println("Restarting ESP32 S3");
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("OTA error code: ");
    Serial.println((int)error);
  });

  ArduinoOTA.begin();

  Serial.println();
  Serial.println("==============================");
  Serial.println("OTA READY");
  Serial.print("Hostname: ");
  Serial.println(otaHostname);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("OTA port: ");
  Serial.println(OTA_PORT);
  Serial.println("==============================");
}

void updateLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousBlinkMillis >= blinkInterval) {
    previousBlinkMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}

void maintainWiFi() {
  static unsigned long previousReconnectMillis = 0;

  if (WiFi.status() == WL_CONNECTED) return;

  unsigned long currentMillis = millis();
  if (currentMillis - previousReconnectMillis >= 5000) {
    previousReconnectMillis = currentMillis;
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
  }
}

void printStatus() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousStatusMillis >= statusInterval) {
    previousStatusMillis = currentMillis;

    Serial.print("STATUS | WiFi: ");
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("CONNECTED");
      Serial.print(" | IP: ");
      Serial.print(WiFi.localIP());
      Serial.print(" | RSSI: ");
      Serial.print(WiFi.RSSI());
      Serial.print(" | OTA PORT: ");
      Serial.println(OTA_PORT);
    } else {
      Serial.println("DISCONNECTED");
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("CALMNEST ESP32 S3 OTA TEST");
  Serial.println("OTA UPDATE PROOF FAST BLINK BUILD");
  Serial.println("==============================");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  connectWiFi();
  setupOTA();

  Serial.println();
  Serial.println("LED blink test running");
}

void loop() {
  ArduinoOTA.handle();
  maintainWiFi();
  updateLED();
  printStatus();
  delay(2);
}
