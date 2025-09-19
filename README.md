# ArdLamp
**ArdLamp version 1.0 supports:**
1. RGB mode
2. "Fire" RGB mode
3. To turn off and on without fully turning on
4. 255 colors are supported
5. 255 units of brightness

**Controls:**
**When arduino is turn on:**
- Hold the encoder to turn off
- Press the encoder once to switch between color and brightness changes
- Press the encoder twice to switch between RGB and "Fire" mode
- Press the encoder once to switch between "Fire" mode and RGB
  
**When arduino is turn off:**
- Press the encoder once to turn on

**Connection:**
2, 3, 4 - encoder
6 pin - led with 100- 500 Ohm resistor

**Used libs:**
- [FastLed](https://github.com/FastLED/FastLED)
- [EncButton](https://github.com/GyverLibs/EncButton)
