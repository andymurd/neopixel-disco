/**
 * @file Arduino recipe for neopixel strip
 *
 * @copyright Amazed Pty Ltd 2017
 * @author Andy Murdoch
 */

#include <FastLED.h>

/// The number of individual LEDs in the NeoPixel strip
#define NUM_LEDS 150

/// The GPIO pin that controls the LEDs
#define DATA_PIN 6

/// Memory for the LED state
static CRGB leds[NUM_LEDS];

/// The length of the rainbow colour array
#define RAINBOW_LEN 7

/// An array of colours in the rainbow
static CRGB rainbow[RAINBOW_LEN] = {
    CRGB::Red,
    CRGB::Orange,
    CRGB::Yellow,
    CRGB::Green,
    CRGB::Blue,
    CRGB::Indigo,
    CRGB::Violet
};

/**
 * Called once to initialise the system upon power up and installation
 */
void setup() {
    // Initialise
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

/**
 * Move a dot from the bottom (LED at position 0) to the top of the neopixel strip.
 * 
 * @param top {Integer} The total number of LEDs
 * @param fg_colour {Object} The colour of the "moving" LED
 * @param bg_colour {Object} The colur that will be used to erase the "moving" LED
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void dotBottomToTop(int top, CRGB fg_colour, CRGB bg_colour, int delay_ms) {
    for(int dot = 0; dot < top; dot++) { 
        leds[dot] = fg_colour;
        FastLED.show();
        leds[dot] = bg_colour;
        delay(delay_ms);
    }
}

/**
 * Move a dot from the top to the bottom (LED at position 0) of the neopixel strip.
 * 
 * @param top {Integer} The total number of LEDs
 * @param fg_colour {Object} The colour of the "moving" LED
 * @param bg_colour {Object} The colur that will be used to erase the "moving" LED
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void dotTopToBottom(int top, CRGB fg_colour, CRGB bg_colour, int delay_ms) {
    for(int dot = top; dot >= 0; dot--) {
        leds[dot] = fg_colour;
        FastLED.show();
        leds[dot] = bg_colour;
        delay(delay_ms);
    }
}

/**
 * Move two dots from the centre of the neopixel strip to the top and bottom (LED at position 0).
 * 
 * @param top {Integer} The total number of LEDs
 * @param fg_colour {Object} The colour of the "moving" LED
 * @param bg_colour {Object} The colur that will be used to erase the "moving" LED
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void dotMiddleOut(int top, CRGB fg_colour, CRGB bg_colour, int delay_ms) {
    int half = (int)(top * 0.5);
    for(int dot = 0; dot < half; dot++) { 
        leds[half + dot] = fg_colour;
        leds[half - dot] = fg_colour;
        FastLED.show();
        leds[half + dot] = bg_colour;
        leds[half - dot] = bg_colour;
        delay(delay_ms);
    }
}

/**
 * Move two dots from the top and bottom (LED at position 0) to the centre of the neopixel strip.
 * 
 * @param top {Integer} The total number of LEDs
 * @param fg_colour {Object} The colour of the "moving" LED
 * @param bg_colour {Object} The colur that will be used to erase the "moving" LED
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void dotOutsideIn(int top, CRGB fg_colour, CRGB bg_colour, int delay_ms) {
    int half = (int)(top * 0.5);
    for(int dot = half; dot >= 0; dot--) { 
        leds[half + dot] = fg_colour;
        leds[half - dot] = fg_colour;
        FastLED.show();
        leds[half + dot] = bg_colour;
        leds[half - dot] = bg_colour;
        delay(delay_ms);
    }
}

/**
 * Colour all LEDs from the bottom (LED at position 0) to the top of the neopixel strip.
 * 
 * @param top {Integer} The total number of LEDs
 * @param colour {Object} The colour of the LEDs
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void fillBottomToTop(int top, CRGB bar_colour, int delay_ms) {
    dotBottomToTop(top, bar_colour, bar_colour, delay_ms);
}

/**
 * Colour all LEDs from the top to the bottom (LED at position 0) of the neopixel strip.
 * 
 * @param top {Integer} The total number of LEDs
 * @param colour {Object} The colour of the LEDs
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void fillTopToBottom(int top, CRGB bar_colour, int delay_ms) {
    dotTopToBottom(top, bar_colour, bar_colour, delay_ms);
}

/**
 * As with a graphic equaliser, colour LEDs from the bottom (LED at position 0) to the
 * top of the neopixel strip, leaving a single LED coloured and then dropping the bar back
 * down to the bottom.
 * 
 * @param top {Integer} The total number of LEDs
 * @param top_colour {Object} The colour of the LED at the peak of the bar
 * @param bar_colour {Object} The colour of the LEDs in the bar
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void equaliser(int top, CRGB top_colour, CRGB bar_colour, int delay_ms) {
    fillBottomToTop(top, bar_colour, delay_ms);
    leds[top-1] = top_colour;
    fillTopToBottom(top-2, CRGB::Black, delay_ms);
}

/**
 * Colour LEDs, moving from the centre of the neopixel strip outwards to the top and bottom (LED at position 0).
 * 
 * @param top {Integer} The total number of LEDs
 * @param bar_colour {Object} The colour of the LEDs
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void fillMiddleOut(int top, CRGB bar_colour, int delay_ms) {
    dotMiddleOut(top, bar_colour, bar_colour, delay_ms);
}

/**
 * Colour LEDs, moving from the ends of the neopixel strip inwards to the centre.
 * 
 * @param top {Integer} The total number of LEDs
 * @param bar_colour {Object} The colour of the LEDs
 * @param delay_ms {Integer} The number of milliseconds to wait in between each frame
 */
static void fillOutsideIn(int top, CRGB bar_colour, int delay_ms) {
    dotOutsideIn(top, bar_colour, bar_colour, delay_ms);
}

/**
 * The steps in the animation. Epileptics beware, there are lots of flashign lights!
 */
void loop() {
    dotOutsideIn(NUM_LEDS, CRGB::Magenta, CRGB::Black, 50);
    dotOutsideIn(NUM_LEDS, CRGB::Magenta, CRGB::Black, 25);
    dotOutsideIn(NUM_LEDS, CRGB::Magenta, CRGB::Black, 10);
    dotOutsideIn(NUM_LEDS, CRGB::Magenta, CRGB::Black, 5);
    dotOutsideIn(NUM_LEDS, CRGB::Magenta, CRGB::Black, 5);
    dotOutsideIn(NUM_LEDS, CRGB::Magenta, CRGB::Black, 5);

    fillMiddleOut(NUM_LEDS, CRGB::Yellow, 2);
    delay(1000);
    
    dotTopToBottom(NUM_LEDS, CRGB::Black, CRGB::Black, 30);

    equaliser((int)(NUM_LEDS * 0.25),    CRGB::Red, CRGB::White, 10);
    equaliser((int)(NUM_LEDS * 0.25),    CRGB::Red, CRGB::White, 10);
    equaliser((int)(NUM_LEDS * 0.33333), CRGB::Red, CRGB::White, 10);
    equaliser((int)(NUM_LEDS * 0.5),     CRGB::Red, CRGB::White, 10);
    equaliser((int)(NUM_LEDS * 0.75),    CRGB::Red, CRGB::White, 10);
    equaliser(NUM_LEDS,                  CRGB::Red, CRGB::White, 10);

    fillTopToBottom(NUM_LEDS, CRGB::Red, 10);

    fillMiddleOut(NUM_LEDS, CRGB::Black, 30);

    int third = (int)(NUM_LEDS * 0.33333);
    for(int dot = 0; dot < third; dot++) { 
        leds[dot * 3] = CRGB::Cyan;
        leds[dot * 3 + 1] = CRGB::Cyan;
        leds[dot * 3 + 2] = CRGB::Black;
        FastLED.show();
        delay(60);
    }

    for(int count = 0; count < 100; count++) {
        for(int dot = 0; dot < third; dot++) {
            leds[dot * 3 + (count % 3)] = CRGB::Cyan;
            leds[dot * 3 + (count % 3) - 1] = CRGB::Cyan;
            leds[dot * 3 + (count % 3) - 1] = CRGB::Black;
        }
        FastLED.show();
        delay(100);
    }

    fillOutsideIn(NUM_LEDS, CRGB::Green, 30);
    dotOutsideIn(NUM_LEDS, CRGB::Green, CRGB::Black, 20);
    
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    

          
    int bands = (int)NUM_LEDS / RAINBOW_LEN;
    for(int dot = 0; dot < NUM_LEDS; dot++) {
        leds[dot] = rainbow[dot / bands];          
        FastLED.show();
        delay(30);
    }
}
