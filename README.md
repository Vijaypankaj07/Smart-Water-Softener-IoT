# Smart Water Softener IoT Controller

An IoT-based Smart Water Softener monitoring and control system developed using **ESP32**, **MQTT**, **Node-RED**, and **Wokwi**. The system continuously monitors water quality parameters, displays them on a live dashboard, generates alerts, and supports remote regeneration.

---

## 📌 Project Overview

This project simulates a Smart Water Softener Controller that monitors:

- 💧 Water Flow
- ⚙️ Water Pressure
- 🧂 Salt Level
- 🌊 TDS (Total Dissolved Solids)

The ESP32 publishes sensor data to an MQTT broker. Node-RED subscribes to the data, processes it, and displays a real-time dashboard. Users can also start the regeneration process remotely using a dashboard button.

---

## ✨ Features

- Real-time sensor monitoring
- MQTT Publish & Subscribe communication
- Live Node-RED dashboard
- Water Flow Gauge
- Pressure Gauge
- Salt Level Gauge
- TDS Gauge
- Current Device State
- Alert Status
- Regeneration Status
- Last Updated Time
- Activity History
- Remote Regeneration Button
- State Machine Implementation

---

## 🛠 Technologies Used

| Technology | Purpose |
|------------|---------|
| ESP32 | IoT Controller |
| Arduino IDE | Firmware Development |
| Wokwi | ESP32 Simulation |
| MQTT | Communication Protocol |
| Node-RED | Dashboard & Data Processing |
| GitHub | Version Control |

---

## 📡 MQTT Topics

### Telemetry Topic

```
ecowell/watersoftener/data
```

Published Data:

```json
{
  "flow": 24,
  "pressure": 38,
  "salt": 55,
  "tds": 210,
  "state": "MONITORING",
  "alert": "NORMAL"
}
```

### Control Topic

```
ecowell/watersoftener/control
```

Command:

```
START
```

Starts the regeneration process remotely.

---

## 🔄 Device States

- IDLE
- MONITORING
- REGENERATION_REQUIRED
- REGENERATION_RUNNING
- FAULT

---

## 🚨 Alert Conditions

| Condition | Alert |
|-----------|-------|
| Pressure < 25 PSI | LOW PRESSURE |
| Flow = 0 | NO WATER FLOW |
| Salt < 20% | LOW SALT |
| TDS > 500 ppm | HIGH TDS |

---

## 📊 Dashboard

The Node-RED dashboard displays:

- Water Flow
- Pressure
- Salt Level
- TDS
- Current State
- Alert Status
- Regeneration Status
- Last Updated Time
- Activity History
- Start Regeneration Button

---

## 🏗 System Architecture

```
                Smart Water Softener

      Simulated Sensors (Wokwi)
     ┌──────────────────────────┐
     │ Flow                     │
     │ Pressure                 │
     │ Salt Level               │
     │ TDS                      │
     └────────────┬─────────────┘
                  │
                  ▼
             ESP32 Controller
                  │
          Wi-Fi / MQTT Publish
                  │
                  ▼
         MQTT Broker
    (test.mosquitto.org)
                  │
        MQTT Subscribe
                  │
                  ▼
             Node-RED
                  │
                  ▼
         Live Dashboard
                  │
                  ▼
      Remote Regeneration Control
```

---

## 📁 Repository Structure

```
Smart-Water-Softener-IoT
│
├── README.md
├── sketch.ino
├── flows.json
├── dashboard.png
├── node-red-flow.png
├── wokwi.png
├── serial-monitor.png
└── architecture.png
```

---

## ▶️ How to Run

1. Open the project in Wokwi.
2. Start the ESP32 simulation.
3. Start Node-RED.
4. Import `flows.json`.
5. Deploy the flow.
6. Open the dashboard:

```
http://localhost:1880/ui
```

7. Monitor live sensor values.
8. Click **Start Regeneration** to send a control command.

---

## 🚀 Future Improvements

- Real sensors instead of simulated values
- Cloud database integration
- Mobile application
- Email/SMS notifications
- Historical data logging
- Predictive maintenance using Machine Learning

---

## 👨‍💻 Author

**Pankaj Vijay Vargiya**

M.Tech – Embedded Systems

NIELIT Calicut

Email: vijaypankaj0707@gmail.com

LinkedIn: https://www.linkedin.com/in/pankaj-vijay-vargiya-1976bb172
