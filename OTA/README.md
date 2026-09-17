# CalmNest ESP32 S3 OTA Reference

This folder contains the validated engineering OTA baseline for the CalmNest ESP32 S3 MINI 1.

## Validated environment

- Test date: 2026-09-17
- Board profile: ESP32S3 Dev Module
- ESP32 Arduino core: 3.3.0
- OTA hostname: `calmnest-s3`
- OTA port: `3232`
- LED_EN test GPIO: `39`

## Files

### `CalmNest_ESP32S3_OTA_Minimum_Proof_Core330.ino`
Minimum WiFi and ArduinoOTA proof firmware.

### `CalmNest_ESP32S3_OTA_LED39_Final_Working_Core330.ino`
Final validated engineering reference. Includes WiFi reconnect, OTA callbacks, status diagnostics, and GPIO39 LED_EN blink test.

### `CalmNest_ESP32S3_OTA_LED39_FastBlink_Update_Core330.ino`
OTA update proof build using a 250 ms LED blink interval to verify that a real application behavior change was delivered through WiFi.

## Important validation result

ESP32 Arduino core 3.3.11 reached WiFi connection and OTA discovery but the OTA handshake failed in this test setup. Rebuilding the same OTA baseline with core 3.3.0 allowed the network firmware transfer to complete successfully.

## WiFi credentials

The repository copies use placeholders:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

Replace them locally before compiling.

## Production note

OTA authentication is intentionally disabled in these engineering test builds. Do not use this configuration as the final customer update mechanism. Production firmware should add authentication, secure firmware delivery, version control, integrity verification, and recovery or rollback behavior.
