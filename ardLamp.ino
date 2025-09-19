// -------------------- НАСТРОЙКИ ----------------------------------------------------------------------------------------

#define LED_NUM 100 // кол-во светодиодов

// настройка цветового режима
int colorLevel = 0; // начальный цвет (0-255)
int colorStep = 5; // шаг изменения цвета (желательно, чтобы было кратно 5)

int lightLevel = 255; // начальная яркость (0-255)
int lightStep = 5; // шаг изменения яркости (желательно, чтобы было кратно 5)

// настройки пламени
#define HUE_GAP 21      // заброс по hue
#define FIRE_STEP 15    // шаг огня
#define HUE_START 0   // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define MIN_BRIGHT 70   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 245     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность
#define COLOR_DEBTH 2   // цветовая глубина: 1, 2, 3 (в байтах)

// -----------------------------------------------------------------------------------------------------------------------

#define LED_PIN 6   

#include <FastLED.h>
#include <EncButton.h>

CRGB leds[LED_NUM];
EncButton eb(2, 3, 4);


int whiteLevel = 0;

bool isOn = true;
bool colorMode = true;
bool colorLed = true;

int counter = 0;

void setup() {
    // Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
    FastLED.setBrightness(lightLevel);
    for (int i = 0; i < LED_NUM; i++) {
        leds[i].setHSV(0, 255, 255);
    }
    FastLED.show();
}

void loop() {
    eb.tick();

    if(isOn){
        if(colorLed){
            if (eb.turn()){
                if (eb.right()){
                    if(colorMode){
                        colorLevel = (colorLevel + colorStep > 255 + colorStep) ? 0 - colorStep : colorLevel + colorStep;
                    }
                    else{
                        lightLevel = (lightLevel >= 255) ? 0 + lightStep: lightLevel + lightStep;
                    }
                    // Serial.print("right: ");
                }
                else{
                    if(colorMode){
                        colorLevel = (colorLevel - colorStep < 0 - colorStep) ? 255 + colorStep: colorLevel - colorStep;
                    }
                    else{
                        lightLevel = (lightLevel - lightStep <= 0) ? 255 : lightLevel - lightStep;
                    }
                    // Serial.print("left ");
                }
                whiteLevel = (colorLevel + colorStep > 255 + colorStep || colorLevel - colorStep < 0 - colorStep) ? 0 : 255;
                // Serial.print(colorLevel);
                // Serial.print(" ");
                // Serial.print(whiteLevel);
                // Serial.print(" ");
                // Serial.println(lightLevel);
                for (int i = 0; i < LED_NUM; i++) {
                    leds[i].setHSV(colorLevel, whiteLevel, 255);
                }
                FastLED.setBrightness(lightLevel);
                FastLED.show();
            }

            if(eb.getClicks() == 2){
                colorLed = false;
            }
            else if(eb.click()){
                if(colorMode){
                    colorMode = false;
                }
                else{
                    colorMode = true;
                }
            }
        }
        else{
            static uint32_t prevTime;
            int val = 0;
            int h = 0;
            int s = 0;
            int v = 0;
            if (millis() - prevTime > 20) {
                prevTime = millis();
                int thisPos = 0, lastPos = 0;
                for (int i = 0; i < LED_NUM; i++) {
                    val = (inoise8(i * FIRE_STEP, counter));
                    h = colorLevel + map(val, 0, 255, 0, HUE_GAP);
                    s = constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255);
                    v = constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255);

                    leds[i].setHSV(h, s, v);
                }
                counter += 20;
                FastLED.show();
            }
            if(eb.click()){
                colorLed = true;
                for (int i = 0; i < LED_NUM; i++) {
                    leds[i].setHSV(colorLevel, whiteLevel, 255);
                }
                FastLED.show();
                colorMode = colorMode ? false : true;
            }
        }
        if(eb.holding()){
            isOn = false;
            FastLED.setBrightness(0);
            FastLED.show();
        }
    }
    else{
        if(eb.click()){
            isOn = true;
            FastLED.setBrightness(lightLevel);
            FastLED.show();
        }
    }
}
