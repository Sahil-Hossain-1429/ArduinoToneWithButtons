# ArduinoToneWithButtons

# Arduino Tone Keyboard

A simple yet functional **musical keyboard** built with Arduino Uno, 4 push buttons, and a piezo buzzer. Press buttons to play musical notes with proper debouncing and adjustable frequencies.

![Arduino](https://img.shields.io/badge/platform-Arduino%20Uno-blue)
![License](https://img.shields.io/badge/license-MIT-green)

---

## Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Customization](#customization)
- [Troubleshooting](#troubleshooting)
- [How It Works](#how-it-works)

---

## Features

- **4 Programmable Buttons** - Each plays a different musical note
- **Professional Debouncing** - Eliminates false button presses and noise
- **Full Note Range** - All musical notes from B0 (31 Hz) to D8 (4699 Hz)
- **Serial Debug Output** - Monitor button presses in real-time
- **Easy to Expand** - Add more buttons by changing one constant
- **Arduino Uno Compatible** - Works on all Arduino boards with minor changes
- **Low Power** - Minimal memory and resource usage

---

## Hardware Requirements

### Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Microcontroller |
| Piezo Buzzer (Passive) | 1 | 3-12V, cylindrical black module |
| Tactile Push Buttons | 4 | Standard 6mm momentary switches |
| Jumper Wires | 10+ | Male-to-male |
| Breadboard | 1 | Standard 400-point |
| 10kΩ Resistors | 4 | Optional, for debouncing (recommended) |
| USB Cable | 1 | Type B, for programming Arduino |

---

## Circuit Diagram

### Wiring Guide

```
ARDUINO UNO
┌─────────────────────────────┐
│                             │
│  Pin 2 ──→ Button 1 ──→ GND │
│  Pin 3 ──→ Button 2 ──→ GND │
│  Pin 4 ──→ Button 3 ──→ GND │
│  Pin 5 ──→ Button 4 ──→ GND │
│                             │
│  Pin 8 ──→ Buzzer (+)       │
│  GND   ──→ Buzzer (-)       │
│                             │
└─────────────────────────────┘
```

### Pin Assignment

| Arduino Pin | Component | Function |
|------------|-----------|----------|
| Pin 2 | Button 1 | Note C4 (262 Hz) |
| Pin 3 | Button 2 | Note D4 (294 Hz) |
| Pin 4 | Button 3 | Note E4 (330 Hz) |
| Pin 5 | Button 4 | Note F4 (349 Hz) |
| Pin 8 | Piezo Buzzer | Sound output |
| GND | All components | Ground connection |

### Step-by-Step Wiring

1. **Connect Buttons**:
   - Insert each button firmly into the breadboard
   - Connect one leg of each button to its Arduino pin (2, 3, 4, 5)
   - Connect the other leg to the GND rail
   - *(Optional)* Add a 10kΩ resistor from each button pin to GND for extra debouncing

2. **Connect Buzzer**:
   - Connect the buzzer's **positive leg** (+) to Arduino **Pin 8**
   - Connect the buzzer's **negative leg** (-) to **GND**

3. **Verify Connections**:
   - All buttons should connect to pins 2, 3, 4, 5
   - All negative lines should connect to GND
   - Buzzer should be properly polarized (+ to Pin 8, - to GND)

---

## Installation

### 1. Download Arduino IDE

Visit [arduino.cc/software](https://www.arduino.cc/en/software) and download the latest Arduino IDE for your operating system.

### 2. Clone or Download This Repository

```bash
git clone https://github.com/Sahil-Hossain-1429/ArduinoToneWithButtons.git
cd ArduinoToneWithButtons
```

Or download the ZIP file and extract it.

### 3. Open the Sketch

1. Launch Arduino IDE
2. Go to **File → Open**
3. Select `ArduinoToneKeyboard.ino`

### 4. Select Board and Port

1. Click **Tools → Board → Arduino AVR Boards → Arduino Uno**
2. Click **Tools → Port** and select your Arduino's COM port

### 5. Upload Code

1. Click the **Upload** button (→ icon) or press `Ctrl+U`
2. Wait for the message: `Uploading... Done uploading.`
3. The Arduino will automatically reset

---

## Usage

### Basic Operation

1. **Connect the Arduino** to your computer via USB
2. **Open Serial Monitor** (Tools → Serial Monitor, set baud rate to 9600)
3. **Press any button**:
   - Button 1 (Pin 2) → Plays C4 (262 Hz)
   - Button 2 (Pin 3) → Plays D4 (294 Hz)
   - Button 3 (Pin 4) → Plays E4 (330 Hz)
   - Button 4 (Pin 5) → Plays F4 (349 Hz)

### Serial Monitor Output

When you press Button 1, you'll see:
```
Tone Keyboard Ready!
Press buttons to play notes...
Button 1 pressed!
Button 1 released!
```

---

## Customization

### Change Note Frequencies

To make Button 1 play a different note, edit this line:

```cpp
{BUTTON_1, LOW, 0, false, NOTE_C4},  // Change NOTE_C4 to any note
```

Example: Make Button 1 play a higher note (C5):

```cpp
{BUTTON_1, LOW, 0, false, NOTE_C5},  // Now plays 523 Hz instead of 262 Hz
```

**Available notes** (in the code):
- B0 (31 Hz) to D8 (4699 Hz)
- Semitones available: CS = C# (sharp), DS = D#, FS = F#, GS = G#, AS = A#

### Change Note Duration

```cpp
#define NOTE_DURATION 500  // Change 500 to desired milliseconds
```

Examples:
- `100` = short beep (0.1 seconds)
- `500` = medium tone (0.5 seconds)
- `1000` = long tone (1 second)

### Add More Buttons

To add Button 5 and 6:

1. **Define new pins and notes**:
```cpp
#define NUM_OF_BUTTON 6     // Change from 4 to 6
#define BUTTON_5 6          // New button
#define BUTTON_6 7          // New button
```

2. **Add to button array**:
```cpp
ButtonState buttons[NUM_OF_BUTTON] = {
  {BUTTON_1, LOW, 0, false, NOTE_C4},
  {BUTTON_2, LOW, 0, false, NOTE_D4},
  {BUTTON_3, LOW, 0, false, NOTE_E4},
  {BUTTON_4, LOW, 0, false, NOTE_F4},
  {BUTTON_5, LOW, 0, false, NOTE_G4},  // New
  {BUTTON_6, LOW, 0, false, NOTE_A4}   // New
};
```

3. **Update setup() to initialize new pins**:
```cpp
pinMode(BUTTON_5, INPUT_PULLUP);
pinMode(BUTTON_6, INPUT_PULLUP);
```

4. **Wire the physical buttons** to pins 6 and 7

### Adjust Debounce Delay

```cpp
#define DEBOUNCE_DELAY 50  // Milliseconds (default: 50ms is optimal)
```

- Lower values (20ms): More responsive but risk false presses
- Higher values (100ms): More stable but slower response
- 50ms is recommended for most applications

---

## Troubleshooting

### No Sound When Pressing Buttons

**Check**:
1. ✓ Buzzer is powered (+ to Pin 8, - to GND)
2. ✓ Buzzer has power (connects to Arduino)
3. ✓ Arduino is connected to computer
4. ✓ Buttons work (check Serial Monitor for "Button X pressed!")

**Solution**: Test buzzer with this simple code:
```cpp
void setup() {
  pinMode(8, OUTPUT);
}
void loop() {
  tone(8, 262, 500);  // Play C4 for 500ms
  delay(1000);
  noTone(8);
  delay(500);
}
```

### Buttons Triggering Multiple Times Per Press

**Cause**: Electrical noise or insufficient debouncing

**Solution**:
1. Increase `DEBOUNCE_DELAY` to 75ms or 100ms
2. Add 10kΩ resistors from each button pin to GND
3. Add a 0.1µF capacitor in parallel with each button

### Serial Monitor Shows "Button X pressed!" But No Sound

**Cause**: Buzzer not connected or wrong pin

**Solution**:
1. Verify Pin 8 is connected to buzzer (+)
2. Verify GND is connected to buzzer (-)
3. Test buzzer with the test code above
4. Try a different buzzer if available

### Arduino Won't Upload Code

**Cause**: Wrong board or port selected

**Solution**:
1. Go to **Tools → Board → Arduino AVR Boards → Arduino Uno**
2. Go to **Tools → Port** and select the correct COM port
3. Restart Arduino IDE if it still doesn't work
4. Try a different USB cable

---

## How It Works

### Button Debouncing

Buttons produce electrical noise (bouncing) that causes false readings. The code uses a **time-based debouncing algorithm**:

1. **Detect Change**: When pin state changes, record the time
2. **Wait**: Wait 50ms for noise to settle
3. **Confirm**: Check if state is still the same
4. **Process**: Only then treat it as a valid button press

This ensures each button press triggers exactly once, no matter how much it bounces.

### State Tracking

Each button remembers:
- Its pin number
- Last known state (HIGH/LOW)
- When the state last changed
- Whether it's currently being pressed

This prevents the tone from playing multiple times per button press.

### Tone Generation

The `tone()` function generates a square wave at the specified frequency:
- Frequency = how many times per second the signal goes HIGH-LOW
- Duration = how long to play (milliseconds)
- `noTone()` stops the signal

---

## Resources Followed
[Arduino Official Docs](https://docs.arduino.cc/built-in-examples/digital/toneKeyboard/)

## License

This project is licensed under the **MIT License** - feel free to use, modify, and distribute.

See the [LICENSE](LICENSE) file for details.

---

**Enjoy your DIY Arduino Keyboard!**