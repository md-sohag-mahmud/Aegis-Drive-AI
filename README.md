# 🚗 IoT-Based Smart Vehicle Safety System (Aegis-Drive-AI)

An advanced Internet of Things (IoT) driven Advanced Driver Assistance System (ADAS) integrated with automation to monitor real-time vehicle dynamics, ensure driver/environment safety, and execute instant cloud-based emergency notifications.

## 📊 System Architecture & Diagrams
The functional data flow and complete wiring topology are fully documented below:

### 1. Functional System Block Diagram
![Block Diagram](Images/block_diagram.png)

### 2. Complete Circuit Connection Diagram
![Connection Diagram](Images/connection_diagram.png)

## 🌟 Core Features & Automated Logic
- **Accident Prevention & Range Detection:** Uses an **Ultrasonic Sensor (HC-SR04)** to execute non-blocking frontal obstacle tracking. Triggers instant dashboard alerts if an object is within 15 cm.
- **Real-Time Crash & Flip Tracking:** Employs an **MPU6050 Accelerometer/Gyroscope** to calculate spatial tilt angles. Automatically registers a critical rollover crash condition if the tilt exceeds 45 degrees.
- **Driver Intoxication Mitigation:** Integrated with an **MQ-3 Alcohol Sensor** that runs constant digital polling. Suppresses engine start/ignition logic and sounds alerts upon detecting an intoxicated driver state.
- **Hazardous Environment Monitoring:** Continuously samples atmospheric nodes via **MQ-4 (Gas Leak)** and **Flame/Fire Sensors** to prevent on-board catastrophic failures.
- **Concurrent Cloud & Local Telemetry:** Drives an on-board **16x2 I2C LCD screen** and emergency hardware **Buzzer** while streaming high-frequency data matrices globally via the **Blynk IoT Cloud Platform**.

## 🛠️ Hardware Interfacing Profile (NodeMCU ESP8266)

| Component Layer | Sensor Node Pin | Target NodeMCU Pin | Absolute Power rail |
| :--- | :---: | :---: | :---: |
| **Ultrasonic Range Finder** | TRIG / ECHO | `D5` / `D6` | 5V / GND |
| **MPU6050 (Gyro/Accel)** | SDA / SCL | `D2` / `D1` | 3.3V / GND |
| **LCD Display (I2C Module)**| SDA / SCL | `D2` / `D1` | 5V / GND |
| **MQ-4 Cabin Gas Sensor** | AO (Analog) | `A0` | 5V / GND |
| **Flame/Fire Sensor Node** | DO (Digital) | `D3` | 5V / GND |
| **MQ-3 Alcohol Sensor** | DO (Digital) | `D4` | 5V / GND |
| **Output Warning LED** | Positive (+) | `D7` | 3.3V / GND |
| **Emergency Buzzer Array** | Positive (+) | `D8` | 3.3V / GND |

## 🌐 Blynk IoT Virtual Data Pipeline
The firmware architecture is configured under Template ID `TMPL6g-ebZ-CU` and Template Name `VehicleSafety` using the following exact telemetry channels:
- **`V0` (Output):** Live Obstacle Proximity Range Stream (cm).
- **`V1` (Output):** Real-Time Cabin Gas Concentration Value.
- **`V2` (Output):** Angular Spatial Vehicle Tilt Value (Degrees).
- **`V3` (Output):** Absolute System Hazard Alert Status Code (`SAFE` / `OBSTACLE` / `GAS LEAK` / `FIRE ALERT` / `ALCOHOL DET` / `ACCIDENT`).
- **`V4` (Output):** Boolean Fire Detection Bit state (`1` = Fire Present, `0` = Normal).
- **`V5` (Output):** Boolean Driver Intoxication state (`1` = Intoxicated, `0` = Safe).

## 📁 Repository Directory Structure
- `Code/` : Production-ready firmware configuration source file (`sketch_jun10b.ino`).
- `Docs/` : Full theoretical academic report, system parameters, and connection guides.
- `Images/` : Hardware architecture block diagrams and clean operational connection layouts.
- `Results/` : High-resolution physical hardware prototyping snapshots and performance metrics.

## 🚀 Engineering Future Scopes
- **Automatic Engine Cut-off:** Integrating active relay channels to immediately cut off or lock the vehicle's ignition loop during fire events or driver intoxication.
- **GPS & GSM Telemetry Integration:** Interfacing an external GPS engine to parse live NMEA strings and automatically text Google Maps coordinates to emergency responders (e.g., 999 in Bangladesh) during rollover events.
- **AI-Driven Camera Monitoring:** Deploying localized edge computer vision loops via dashboard-mounted camera feeds to trace driver fatigue, eye blink rate, and sleep state anomalies.
- **Automotive Blackbox Data Logger:** Designing an SPI-driven SD card storage array to maintain a continuous 10-second rolling buffer of all sensor values prior to a crash register for investigation.
