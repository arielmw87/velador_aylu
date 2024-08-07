#include <Arduino.h>

#include "led.h"


// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

/*
 * uso el ejemplo FastLED "100-lines-of-code" demo reel, ya que trae
 * una serie de efectos ya hechos y una buena manera de cambiar entre
 * ellos con un vector de punteros a funcion.
 */

#define EFFECT_DURATION 15

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

void setup() {

  Serial.begin(9600);
  Serial.println("Boot...\n");

  pinMode(13,OUTPUT);

  for(uint8_t i = 0 ; i< 5 ; i++){
    digitalWrite(13,HIGH);
    delay(10);
    digitalWrite(13,LOW);
    delay(10);
  }

  Serial.println("starting on effect 0");
  leds_init();

}

// List of patterns to cycle through.  Each is defined as a separate function below.

SimplePatternList gPatterns = { magentaWithGlitter, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);


  // do some periodic updates
  EVERY_N_MILLISECONDS( 500 ) { Serial.print("."); }
  EVERY_N_MILLISECONDS( 20 ) { updateghue(); } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( EFFECT_DURATION ) {
    Serial.println(" next!");
    digitalWrite(13,HIGH);
    FastLED.delay(100);
    digitalWrite(13,LOW);

    nextPattern(&gCurrentPatternNumber, ARRAY_SIZE( gPatterns));
    Serial.print("actual effect:");
    Serial.println(gCurrentPatternNumber);


  } // change patterns periodically
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
