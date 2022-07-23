# Pro Micro Smash Stick (with analog lever)

Based on the Arduino Pro Micro (so kind of slowish) with support for analog levers. Can play on PC as a Pro Controller or Switch.

# How to

* Install the SwitchControlLibrary https://github.com/celclow/SwitchControlLibrary
* Install the AnalogLever library https://github.com/bad64/AnalogLever-ProMicro
* Flash the firmware to your Pro Micro
* Enjoy the analog !

# Modes

Plug it in, and it'll show up as a Pro Controller, with the C-Buttons showing up as the right stick and your lever of choice as the left stick.  
Hold START while plugging in, and it'll instead map like a more traditional fight stick. (AKA "FGC Mode")

```
Input         Normal Mode           FGC MODE
--------------------------------------------
C-Left       C-Stick Left               P1
C-Up          C-Stick Up                P2
C-Right      C-Stick Right              P3
Y                 Y                     P4
B                 B                     K1
X                 X                     K2
R                ZR                     K3
Z                 R                     K4
A                 A                     K1
C-Down       C-Stick Down            Nothing
START             +                  START/+
L                 L                  SELECT/-
```