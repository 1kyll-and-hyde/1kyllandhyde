#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.
#include <AcceleroMMA7361.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>            //라이브러리 추가(기본라이브러리)
#include <TinyGPS.h>                //라이브러리 추가 필요
#include <SoftwareSerial.h>     
// Arduino에서 GPS와 통신하기 위해 사용할 핀을 정의합니다. 
// 이 경우 GPS 모듈의 TX 핀이 Arduino의 RXPIN(핀 3)에 연결됩니다.
#define RXPIN 1
#define TXPIN 2
//이 값을 GPS의 보드 속도와 동일하게 설정합니다.
#define GPSBAUD 9600
// TinyGPS 개체의 인스턴스 생성
TinyGPS gps;
// 위에서 정의한 핀으로 NewSoftSerial 라이브러리 초기화

SoftwareSerial uart_gps(RXPIN, TXPIN);
SoftwareSerial BTSerial(2, 3); 
AcceleroMMA7361 accelero;
int x;
int y;
int z;

int distance;
int triggerPin = 4;
int echoPin = 3;

// 블루투스
SoftwareSerial HC05 (6,7);

//  Variables
const int PulseWire = 5;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.

PulseSensorPlayground pulseSensor; 
 
void getgps(TinyGPS &gps);

void setup()
{
  Serial.begin(9600);
 
  // 가속도
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(5); //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW); //sets the sensitivity to +/-6G
  accelero.calibrate();

  // GPS
  uart_gps.begin(GPSBAUD);

  // 초음파, 심박도
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }

  // 블루투스
  Serial.begin(9600);
  HC05.begin(9600);
  //HC05.begin(38400);
}
 
void loop()
{
  //GPS
  while(uart_gps.available())     // GPS모듈에서 신호가 수신 될 경우
  {
      int c = uart_gps.read();    // 변수에 데이터를 저장
      if(gps.encode(c))              // 새로운 문장이 있다면
      {
        getgps(gps);                 // 데이터를 수집
      }   
  }

  // 초음파, 심박도
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  distance = pulseIn(echoPin, HIGH) / 58;
  
  delay(1000);
  if (distance < 50)
  {
    analogWrite(5, 200);                                        // 진동모터를 200/255의 파워로 작동시킵니다.

    //delay(3000);                                                    // 3초간 대기

  }
  else
  {
    analogWrite(5, 0);                                           // 진동모터를 0의 파워로 작동시킵니다. (OFF)

    //delay(3000);                                                   // 3초간 대기

  }

  delay(100);




  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  // "myBPM" hold this BPM value now.

  delay(20);                    // considered best practice in a simple sketc

  // 블루투스
 // if(Serial.available()) HC05.write(Serial.read());
 // if(HC05.available()) Serial.write(HC05.read());
  if (HC05.available())
    Serial.write(HC05.read());
  if(Serial.available())
    HC05.write(HC05.read());

   // 가속도
  x = accelero.getXAccel();
  y = accelero.getYAccel();
  z = accelero.getZAccel();
  //Serial.print("\nx: ");
  //Serial.print(x);
  //Serial.print(" \ty: ");
  //Serial.print(y);
  //Serial.print(" \tz: ");
  //Serial.print(z);
  //Serial.print("\tG*10^-2");
  
  delay(500); //make it readable

  if (BTSerial.available())
    Serial.write(BTSerial.read());
              
   if (Serial.available())
    BTSerial.write(Serial.read());

  if(x<0){
    Serial.print("999");
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    //Serial.print(myBPM);                        // Print the value inside of myBPM.
   // Serial.print(",");
    Serial.println("888");

    HC05.print("999");
    HC05.print(",");
    HC05.print(distance);
    HC05.print(",");
    HC05.print(distance);
    HC05.print(",");
    //HC05.print(myBPM);
    //HC05.print(",");
    HC05.println("888");
  }
  if(x>0){
    Serial.print("999");
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    //Serial.print(myBPM);                        // Print the value inside of myBPM.
   // Serial.print(",");
    Serial.println("888");

    HC05.print("999");
    HC05.print(",");
    HC05.print(distance);
    HC05.print(",");
    HC05.print(distance);
    HC05.print(",");
    //HC05.print(myBPM);
    //HC05.print(",");
    HC05.println("888");
  }

  delay(500);
}


 
 void getgps(TinyGPS &gps)
{
  // 변수정의
  float latitude, longitude;
  // 기능호출
  gps.f_get_position(&latitude, &longitude);
 //  위도(latitude)경도(longitude )출력 가능상태
  Serial.print("Lat/Long: "); 
  Serial.print(latitude,5); 
  Serial.print(", "); 
  Serial.println(longitude,5);
  
  // 날짜랑 시간 데이터도 동일한 포멧입니다.
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/"); 
  Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(hour, DEC); Serial.print(":"); 
  Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC); 
  Serial.print("."); Serial.println(hundredths, DEC);
  
  // 여기서 고도와 코스 값을 직접 인쇄할 수 있습니다
  Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());  
  Serial.print("Course (degrees): "); Serial.println(gps.f_course()); 
  Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
  Serial.println();
  
  // 여기서 문장에 대한 통계를 인쇄할 수 있습니다.
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  //Serial.print("Failed Checksums: ");Serial.print(failed_checksum);
  //Serial.println(); Serial.println();
  delay(1000);
}
