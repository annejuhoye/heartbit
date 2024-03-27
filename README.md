# Hearbit V2

## Description
This project enables communication between two ESP32 C3 BEETLE cards using the AP/STA (access point/station) communication mode, without the need for external communication. Each card is equipped with a button, an RGB LED and a vibrating motor. Pressing a button on ESP32 A triggers the LED and vibrating motor on ESP32 B, and vice versa.

## Components
- 2 x ESP32 C3 BEETLE
- 2 x Push Buttons
- 2 x LEDs RGB
- 2 x Vibration Motors
- Connection Wires
- Resistors (for LEDs)

## Hardware Setup
1. Connect the 2 ESP32s to a breadboard.
2. For each board, connect the push button, LED, and motor to the GPIO pins of the ESP32, which will be referred to as INTERRUPT_PIN, LedPin, and MOTOR in the code.

## Installation
1. Install the Arduino IDE and the necessary packages for ESP32.
2. Clone this repository to your local machine.
3. Open the code file in the Arduino IDE.
4. Upload the code to both ESP32 boards.

## Usage
After powering up both ESP32 boards, press the button on one of the boards. This should activate the LED and vibration motor on the other board.

## Code
The code supplied establishes direct communication between the two ESP32s. It manages the sending and receiving of messages, as well as the control of external devices (LED and vibrating motor) in response to a button input.

## Debugging
If communication between the two boards stops working:
- Make sure the lithium battery is sufficiently charged. You can charge it with the Lipo charger Type C(V1.0).

   ![charge the battery](https://github.com/annejuhoye/heartbit/blob/main/charge.png)
  
- Reload the Arduino code below onto the board, being careful with the macAdress (see the macAdress file for the code).
- If the LEDs do not light up correctly, turn off the PCBs, wait a moment, then turn them back on.
