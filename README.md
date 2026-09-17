# CalmNest Beta S3 2026

CalmNest ESP32 S3 firmware repository for the 2026 hardware revision.

## Repository structure

- `Main_Firmware/` contains the main CalmNest application firmware area.
- `OTA/` contains validated OTA reference and test firmware.
- `Documentation/OTA/` contains OTA validation notes and evidence references.

## Validated OTA baseline

Validated on 2026-09-17 with:

- MCU: ESP32 S3 MINI 1
- Arduino board profile: ESP32S3 Dev Module
- ESP32 Arduino core: 3.3.0
- OTA hostname: `calmnest-s3`
- OTA port: `3232`
- CalmNest LED_EN GPIO: `39`
- WiFi OTA upload: PASS

During validation, ESP32 Arduino core 3.3.11 reached OTA discovery but the OTA handshake failed. Rebuilding and running the OTA firmware with core 3.3.0 completed the network firmware upload successfully.

## Security

WiFi credentials are intentionally not stored in this public repository. Replace the placeholders locally before testing.

OTA authentication is disabled in the engineering reference firmware. Add authentication and production update security before customer deployment.

## Status

This repository currently contains the validated engineering OTA baseline. It is not yet the final production CalmNest firmware.
