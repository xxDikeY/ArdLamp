// Насткройки
// ------------------------------
#define LED_NUM 120    // количество светодиодов
#define volt 5 // ограничение ленты по вольтам
#define miliAmp 1 // ограничение ленты по амперам
#define stepsForLight 5 // на сколько будет изменятся яркость при вращении. Значения 0-100; 100 / stepsForLight = доступное количество яркости
#define stepsForColor 5 // на сколько шагов будет менятся свет при вращении. Значения 0-255; 255 / stepsForColor = доступное количество цветов

int lightLevel = 50; // начальный уровень света при первом запуске. Значения 0-100;
int colorLevel = 0; // начальный цвет при первом запуске. Значения 0-255;
// ------------------------------

#define EB_FAST_TIME 10000

#define CLK 3
#define DT 4
#define SW 5

#define LED_PIN 6

#include <EncButton.h>
#include <FastLED.h>

EncButton enc(CLK, DT, SW);
CRGB leds[LED_NUM];

bool isBright = true;
bool turnOn = true;
bool colorMode = true;

void setup() {
    FastLED.addLeds< WS2812, LED_PIN, GRB>(leds, LED_NUM);

    Serial.begin(9600);
    FastLED.clear();
    FastLED.show();
    FastLED.setBrightness(lightLevel);
    
}


void loop() {
    enc.tick();


    if (turnOn) {
        if (enc.hold()) {
            turnOn = false;
            FastLED.setBrightness(0);
        }

        if (colorMode) {
            for (int i = 0; i < LED_NUM; i++) {
                leds[i].setHue(colorLevel);
            }
        }

        else {
            for (int i = 0; i < LED_NUM; i++) {
                leds[i] = CRGB(0, 0, 0);
            }
            FastLED.show();
        }
        Serial.print(colorLevel);
        Serial.print("_");
        Serial.println(lightLevel);

        if (enc.turn()) {
            if (isBright) {
                if (enc.right() || enc.rightH()) {
                    if (lightLevel + stepsForLight < 100) {
                        if (!colorMode) {
                            colorMode = true;
                        }
                        lightLevel += stepsForLight;
                    }
                    else colorMode = false;
                }

                else {
                    if (lightLevel - stepsForLight > 0) {
                        if (!colorMode) {
                            colorMode = true;
                        }
                        lightLevel -= stepsForLight;

                    }
                    else colorMode = false;
                }



                FastLED.setBrightness(lightLevel);
            }
            else {
                if (enc.right() || enc.rightH()) {
                    if (colorLevel + stepsForColor < 255) colorLevel += stepsForColor;
                    else colorLevel = 255;
                }

                else {
                    if (colorLevel - stepsForColor > 0) colorLevel -= stepsForColor;
                    else colorLevel = 0;
                }
            }
        }

        else if (enc.click()) {
            if (isBright) {
                isBright = false;
            }

            else {
                isBright = true;
            }
        }

    }

    else {
        if (enc.hold()) {
            turnOn = true;
            FastLED.setBrightness(lightLevel);
        }
    }
}
