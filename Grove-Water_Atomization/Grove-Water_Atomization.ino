void setup() {
  Serial.begin(9600);
  
  pinMode(13, INPUT);
  pinMode(A5, OUTPUT);
}

void loop() {
  int buttonValue = digitalRead(13);

  if (buttonValue == HIGH) {
    Serial.println("Swich ON");
    digitalWrite(A5, HIGH);
  }
  else if (buttonValue == LOW) {
    Serial.println("Swich OFF");
    digitalWrite(A5, LOW);
  }
}
