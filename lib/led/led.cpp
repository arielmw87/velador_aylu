
#include "led.h"

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
CRGB leds[NUM_LEDS];

void leds_init(){

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}

void updateghue(){
    gHue++;
}

void nextPattern(uint8_t* gCurrentPatternNumber, uint8_t pattern_list_len)
{
  // add one to the current pattern number, and wrap around at the end
  *gCurrentPatternNumber = (*gCurrentPatternNumber + 1) % pattern_list_len;
}

void addGlitter( fract8 chanceOfGlitter)
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}


//------------------------------------------------------------
// Funciones que se llaman para los distintos efectos
//------------------------------------------------------------


void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}
//------------------------------------------

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}
//------------------------------------------

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}
//------------------------------------------

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}
//------------------------------------------

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
//------------------------------------------

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
//------------------------------------------
void magentaWithGlitter(){

  fill_solid( &leds[0], NUM_LEDS, CRGB::Magenta );
//  for( int i = 0; i < NUM_LEDS; i++) {
//    leds[i]=CRGB::Magenta;
//  }
  fadeToBlackBy( leds, NUM_LEDS, 150);
  addGlitter(80);

}
//------------------------------------------
