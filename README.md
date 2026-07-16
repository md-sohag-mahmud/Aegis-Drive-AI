# 🚗 IoT-Based Smart Vehicle Safety System (Aegis-Drive-AI)

An AI-assisted Advanced Driver Assistance System (ADAS) integrated with IoT and Embedded Systems designed to prevent road accidents and ensure vehicle data monitoring in real-time.

## 📊 System Connection Diagram
এখানে আপনার সার্কিট ডায়াগ্রামটি সরাসরি ডিসপ্লে হবে:
![Connection Diagram](Images/Connection%20Diagram.png)

## 🌟 Core Features & Modules
- **Accident Prevention & Detection:** Uses an **Ultrasonic Sensor (HC-SR04)** for real-time frontal obstacle detection and an **MPU6050 Gyro/Accel sensor** to instantly detect vehicle rollover or accidents.
- **Driver & Environment Safety:** Integrated with an **MQ-3 Alcohol Sensor** to detect drunk driving (restricts vehicle ignition) and an **MQ-4 Gas Sensor** to identify hazardous gas leaks inside the vehicle.
- **Fire Monitoring:** Features a **Flame/Fire Sensor** to detect engine or short-circuit fires instantly.
- **Instant Alerts & Cloud Sync:** Triggers an on-board **Buzzer and I2C LCD Display** during emergencies, while simultaneously sending live push notifications to the user's mobile via the **Blynk IoT Cloud Platform**.

## 🛠️ Hardware & Component Mapping (NodeMCU ESP8266)

| Component | Sensor Pin | NodeMCU Pin | Power Line |
| :--- | :---: | :---: | :---: |
| **Ultrasonic Sensor** | TRIG / ECHO | D5 / D6 | 5V / GND |
| **MPU6050 (Gyro/Accel)** | SDA / SCL | D2 / D1 | 3.3V / GND |
| **LCD Display (I2C)** | SDA / SCL | D2 / D1 | 5V / GND |
| **MQ-4 Gas Sensor** | AO (Analog) | A0 | 5V / GND |
| **Flame/Fire Sensor** | DO (Digital) | D3 | 5V / GND |
| **MQ-3 Alcohol Sensor** | DO (Digital) | D4 | 5V / GND |
| **Output LED / Buzzer** | Positive (+) | D7 / D8 | GND |

## 📁 Repository Structure
- `Code/` : Contains the complete master Arduino IDE firmware code (`.ino`) for the ESP8266.
- `Docs/` : Complete academic project report, pin connection guides, and system design documents.
- `Images/` : Block diagrams and hardware schematics.

## 🚀 Future Scopes
1. **GPS & GSM Integration:** Adding GPS modules to text real-time Google Maps coordinates directly to emergency services (e.g., 999 in Bangladesh) during crashes.
2. **AI-Driven Camera Monitoring:** Image processing to detect driver drowsiness and sleep alerts.
