#include <Servo.h>

#define LINEAR 9        //Linear Actuator

#define L16_MSMIN      1000
#define L16_MSMAX      2000

Servo L16;

int L16value = 10;

int button = 0;
int BMAX = 0;
int BMIN = 0;

void setup()
{ Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  L16.attach(LINEAR, L16_MSMIN, L16_MSMAX);
  L16.writeMicroseconds(L16value);
}

void loop() {
  BMAX = digitalRead(10);

  if (BMAX == HIGH) {
    while (button != 100) {
      button++;

      L16value = map(button, 0, 100, L16_MSMIN, L16_MSMAX);
      L16.writeMicroseconds(L16value);
    }
  }

  BMIN = digitalRead(11);
  if (BMIN == HIGH) {
    while (button != 0) {
      button--;

      L16value = map(button, 0, 100, L16_MSMIN, L16_MSMAX);
      L16.writeMicroseconds(L16value);
    }
  }

}
