#ifndef __led_
#define __led_

#include <FastLED.h>

FASTLED_USING_NAMESPACE


#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    30

#define BRIGHTNESS          100//96 //0-255
#define FRAMES_PER_SECOND  120 //leds refresh per second

typedef void (*SimplePatternList[])();

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void leds_init();

void updateghue();
void nextPattern(uint8_t* gCurrentPatternNumber, uint8_t pattern_list_len);
void rainbow();
void addGlitter( fract8 chanceOfGlitter);
void rainbowWithGlitter();
void confetti();
void sinelon();
void bpm();
void juggle();


#endif //__led_
