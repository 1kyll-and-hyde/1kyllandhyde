/*안녕*/

/*
 * made by codingbird
 * Copyright 2020. codingbird All rights reserved 
 */
/*
#include<Wire.h>

const int MPU_ADDR = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;
double angleFiX, angleFiY, angleFiZ;

const double RADIAN_TO_DEGREE = 180 / 3.14159;
const double DEGREE_PER_SECOND = 32767 / 250;
const double ALPHA = 1 / (1 + 0.04);

unsigned long now = 0;
unsigned long past = 0;
double dt = 0;

double baseAcX, baseAcY, baseAcZ;
double baseGyX, baseGyY, baseGyZ;

void setup() {
  initSensor();
  Serial.begin(115200);
  calibrateSensor();
  past = millis();
}

void loop() {
  getData();
  getDT();

  angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2)));
  angleAcY *= RADIAN_TO_DEGREE;

  angleGyY += ((GyY - baseGyY) / DEGREE_PER_SECOND) * dt;

  double angleTmp = angleFiY + angleGyY * dt;
  angleFiY = ALPHA * angleTmp + (1.0 - ALPHA) * angleAcY;
  Serial.print(angleFiY);
  Serial.println("º");
}

void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

void getDT() {
  now = millis();
  dt = (now - past) / 1000.0;
  past = now;
}

void calibrateSensor() {
  double sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  double sumGyX = 0, sumGyY = 0, sumGyZ = 0;
  getData();
  for (int i = 0; i < 10 ; i++) {
    getData();
    sumAcX += AcX; sumAcY += AcY; sumAcZ += AcZ;
    sumGyX += GyX; sumGyY += GyY; sumGyZ += GyZ;
    delay(100);
  }
  baseAcX = sumAcX / 10;
  baseAcY = sumAcY / 10;
  baseAcZ = sumAcZ / 10;
  baseGyX = sumGyX / 10;
  baseGyY = sumGyY / 10;
  baseGyZ = sumGyZ / 10;
}
*/


#include <AcceleroMMA7361.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); 
AcceleroMMA7361 accelero;
int x;
int y;
int z;
 
void setup()
{
  Serial.begin(9600);
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(5); //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW); //sets the sensitivity to +/-6G
  accelero.calibrate();
}
 
void loop()
{
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
    Serial.println("오른쪽으로!!");
    BTSerial.println("오른쪽으로!!");
  }
  if(x>0){
    Serial.println("왼쪽으로!!");
    BTSerial.println("왼쪽으로!!");
  }
  }
