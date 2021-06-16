#include<Servo.h>  //서보모터 라이브러리 사용

Servo myservo;  
  
char ch;


void setup() 
{ 
  Serial.begin(9600); //시리얼 통신 초기화
  myservo.attach(9);  //서보모터 핀번호 9번으로 설정
  pinMode(13, INPUT);
} 


void loop() {
    int buttonValue = digitalRead(13);
  if(buttonValue == HIGH) {
    Serial.println("Swich ON");
       myservo.write(180);
      delay(5000);    
  }
  else if(buttonValue == LOW) {
    Serial.println("Swich OFF");
      myservo.write(90);
      delay(1000);
      //myservo.write(92);
  }
}
