// Насткройки
// ------------------------------
#define LED_NUM 60    // количество светодиодов
#define volt 5 // ограничение ленты по вольтам
#define miliAmp 1 // ограничение ленты по амперам
#define stepsForLight 5 // на сколько будет изменятся яркость при вращении. Значения 0-100; 100 / stepsForLight = доступное количество яркости
#define stepsForColor 5 // на сколько шагов будет менятся свет при вращении. Значения 0-255; 255 / stepsForColor = доступное количество цветов

int lightLevel = 50; // начальный уровень света при первом запуске. Значения 0-100;
int colorLevel = 0; // начальный цвет при первом запуске. Значения 0-255;
// ------------------------------

#define CLK 3
#define DT 4
#define SW 5

#define LED_PIN 6


#include <GyverEncoder.h>
#include <FastLED.h>

Encoder enc(CLK, DT, SW);
CRGB leds[LED_NUM];

bool turnOn = false;
bool fireMode = false;
bool light = true;



void setup() {
  FastLED.addLeds< WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setMaxPowerInVoltsAndMilliamps(volt, miliAmp);

  FastLED.clear();
  FastLED.show();
}

void loop() {
  enc.tick();

  if(enc.isHolded()){
    if(turnOn){
      turnOn = false;

      FastLED.clear();
      FastLED.show();      
    }

    else{
      turnOn = true;

      FastLED.setBrightness(lightLevel);
      for (int i = 0; i < LED_NUM; i++) {
        leds[i].setHue(colorLevel);
      }
      FastLED.show(); 
    }
  }

  if (fireMode){
    
  }

  else{
    if(enc.isTurn()){
      if(light){
        if(enc.isRight() || enc.isRightH()){
          lightLevel += stepsForLight;
        }

        else{
          lightLevel -= stepsForLight;
        }

        FastLED.setBrightness(lightLevel);
        FastLED.show();
      }

      else{
        if(enc.isRight() || enc.isRightH()){
          if(colorLevel + stepsForColor < 255){
            for (int i = 0; i < LED_NUM; i++) {
              leds[i].setHue(colorLevel + stepsForColor);
            }
          }

        }

        else{
          if(colorLevel - stepsForColor > 0){
            for (int i = 0; i < LED_NUM; i++) {
              leds[i].setHue(colorLevel - stepsForColor);
            }
          }
        }
        FastLED.show(); 
      }
    }

    else if(enc.isPress()){
      if(light) light = false;
      else light = true;
    }
  }
}
