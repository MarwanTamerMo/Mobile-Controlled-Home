# Mobile‑Controlled‑Home

A mobile‑controlled embedded home automation system built around an AVR ATmega32 microcontroller. Users can open a safety door, toggle lights, and trigger an emergency shutdown via Bluetooth commands—complete with real‑time feedback on an LCD and audible alerts.

> I created this repository to showcase my IMT AVR Diploma graduating project. The project uses an AVR ATmega32 microcontroller interfaced with a variety of electronics and sensors to create a mobile controlled embedded home system.

---

## Table of Contents

1. [Features](#features)
2. [Hardware Components](#hardware-components)
3. [Repository Structure](#repository-structure)
4. [Prerequisites](#prerequisites)
5. [Build & Flash](#build--flash)
6. [Usage](#usage)
7. [Configuration](#configuration)
8. [Testing](#testing)
9. [Troubleshooting](#troubleshooting)
10. [FAQ](#faq)
11. [Roadmap](#roadmap)
12. [Contributing](#contributing)
13. [License](#license)
14. [Acknowledgments](#acknowledgments)
15. [Contact](#contact)

---

## Features

* **Secure Door Control**
  ‑ Authenticate up to 10 users by username/password over Bluetooth
  ‑ Drive a servo‑actuated door lock

* **Light Control**
  ‑ Individually switch room lights on/off via mobile

* **Emergency Shutdown**
  ‑ Trigger buzzer and disable outputs in an emergency

* **Status Feedback**
  ‑ 16×2 LCD displays current mode, prompts, and errors
  ‑ Buzzer sounds for invalid commands or alerts

* **Modular Software Layers**
  ‑ **MCAL**: GPIO, UART, PWM drivers
  ‑ **HAL**: Abstractions for LCD, Bluetooth (HC‑05), buzzer, servo, motors
  ‑ **Application Logic**: User interface, credential checking, command parsing

---

## Hardware Components

| Component          | Description                            |
| ------------------ | -------------------------------------- |
| ATmega32 MCU       | Main microcontroller                   |
| HC‑05 Bluetooth    | Serial‑to‑Bluetooth bridge             |
| 16×2 LCD           | Alphanumeric display                   |
| Servo Motor        | Door lock actuator                     |
| DC Motor & Drivers | (Optional) e.g. door sliding mechanism |
| LEDs               | Status indicators                      |
| Buzzer             | Audible alert / error tone             |
| Pushbuttons (×2)   | Manual override & reset                |
| Power Supply (5 V) | Regulated for MCU and peripherals      |

---

## Repository Structure

```
/
├── MCAL/                      # Low-level: DIO, UART, PWM
├── HAL/                       # Hardware abstractions: LCD, Bluetooth, Buzzer, Servo
├── LIB/                       # Utility libraries (e.g. delay, string ops)
├── Logic Implementation Files/  # Application code
│   ├── main.c                 # System initialization & main loop
│   ├── app.c / app.h          # Application states & command parser
│   └── auth.c / auth.h        # User credential routines
└── README.md                  # This document
```

---

## Prerequisites

* **Toolchain**: AVR‑GCC, AVR‑Libc
* **Programmer**: USBasp, AVR‑DUDE or equivalent
* **Host**: Linux or Windows with appropriate drivers
* **Mobile App**: Any Bluetooth‑serial terminal (e.g. “Serial Bluetooth Terminal” on Android)

---

## Build & Flash

1. **Clone the repo**

   ```bash
   git clone https://github.com/MarwanTamerMo/Mobile-Controlled-Home.git
   cd Mobile-Controlled-Home
   ```

2. **Compile**

   ```bash
   avr-gcc -mmcu=atmega32 -Os -I./MCAL -I./HAL -I./LIB \
     MCAL/*.c HAL/*.c "Logic Implementation Files"/*.c -o build/main.elf
   avr-objcopy -O ihex build/main.elf build/main.hex
   ```

3. **Flash**

   ```bash
   avrdude -c usbasp -p m32 -U flash:w:build/main.hex
   ```

---

## Usage

1. **Power up** the board and ensure Bluetooth HC‑05 is in pairing mode (`1234` default PIN).
2. **Pair** from your phone’s Bluetooth settings.
3. **Open** your serial‑terminal app (baud: **9600**, **8N1**).
4. **Authenticate** by entering your username and password when prompted.
5. **Send commands**:

   * `LIGHT_ON` / `LIGHT_OFF`
   * `DOOR_OPEN`
   * `EMERGENCY` (shutdown)
6. **View feedback** on the LCD and listen for buzzer alerts.

---

## Configuration

Before building, you can customize:

* **User Credentials**: Edit `auth.h` to add/remove usernames and passwords.
* **Command Keywords**: Modify command strings in `app.c` to suit your preference.
* **Pins & Ports**: Adjust pin definitions in `MCAL/dio.h` for your hardware setup.

---

## Testing

1. **Unit tests** (if implemented) can be run via your chosen AVR simulator (e.g., simAVR).
2. **Integration test**: Use the mobile app to cycle through all commands and verify:

   * Door actuator response
   * Light toggling
   * Emergency shutdown behavior
   * LCD and buzzer feedback

---

## Troubleshooting

* **Bluetooth not pairing**: Ensure HC‑05 is powered at 5 V and in AT mode if reconfiguration is needed.
* **No LCD output**: Check contrast pot and wiring (RS, E, D4–D7).
* **Command ignored**: Verify baud rate and spelling in terminal app.
* **Door not moving**: Confirm servo power and correct PWM pin mapping.

---

## FAQ

**Q:** Can I add more than 10 users?
**A:** Yes—adjust array sizes in `auth.c` and ensure memory limits are respected.

**Q:** Can I use a different microcontroller?
**A:** The code targets ATmega32, but you can adapt timers and registers for other AVR MCUs.

**Q:** How do I reset to factory settings?
**A:** Press and hold the manual reset button for 5 seconds during boot.

---

## Roadmap

* [ ] Smartphone app with GUI
* [ ] Add sensor inputs (temperature, motion)
* [ ] Secure OTA firmware updates

---

## Contributing

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/my-feature`).
3. Commit your changes (`git commit -m "Add my feature"`).
4. Push to your branch (`git push origin feature/my-feature`).
5. Open a pull request.

---

## Acknowledgments
* Eng.Ahmed Abo El-Nour (IMT School Embbedded Systems Instructor and Senior Engineer at Valeo)
* IMT School (Coretech Company)
* AVR‑GCC & AVR‑Libc communities
* HC‑05 module documentation
* LCD1602 tutorials and examples

---

## Contact

Marwan Tamer – [Linkedin](https://www.linkedin.com/in/marwan-tamer-abdelmoneim/) – [marwan-tamer@ieee-zsb.org](mailto:marwan-tamer@ieee-zsb.org)
