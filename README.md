# Mobile‑Controlled‑Home

A mobile‑controlled embedded home automation system built around an AVR ATmega32 microcontroller. Users can open a safety door, toggle lights, and trigger an emergency shutdown via Bluetooth commands—complete with real‑time feedback on an LCD and audible alerts.

> I created this repository to showcase my IMT AVR Diploma graduating project. The project uses an AVR ATmega32 microcontroller interfaced with a variety of electronics and sensors to create a mobile controlled embedded home system.

---

## Features

- **Secure Door Control**  
  ‑ Authenticate up to 10 users by username/password over Bluetooth  
  ‑ Drive a servo‑actuated door lock

- **Light Control**  
  ‑ Individually switch room lights on/off via mobile

- **Emergency Shutdown**  
  ‑ Trigger buzzer and disable outputs in an emergency

- **Status Feedback**  
  ‑ 16×2 LCD displays current mode, prompts, and errors  
  ‑ Buzzer sounds for invalid commands or alerts

- **Modular Software Layers**  
  ‑ **MCAL**: GPIO, UART, PWM drivers  
  ‑ **HAL**: Abstractions for LCD, Bluetooth (HC‑05), buzzer, servo, motors  
  ‑ **Application Logic**: User interface, credential checking, command parsing  

---

## Hardware Components

| Component           | Description                                  |
|---------------------|----------------------------------------------|
| ATmega32 MCU        | Main microcontroller                         |
| HC‑05 Bluetooth     | Serial‑to‑Bluetooth bridge                    |
| 16×2 LCD            | Alphanumeric display                         |
| Servo Motor         | Door lock actuator                           |
| DC Motor & Drivers  | (Optional) e.g. door sliding mechanism       |
| LEDs                | Status indicators                             |
| Buzzer              | Audible alert / error tone                   |
| Pushbuttons (×2)    | Manual override & reset                      |
| Power Supply (5 V)  | Regulated for MCU and peripherals            |

---

## Repository Structure

