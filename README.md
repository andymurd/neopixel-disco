Arduino Sketch to Control a Neopixel Strip
==========================================

This simple sketch does lots of funky light show. Change the colours are function calls in the loop() method to make it your own.

There's a good write-up of setting up Neopixels to work with an Arduino at

This code also uses the excellent (FastLED library|https://github.com/FastLED/FastLED).

Check the constants at the top of the file and change NUM_LEDS and DATA_PIN to suit your hardware set up:

    #define NUM_LEDS 150
    #define DATA_PIN 6

