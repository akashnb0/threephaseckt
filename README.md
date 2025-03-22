# Wireless Next-Generation Three-Phase Power Failure Monitoring with IoT in Smart Urban Networks

This project implements an IoT-based system to monitor three-phase power networks (R, Y, B phases) in real-time. It detects faults like phase loss or earth faults and sends instant alerts via the Blynk IoT platform, aiming to enhance the reliability and efficiency of smart urban power distribution. 
## Project Overview

The system uses an Arduino Mega 2560 as the central microcontroller, interfaced with sensors (e.g., ACS712 for current up to 20A) and communication modules (NodeMCU ESP8266 for WiFi, Ai Thinker A9 for GSM backup). It monitors voltage, current, and power quality across three phases, displaying results locally on a 16x2 LCD with I2C interface and remotely via Blynk IoT. Designed for scalability, it suits both overhead and underground urban power networks, reducing downtime through automated fault detection and alerts.

## Features

- Real-time monitoring of voltage, current, and power quality across R, Y, B phases.
- Automated fault detection for phase imbalances, voltage drops, and earth faults.
- Remote notifications and data visualization via Blynk IoT app.
- Local display of readings and fault status on a 16x2 LCD.
- Scalable design for diverse power infrastructures.
- Backup SMS alerts via GSM if WiFi connectivity fails.

## Technical Skills

### Hardware
- Arduino Mega 2560 programming and sensor interfacing.
- ACS712 current sensor and voltage sensor integration.
- Circuit prototyping with relays, transformers, and breadboards.

### Software
- Embedded C/C++ for Arduino Mega and NodeMCU ESP8266.
- Blynk IoT platform configuration and data handling.
- Serial communication between Arduino and NodeMCU.

### Communication
- WiFi connectivity via ESP8266 NodeMCU.
- GSM/GPRS backup using Ai Thinker A9 module.

### Tools
- Arduino IDE for code development and upload.
- Multimeter for continuity and power-on testing.

## Hardware Setup

The system comprises:
1. **Arduino Mega 2560**: Processes sensor data and controls outputs (see `ArduinoMega.ino`).
2. **NodeMCU ESP8266**: Handles WiFi and Blynk IoT connectivity (see `NodeMCU.ino`).
3. **ACS712 Current Sensor**: Measures current flow up to 20A per phase.
4. **Voltage Sensors**: Monitor R, Y, B phase voltages.
5. **16x2 LCD with I2C**: Displays real-time data and fault alerts.
6. **Ai Thinker A9 GSM Module**: Sends SMS alerts as a fallback.
7. **Relay Module**: Activates alarms during faults.
8. **Power Supply**: Hondas 12-0-12 500mA transformer provides 12V DC.

### Hardware Visuals
- Block Diagram: 
  ![Output](screenshot/three1.jpg)
- Setup Images:
  ![Output](screenshot/three2.jpg)
  ![Output](screenshot/three3.jpg)
  
## Software Components

### ArduinoMega.ino
- **Libraries**: `EveryTimer.h`, `LiquidCrystal.h`.
- Reads analog inputs (A0-A3) for phase voltages and current.
- Controls relay (pin 2) and LCD based on fault conditions.
- Sends serialized data to NodeMCU via Serial port.

### NodeMCU.ino
- **Library**: `BlynkSimpleEsp8266.h`.
- Parses Serial data from Arduino and updates Blynk virtual pins (V0-V4).
- Sends fault notifications (e.g., "R PHASE DISCONNECTED") to Blynk app.

## Setup Instructions

### Prerequisites
- Arduino IDE (v1.8.x or later).
- Blynk app on iOS/Android.
- Hardware components listed above.
- WiFi network and optional GSM SIM.

### Steps
1. Connect sensors to Arduino Mega: A0 (R), A1 (Y), A2 (B), A3 (current).
2. Wire LCD via I2C, relay to pin 2, buzzer to pin 3.
3. Link Arduino TX/RX to NodeMCU RX/TX for Serial communication.
4. Create a Blynk project and obtain the auth token.
5. Update `NodeMCU.ino` with WiFi SSID, password, and Blynk auth token.
6. Upload `ArduinoMega.ino` to Arduino Mega and `NodeMCU.ino` to NodeMCU.
7. Power on with 12V DC and verify LCD output.

## Usage

- On startup, LCD shows "THREE PHASE POWER FAILURE" briefly.
- Real-time phase voltages (R, Y, B) and current (C) display on LCD.
- In Blynk app, monitor live data on virtual pins:
  - V0: R phase, V1: Y phase, V2: B phase, V3: Current, V4: Fault status.
- Faults (e.g., voltage < 200 or earth fault) trigger:
  - Relay activation for alarms.
  - LCD updates (e.g., "EARTH FAULT").
  - Blynk notifications to your device.

### IoT Visuals
- Blynk Interface: 
  ![Output](screenshot/three4.jpg)
  ![Output](screenshot/three5.jpg)

## Notes

- Ensure secure hardware connections before powering on.
- Use a multimeter to test continuity and avoid wiring issues.
- Blynk app requires internet for real-time updates.

### Akash S
