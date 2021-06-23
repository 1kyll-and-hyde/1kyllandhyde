#include<Servo.h>
Servo myservo;

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(13, INPUT);
  pinMode(A5, OUTPUT);
}


void loop() {
  int Upbutton = digitalRead(12);

  if (Upbutton == HIGH) {
    Serial.println("UP Switch ON");
    myservo.write(180);
    delay(1000);
  }
  else if (Upbutton == LOW) {
    Serial.println("UP Switch OFF");
    myservo.write(90);
    delay(1000);
  }
  
  int Downbutton = digitalRead(11);
  
 if (Downbutton == HIGH) {
    Serial.println("DOWN Switch ON");
    myservo.write(0);
    delay(1000);
  }
  else if (Downbutton == LOW) {
    Serial.println("DOWN Switch OFF");
    myservo.write(90);
    delay(1000);
  }

    int WaterButton = digitalRead(13);

  if (WaterButton == HIGH) {
    Serial.println("Water Switch ON");
    digitalWrite(A5, HIGH);
    digitalWrite(A0, HIGH);
  }
  else if (WaterButton == LOW) {
    Serial.println("Water Switch OFF");
    digitalWrite(A5, LOW);
    digitalWrite(A0, LOW);
  }
}
