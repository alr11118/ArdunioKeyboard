# Custom Matrix Keyboard

Demo gif will be added soon...
![Demo GIF](images/demo.gif)

This project was originally made for my AP Physics 1 class electronics project, it is a custom-built matrix keyboard designed and programmed from scratch using an Arduino Uno. This project explores how modern keyboards work internally by implementing custom hardware, matrix scanning, character selection logic, and a user interface using an LCD display.

## Overview

Most keyboards rely on a matrix of rows and columns to detect key presses efficiently. Instead of using a pre-built keyboard module, this project implements the complete system from the ground up, including the hardware matrix, scanning software, text entry logic, and feedback systems.

The project cosists a custom 3×3 matrix keyboard controlled by an Arduino Uno R3. The keyboard scans rows and columns to determine which key is being pressed. When a key is pressed, it creates a closed circuit between a specific row and column. The Arduino activates one row at a time and reads the column inputs to identify the location of the pressed key, reducing the number of wires needed.

The software prevents a single press from being detected multiple times.

Each key represents a group of letters similar to early mobile phone keypads. Repeated presses of the same key cycle through the available letters, and a dedicated confirm key adds the selected character to the text buffer. The current text is displayed on a 16×2 LCD screen, and a buzzer gives feedback whenever a key is pressed.

### Finished Build

<img src="Media/wired.png" alt="inished Keyboard" width="400">

## Features

* Custom 3×3 keyboard matrix
* Matrix scanning firmware
* Multi-tap character input system
* Character confirmation key
* LCD text display
* Audible keypress feedback
* Software debouncing
* Arduino Uno based

## How It Works

The keyboard is arranged as a matrix of rows and columns. The Arduino continuously scans the matrix by activating one row at a time and checking the column inputs. When a key is pressed, the row and column become electrically connected, allowing the software to identify the key location.

Each key corresponds to a group of letters. Pressing the same key repeatedly cycles through the available letters. Once the desired letter is selected, the confirm key adds it to the text buffer and displays it on the LCD screen.

## Hardware

### Components

* Arduino Uno R3
* 16×2 LCD Display
* Passive Buzzer
* Custom Keyboard Matrix
* Potentiometer
* Power supply
* Breadboard
* Copper tape
* Jumper Wires

### Pin Connections

| Component | Pins                 |
| --------- | -------------------- |
| LCD       | 8, 9, 10, 11, 12, 13 |
| Rows      | 3, 4, 2              |
| Columns   | 6, 7, 5              |
| Buzzer    | A3                   |

### Wiring Diagram

<img src="Media/circuitDiagram.png" alt="Citcuit Diagram" width="600">

## Software

The software continuously scans the keyboard matrix by activating one row at a time and checking the column inputs for a connection. When a key press is detected, the program uses the row and column location to determine which key was pressed. The software implements a debouncing system that prevents a single press from being counted multiple times. The software also implements a text entry system similar to early mobile phones, where repeatedly pressing the same key cycles through a group of letters. A dedicated confirm key adds the selected letter to the final message. The program updates the LCD display to show the current text and selected letter and activates a buzzer to provide feedback whenever a key press is pressed.

## Technical Challenges

* Designing a reliable homemade key mechanism
* Implementing matrix scanning logic
* Preventing duplicate key registrations
* Managing multi-tap character selection
* Providing real-time user feedback on a limited display

## Skills Demonstrated

* Embedded Systems Programming
* Arduino Development
* Digital Electronics
* Circuit Design
* Matrix Scanning Algorithms
* State Management
* Hardware Debugging
* Technical Documentation

## Future Improvements

* Larger keyboard matrix
* Mechanical key switches
* Predictive text input
* Custom enclosure

## More Media
Will be added soon...

## Repository Structure
```text
ArduinoKeyboard/
├── SourceCode/
|   |── KeyPad9
|       └── KeyPad9.ino          # Actual typing logic
|   └── HardwareTesting
|        └── HardwareTesting.ino # The code used for testing hardware conductivity
├── Media/
|   |── circuitDiagram.png
|   └── wired.png
└── README.md

```
## License

MIT License
