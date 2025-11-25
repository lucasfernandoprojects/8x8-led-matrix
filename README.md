# 8x8 RGB LED Matrix (Custom PCB Project)

This repository contains everything you need to build, assemble, and program your own 8x8 RGB LED matrix, fully designed as a custom PCB and manufactured using [JLCPCB’s fabrication and assembly services.](https://jlcpcb.com/)

This project started as a personal challenge: could I design my own WS2812B matrix from scratch, send it to manufacturing, and get a fully assembled board that actually works on the first try? I wasn’t sure, especially because this was my first time using PCB assembly. But once the box arrived and I plugged it in… seeing it light up was surreal. And now, you can build the exact same board.

## ⭐FEATURES

+ **64 WS2812B LEDs** arranged in an 8×8 grid
+ Precise spacing and clean routing
+ **Daisy‑chain support** (DOUT → DIN) for connecting multiple matrices
+ Designed for **5V input**
+ Right‑angle 4‑pin connector for easy chaining
+ Fully compatible with Arduino, ESP32, Raspberry Pi, and other microcontrollers

## ⚠️POWER & SAFETY WARNINGS

### High Current Requirement
WS2812B LEDs can draw up to **60 mA each at full white**. With 64 LEDs:
+ **Max brightness draw**: ~4A
+ **Matrix PCB rating**: ~2A

> [!WARNING]
> **Therefore, brightness must be limited to ~50%** to avoid overheating traces. **Avoid powering the LEDs directly from a microcontroller pin**. Use a dedicated 5V 2A power supply. If you chain multiple matrices, inject power to each board.

### Multiple Panels

The board supports clean chaining:
```
Matrix 1: DOUT → Matrix 2: DIN
Matrix 2: DOUT → Matrix 3: DIN
...
```
Make sure **all grounds are connected**, especially if using separate supplies.

## 📁REPOSITORY STRUCTURE

### Hardware Files
| File | Description |
| ---- | ----------- |
| matrix-rgb-gerber.zip	| Gerber files for PCB manufacturing |
| matrix-led-bom.csv | Bill of Materials for assembly |
| matrix-led-cpl.csv | Pick‑and‑place file for automated component placement |

### Firmware
| File | Description |
| ---- | ----------- |
| animations.ino | Arduino sketch to test color patterns and validate the board|

## 🛠️HOW TO ORDER THE PCB (Sponsored by JLCPCB)

This project is proudly sponsored by [JLCPCB](https://jlcpcb.com/), who handled both the PCB manufacturing and full assembly for this matrix. If you’ve never ordered an assembled PCB before, this is honestly the easiest way to turn an idea into real hardware.

You design your board → upload the files → choose the assembly options → and a few days later, you get a professional, fully assembled module at your doorstep. No soldering 64 LEDs by hand. No dealing with reflow. No headaches.

I used JLCPCB’s PCBA service, which places places the components automatically, but also offering by hand soldering when you need it. They even added edge rails to the PCB so the machines could hold it properly during reflow.

Here’s the exact configuration used to manufacture this board:

### 1. Upload the Gerbers
Upload matrix-rgb-gerber.zip at JLCPCB.

### 2. PCB Options
+ Layers: 2
+ Color: Black
+ Thickness: Default
+ Surface finish: Default
+ Edge rails: Added automatically by JLCPCB (needed for assembly)

### 3. Assembly Options
+ PCBA Type: Standard
+ Side: Top only
+ Quantity: As needed

### 4. Components Used (LCSC Codes)
+ WS2812B LEDs: C22371521
+ 100 nF capacitors: C49678
+ Right‑angle 4‑pin header: C91552 (requires wave soldering)

### 5. Upload Assembly Files
Upload:
+ matrix-led-bom.csv
+ matrix-led-cpl.csv

JLCPCB’s web viewer automatically shows part placement, orientation, and polarity.

### 6. Confirm & Order

Check the 3D preview, confirm everything looks correct, and place the order.

A few days later, the assembled matrices arrived. This was my first time using PCB assembly, so I genuinely didn’t know if the project would work. But after powering up the board with the test sketch, everything lit up perfectly on the first try (a very satisfying moment).

## 🔌WIRING GUIDE
## Single Matrix Wiring
```
5V  → 5V
GND → GND
DIN → Microcontroller pin
```
Recommended:
+ 5V external supply, not USB power

### Chaining Multiple Matrices
```
Matrix A DOUT → Matrix B DIN
Matrix B DOUT → Matrix C DIN
```
Before turning on, make sure:
+ Brightness stays reasonable

## 💡USING THE TEST ANIMATIONS

Open **animations.ino** and upload it to your Arduino board. Make sure you have installed the library **Adafruit Neoxpixel**.

Included patterns:
+ Color wipe
+ Rainbow
+ Sparkle effect
+ Basic waves
+ Solid color test

These tests help confirm:
+ LED orientation
+ Data signal integrity
+ No cold solder joints
+ Power stability

## 📐DESIGN NOTES

A few engineering decisions behind the board:
+ Each WS2812B has its own 100nF capacitor for stability.
+ Power traces were sized for ~2A continuous current.
+ Right‑angle connectors were chosen for cleaner cable management.

## 🚀FINAL THOUGHTS

If you're learning PCB design, LED driving, or embedded systems, this project is the perfect mix of challenge and reward. It proves that even as a beginner, you can build hardware that feels professional.

Remember, **you can invent anything you set your mind to**.

Feel free to fork the project, redesign the layout, or build a giant display by chaining multiple panels.

## 🧱LICENSE

This project is released under the GPL‑3.0 License.

You are free to modify, study, and share it as long as derivatives remain open‑source under the same license.

Enjoy building your matrix🔥
