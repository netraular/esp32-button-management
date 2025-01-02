# ESP32 Button Management Project

This project demonstrates how to manage and detect button presses on an ESP32 microcontroller. It includes handling single button presses, simultaneous button combinations, and visual feedback using an LVGL-based display. The project is designed to be modular and easy to extend for more complex interactions.

---

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Hardware Requirements](#hardware-requirements)
4. [Setup](#setup)
5. [Code Structure](#code-structure)
6. [Usage](#usage)
7. [Debugging](#debugging)
8. [License](#license)

---

## Overview

The ESP32 Button Management project uses three buttons connected to an ESP32 microcontroller. The system detects button presses, manages their states, and provides visual feedback on a display. The button states are represented as follows:

- **None (Grey)**: The button is not pressed.
- **Pressed (Green)**: The button is pressed individually.
- **Combo (Red)**: The button is pressed simultaneously with other buttons.

The display uses LVGL to render three circles, each representing a button. The circles animate based on the button's state, providing a smooth visual experience.

---

## Features

- **Button State Management**: Detects single and simultaneous button presses.
- **Visual Feedback**: Displays button states using colored circles with animations.
- **Debouncing**: Uses a time margin to avoid false triggers due to button bouncing.
- **Debugging Output**: Prints button states and changes to the Serial Monitor for easy debugging.

---

## Hardware Requirements

- **ESP32 Microcontroller**: The main processing unit.
- **Three Buttons**: Connected to the ESP32 for input.
- **Display**: Compatible with LVGL for visual feedback.
- **Wiring**: Connect the buttons to the ESP32 pins as defined in `config.h`.

---

## Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/netraular/esp32-button-management.git
   ```

2. **Install Dependencies**:
   - Ensure you have the ESP32 development environment set up.
   - Install the LVGL library for the display.

3. **Configure Pins**:
   - Update the pin configurations in `config.h` to match your hardware setup.

4. **Upload the Code**:
   - Use the Arduino IDE or PlatformIO to upload the code to the ESP32.

5. **Connect the Hardware**:
   - Connect the buttons and display to the ESP32 as per the pin configuration.

---

## Code Structure

The project is organized into the following files:

- `main.cpp`: Initializes the system and runs the main loop.
- `config.h`: Defines pin configurations and constants.
- `Screen.h` and `Screen.cpp`: Define the base `Screen` class for managing button states and interactions.
- `MainScreen.h` and `MainScreen.cpp`: Implement the main screen logic, including button detection and visual representation.

---

## Usage

### Behavior
- **Single Press**: Press a single button to turn its corresponding circle green and animate between green and blue.
- **Combination Press**: Press multiple buttons simultaneously to turn their corresponding circles red and animate between red and yellow.
- **Button Release**: Release a button to turn its corresponding circle grey and animate between grey and black.

### Debugging
Open the Serial Monitor to view the real-time state and changes of the buttons. The output format is:

```
State: B1=ON/OFF B2=ON/OFF B3=ON/OFF | Change: B1=YES/NO B2=YES/NO B3=YES/NO
```

---

## Debugging

The `handleButtonEvent` function prints the current state and changes of the buttons to the Serial Monitor. This helps in verifying the correctness of the button detection logic and debugging any issues.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

---