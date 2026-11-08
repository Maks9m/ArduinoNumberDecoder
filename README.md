# Number Decoder: Decimal → Binary Trainer on Arduino

An Arduino Uno project built in Tinkercad. On start the board picks a random decimal number and shows it on a 16×2 LCD. The user types its binary form with two buttons, one for `0` and one for `1`. When all bits are entered, a green LED lights up for a correct answer and a red LED for a wrong one.

**Live project:** [Tinkercad link](https://www.tinkercad.com/) <!-- replace with your project's share link -->

## How it works

1. `setup()` seeds the random generator, picks a number from `0` to `2^MAX_BITS − 1` (0–255 by default) and prints it on the first LCD row.
2. Each button press appends one bit to the second row (`Binary:`).
3. The program reacts to the **moment of pressing** (a LOW → HIGH transition), not to the button being held. One press adds exactly one bit, however long the button is held.
4. Entered bits are accumulated into a number without strings: `value = value * 2 + bit`.
5. After `MAX_BITS` bits the entered value is compared with the target and the matching LED turns on.

Leading zeros are required: with 8 bits, `5` is entered as `00000101`.

## Components

| Part | Qty | Purpose |
|---|---|---|
| Arduino Uno R3 | 1 | controller |
| LCD 16×2 (parallel, HD44780-compatible) | 1 | shows the number and the entered bits |
| Push button | 2 | input `0` / input `1` |
| 10 kΩ resistor | 2 | pull-down resistors for the buttons |
| 220 Ω resistor | 2 | current limiting for the LEDs |
| Green LED | 1 | correct answer |
| Red LED | 1 | wrong answer |
| Potentiometer 10 kΩ (optional) | 1 | LCD contrast |

## Wiring

| Arduino pin | Connected to |
|---|---|
| D2 | Green LED anode (through 220 Ω), cathode → GND |
| D3 | Red LED anode (through 220 Ω), cathode → GND |
| D4 | Button `0`. Other side → 5V, 10 kΩ from pin to GND |
| D5 | Button `1`. Other side → 5V, 10 kΩ from pin to GND |
| D11 | LCD RS |
| D10 | LCD E |
| D9 | LCD D4 |
| D8 | LCD D5 |
| D7 | LCD D6 |
| D6 | LCD D7 |
| A0 | left unconnected (noise source for `randomSeed`) |

LCD power: VSS and RW → GND, VDD → 5V, V0 → potentiometer wiper (contrast), backlight anode → 5V, cathode → GND. The display runs in 4-bit mode, so D0–D3 are not connected.

## Running it

1. Open the Tinkercad project link above and press **Start Simulation**.
2. Read the number on the first row.
3. Click the buttons to enter its binary form, most significant bit first.
4. To play a new round, restart the simulation.

To run it on real hardware, wire it as shown above and upload `NumberDecoder.ino` with the Arduino IDE. `LiquidCrystal` ships with the IDE.

## Configuration

| Constant | Default | Meaning |
|---|---|---|
| `MAX_BITS` | `8` | number of bits to enter. Defines the range `0 … 2^MAX_BITS − 1` |
| `CURSSOR_OFFSSET` | `8` | LCD column where the entered bits start |

`MAX_BITS` should stay at 8 or less: only 8 columns are free after `Binary:` on a 16-column display.

## Limitations

- The game ends after one answer. Restart (or reset the board) to get a new number.
- No software debounce. The Tinkercad simulator has clean button presses. Real buttons may need a short debounce delay.
- `randomSeed(analogRead(A0))` relies on electrical noise on a floating pin. On real hardware this gives a different number each run.

## Files

| File | Description |
|---|---|
| `NumberDecoder.ino` | Arduino sketch. Every line is commented (in Ukrainian) |
| `README.md` | this file |
