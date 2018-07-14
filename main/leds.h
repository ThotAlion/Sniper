#include "shared.h"
#include <FastLED.h>

// DOC https://github.com/FastLED/FastLED/wiki/Pixel-reference#chsv
// Good example https://github.com/atuline/FastLED-Demos/blob/master/fill_colours/fill_colours.ino

// FastLED.setBrightness(byte);
//


// Define Neopixel
#define NUM_LEDS 40
const uint8_t pin_data_NEO_PIXEL = A9;

// Define the array of leds
CRGB neo_leds[NUM_LEDS];

volatile int fading_percentage = 50;
volatile bool up = true ;

IntervalTimer timerNeoLeds;

// prototypes
void neo_to_black(void);
void ledsManagment(void);
void full_leds_RGB(uint8_t, uint8_t, uint8_t);
void fade_led(uint8_t, uint8_t);



//2ème année Licence de Sciences Technologie Santé

// Faire tourner un dégradé de couleurs (chenillard)
// Fading for emotion


// Specific breathing curve
// See https://www.wolframalpha.com/input/?i=(exp(sin(1000*(x%2F2000*PI)))+-+0.36787944)108.0;
void _breathe(uint8_t min_bright, uint8_t max_bright, float frequency_factor) {
  static double elapsed = 0;
  uint8_t random_led = random(0, NUM_LEDS);
  int color[3] ;
  color[0] = random(0, 100);
  color[1] = random(0, 100);
  color[2] = random(0, 100);

  neo_leds[random_led] = CRGB(color[0],color[1],color[2]);

  elapsed++ ;
  // float breath = max_bright/2 * sin(frequency_factor * elapsed) + max_bright/2 ;
  // FastLED.setBrightness(map(breath, 0, max_bright, min_bright, max_bright));

  // Specific function
  float breath = (exp(sin(frequency_factor * (elapsed/2000.0*PI)) - 0.36787944))*108.0;
  FastLED.setBrightness(map(breath, 0, 255, min_bright, max_bright));
  FastLED.show();
  neo_leds[random_led] = CRGB(100,100,100);
}

void breathe_ISR() {
  // _breathe(0, 150, 0.02);
  _breathe(0, 150, 15);
}

void chenillard() {
for(int dot = 0; dot < NUM_LEDS; dot++) {
    neo_leds[dot] = CRGB::Red;
    FastLED.show();
    neo_leds[dot] = CRGB(100, 60, 90);
    delay(10);
  }
}

void sunrise() {

  // total sunrise length, in minutes
  static const uint8_t sunriseLength = 30;

  // how often (in seconds) should the heat color increase?
  // for the default of 30 minutes, this should be about every 7 seconds
  // 7 seconds x 256 gradient steps = 1,792 seconds = ~30 minutes
  static const uint8_t interval = (sunriseLength * 60) / 256;

  // current gradient palette color index
  static uint8_t heatIndex = 0; // start out at 0

  // HeatColors_p is a gradient palette built in to FastLED
  // that fades from black to red, orange, yellow, white
  // feel free to use another palette or define your own custom one
  CRGB color = ColorFromPalette(HeatColors_p, heatIndex);

  // fill the entire strip with the current color
  fill_solid(neo_leds, NUM_LEDS, color);

  // slowly increase the heat
  EVERY_N_SECONDS(interval) {
    // stop incrementing at 255, we don't want to overflow back to 0
    if(heatIndex < 255) {
      heatIndex++;
    }
  }
}


// Strange behaviour
void fade_led(uint8_t led_id, uint8_t percentage) {
  neo_leds[led_id].fadeLightBy(percentage * 100 / 256) ;
}


void full_leds_RGB(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    neo_leds[i] = CRGB(red, green, blue);
    FastLED.show();
  }
}

void full_leds_HSV(uint8_t hue, uint8_t sat, uint8_t val) {
  for (int i = 0; i < NUM_LEDS; i++) {
    neo_leds[i] = CHSV(hue, sat, val);
    FastLED.show();
  }
}

void blynk(int val) {
  for (int i = 0; i <= NUM_LEDS; i++) {
    neo_leds[i] = CRGB(val, val * 2 / 3, val * 1 / 2);
    FastLED.show();
  }
}

void neo_to_black() {
  full_leds_RGB(0,0,0);
}

void init_neo_pixel() {
  FastLED.addLeds<NEOPIXEL, pin_data_NEO_PIXEL>(neo_leds, NUM_LEDS);

  // fill_rainbow(neo_leds, NUM_LEDS,222);
  FastLED.clear();
  FastLED.setBrightness(MAX_BRIGHTNESS);
  fill_solid(neo_leds, NUM_LEDS, CRGB::Red);

  timerNeoLeds.begin(breathe_ISR, 100000);
  timerNeoLeds.priority(250);
  // full_leds_RGB(60, 30, 40);
}
