# CalmNest ESP32 S3 OTA Validation Notes

Validation date: 2026-09-17

## Final result

WiFi OTA firmware updating was successfully validated on the CalmNest ESP32 S3 MINI 1.

## Confirmed working configuration

- Board profile: ESP32S3 Dev Module
- ESP32 Arduino core: 3.3.0
- Native USB programming path: D+ and D-
- OTA hostname: `calmnest-s3`
- OTA port: `3232`
- CalmNest LED_EN GPIO: `39`
- WiFi OTA upload: completed to 100 percent
- Updated firmware rebooted and resumed OTA service successfully

## Important troubleshooting findings

1. BOOT held permanently at GND forced the ESP32 S3 into download mode. Restoring BOOT through the CalmNest BOOT switch and EN through the existing reset circuit allowed normal application boot and Serial Monitor output.
2. ESP32 Arduino core 3.3.11 allowed WiFi connection, mDNS network port discovery, and ping reachability, but the OTA handshake repeatedly returned no response from device.
3. Direct `espota.exe` testing produced the same handshake failure with core 3.3.11, ruling out the Arduino IDE network port as the only cause.
4. Rebuilding the OTA firmware using ESP32 Arduino core 3.3.0 allowed the OTA upload to complete successfully.
5. GPIO39 was used for the final CalmNest LED_EN behavior proof after OTA.

## Security note

The validated firmware is an engineering reference. WiFi credentials are excluded from the repository and OTA authentication is not enabled. Production deployment requires secure authentication, protected firmware delivery, version control, integrity verification, and recovery or rollback planning.

## Supporting evidence

The full validation report and evidence screenshots are maintained with the project validation package. The key proof points are OTA READY on the device, network discovery at the device IP, successful 100 percent OTA transfer, and the updated GPIO39 firmware running after reboot.
