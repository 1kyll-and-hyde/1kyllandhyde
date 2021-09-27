// 심박도 라이브러리
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
PulseSensorPlayground pulseSensor;

// 가속도 라이브러리
#include <AcceleroMMA7361.h>

// 블루투스 라이브러리
#include <SoftwareSerial.h>

// 심박도 아두이노 보드 넘버
const int PulseWire = A5;
const int LED13 = 13;
int Threshold = 550;

// 가속도 아두이노 보드 넘버
AcceleroMMA7361 accelero;
int x;
int y;
int z;

// 블루투스 보드 넘버
SoftwareSerial BTSerial(7, 6);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  // 심박도
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
  }

  // 가속도
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(5);
  accelero.setSensitivity(LOW);
  accelero.calibrate();
}

void loop() {
  // 블루투스
  Serial.print("999");
  Serial.print(",");
  
  BTSerial.print("999");
  BTSerial.print(",");
  
  // 심박도
  int myBPM = pulseSensor.getBeatsPerMinute();

  if (pulseSensor.sawStartOfBeat()) {
    Serial.print(myBPM);
    Serial.print(",");
    
    BTSerial.print(myBPM);
    BTSerial.print(",");
  }

  // 가속도
  x = accelero.getXAccel();
  y = accelero.getYAccel();
  z = accelero.getZAccel();

  if (BTSerial.available())
    Serial.write(BTSerial.read());
              
   if (Serial.available())
    BTSerial.write(Serial.read());

  if(x<-50){
    Serial.print("오른쪽으로!!");
    Serial.print(",");
    
    BTSerial.print("오른쪽으로!!");
    BTSerial.print(",");
  }

  if (x<=50 && x>-50) {
        Serial.print("🤗!!");
    Serial.print(",");
    
    BTSerial.print("🤗!!");
    BTSerial.print(",");
  }

  if(x>50){
    Serial.print("왼쪽으로!!");
    Serial.print(",");
    
    BTSerial.print("왼쪽으로!!");
    BTSerial.print(",");
  }
  Serial.print(x);
  Serial.print(",");

  // 블루투스
  Serial.println("888");
  
  BTSerial.print(888);

  delay(500);
}
