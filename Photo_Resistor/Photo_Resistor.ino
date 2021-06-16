#include <Adafruit_NeoPixel.h>

#define PIN 7
#define LEDNUM 20
#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  int light = analogRead(A0);
  Serial.print( "Light=");
  Serial.println(light);


  strip.begin();
  strip.show();
  if (light < 300) {
    for (int i = 0; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 300 && light <= 400) {
    for (int i = 0; i < 2; i++) {
      strip.setPixelColor(i, 211, 154, 80, 0);
    }
    for (int i = 2; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 401 && light <= 500) {
    for (int i = 0; i < 4; i++) {
      strip.setPixelColor(i, 0, 0, 100, 0);
    }
    for (int i = 4; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 501 && light <= 600) {
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i, 100, 220, 170, 0);
    }
    for (int i = 6; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 601 && light <= 700) {
    for (int i = 0; i < 8; i++) {
      strip.setPixelColor(i, 168, 186, 200, 0);
    }
    for (int i = 8; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 701 && light <= 800) {
    for (int i = 0; i < 10; i++) {
      strip.setPixelColor(i, 180, 255, 190, 0);
    }
    for (int i = 10; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 801 && light <= 900) {
    for (int i = 0; i < 12; i++) {
      strip.setPixelColor(i, 200, 150, 175, 0);
    }
    for (int i = 12; i < 14; i++) {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }

  if (light >= 901 && light <= 1023) {
    for (int i = 0; i < 14; i++) {
      strip.setPixelColor(i, 255, 255, 255, 255);
    }
  }
}
