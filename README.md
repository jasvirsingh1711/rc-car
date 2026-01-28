# 🏎️ WiFi Combat/Racing Robot (Dual-Driver Edition)

A high-performance, 4-wheel drive (4WD) skid-steer robot controlled via Wi-Fi using an ESP8266 NodeMCU. This project features a **Dual-Driver, Dual-Battery architecture** to maximize power delivery and prevent microcontroller resets during high-load scenarios.


## Features
* **Wi-Fi Control:** Creates its own Hotspot (Access Point). No router needed.
* **Dual Power Systems:** Separate batteries for Left and Right motors to handle high current.
* **High Stability:** Uses a Buck Converter to provide clean 5V power to the "Brain" (ESP8266).
* **Safety Features:** "Heartbeat" Status LED and "Stop-on-Release" logic.
* **Custom App Interface:** Compatible with RoboRemoFree (TCP).

---

##  Hardware Requirements (BOM)

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **NodeMCU v1.0** | 1 | ESP8266 Wi-Fi Development Board |
| **L298N Motor Driver** | 2 | Dual H-Bridge Driver (One for Left, One for Right) |
| **DC Gear Motors** | 4 | Yellow TT Motors (or similar 3V-6V motors) |
| **Wheels** | 4 | Compatible with your motors |
| **Li-ion Batteries** | 4 | 18650 Cells (Configured as 2 separate 7.4V packs) |
| **Buck Converter** | 1 | LM2596 (Step-down module) |
| **Switch** | 1 | Rocker Switch (For Main Logic Power) |
| **Chassis** | 1 | Robot frame/body |

---
![alt text](images-videos/circuit.jpg)
## 🔌 Wiring Guide (The Architecture)

This robot uses a **Split-Power Island** design.

### 1. The Left Island (Powering Left Motors)
* **Battery A (7.4V):**
    * Red (+) → **Driver 1 [12V]**
    * Black (-) → **Driver 1 [GND]**
* **Motors:** Left Front & Left Back motors connected to **Driver 1 [OUT3 & OUT4]**.

### 2. The Right Island (Powering Right Motors + Brain)
* **Battery B (7.4V):**
    * Red (+) → **Switch** → **Driver 2 [12V]**
    * Black (-) → **Driver 2 [GND]**
    * *Branch:* Also connect Battery B to **Buck Converter [IN+ / IN-]**.
* **Motors:** Right Front & Right Back motors connected to **Driver 2 [OUT3 & OUT4]**.

### 3. The "Brain" Power (5V Logic)
* **Buck Converter Output:** Set to **5.0V**.
    * OUT (+) → NodeMCU **VIN**
    * OUT (-) → NodeMCU **GND**

### 4. Common Ground (CRITICAL)
* You **MUST** connect a wire between **Driver 1 [GND]** and **Driver 2 [GND]**.

### 5. Signal Connections (NodeMCU to Drivers)
* **Jumpers:** Ensure Black Enabler Caps are **ON** for ENB on both drivers.

| NodeMCU Pin | Connects To | Function |
| :--- | :--- | :--- |
| **D1** (GPIO 5) | Driver 1 **IN3** | Left Wheels Direction A |
| **D2** (GPIO 4) | Driver 1 **IN4** | Left Wheels Direction B |
| **D5** (GPIO 14) | Driver 2 **IN3** | Right Wheels Direction A |
| **D6** (GPIO 12) | Driver 2 **IN4** | Right Wheels Direction B |

---

## Software Setup

### Option 2: PlatformIO

1.  **Install PlatformIO:**
    * **VS Code:** Install the [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode) from the Extensions marketplace.

2.  **Create New Project:**
    * Click on **"New Project"** in the PlatformIO home screen.
    ![New Project Button](Platform.io/1.png)

3.  **Configure Project:**
    * **Board:** Select **"NodeMCU 1.0 (ESP-12E Module)"** (ESP8266-based board).
    * Click **"Finish"**.
    ![Board Selection](Platform.io/2.png)
    * **Note:** First-time users may experience a brief setup delay. Please be patient while PlatformIO downloads the necessary tools and frameworks.

4.  **Add Your Code:**
    * Copy the entire contents of `Code/main.cpp` from this repository.
    * Paste it into `src/main.cpp` in your PlatformIO project (replacing any existing code).

5.  **Build and Upload:**
    * Click the **✓ (checkmark)** icon to build the project.
    * Click the **→ (arrow)** button to upload the code to your NodeMCU.
    ![Build and Upload Buttons](Platform.io/3.png)

6.  **Connect to Robot:**
    * After the code uploads successfully, the Wi-Fi server will automatically start.
    * You can now proceed to configure your mobile device (see App Configuration section below).

---

## App Configuration (RoboRemoFree)

1.  **Download:** Install **RoboRemoFree** from the Google Play Store.
2.  **Connect:**
    * Turn off Mobile Data on your phone.
    * Connect Wi-Fi to **"Utkarsh_Robot"** (Password: `password1234`).
3.  **App Settings:**
    * Menu > Connect > **Internet (TCP)**.
    * IP: `192.168.4.1` | Port: `80`.
4.  **UI Setup:**
    * Create 4 buttons (Forward, Back, Left, Right).
    * **Press Action:** `F`, `B`, `L`, `R`.
    * **Release Action:** Set ALL buttons to send `S` on release.

---

⚠️ Important Safety & Maintenance
Phantom Drain Warning: The Left Battery (Battery A) is connected directly to the motor driver. Even when the robot is "Off", the driver consumes small amounts of power. ALWAYS unplug Battery A when not in use, or the battery will be destroyed.

Mobile Data: If the app fails to connect ("Socket Timeout"), ensure Mobile Data is turned OFF on your phone.

Heat Check: After aggressive driving, check the black heatsinks on the L298N drivers. Warm is okay; too hot to touch means you need a break.

 Contributing
Feel free to fork this project and add features like Speed Control (PWM) or Obstacle Avoidance sensors!