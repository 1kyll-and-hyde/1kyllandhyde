#include <Adafruit_NeoPixel.h>   // 네오픽셀 라이브러리를 불러옵니다.

#define PIN 6                      // 디지털핀 어디에 연결했는지 입력
#define LEDNUM 20                  // 연결된 네오픽셀의 숫자입력
#define BRIGHTNESS 50               // 네오픽셀의 밝기를 설정합니다. (0~255)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
     Serial.begin(9600);
  strip.setBrightness(BRIGHTNESS);
}

void loop() {                              // 이 안에 입력한 내용들이 반복 실행됩니다
   int light = analogRead(A0);
   Serial.print( "Light=");
  Serial.println(light);


  strip.begin();                           // 네오픽셀 제어시작
  strip.show();                            // 네오픽셀 초기화
  if(light<300){
    for(int i=0; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }
  }
  if(light>=300 && light<=400){
    for(int i=0; i<2; i++){
    strip.setPixelColor(i, 211, 154, 80, 0);  
   }
    for(int i=2; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }}
     if(light>=401 && light<=500){
    for(int i=0; i<4; i++){
    strip.setPixelColor(i, 0, 0, 100, 0);  
   }
    for(int i=4; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }}
     if(light>=501 && light<=600){
   for(int i=0; i<6; i++){
    strip.setPixelColor(i, 100, 220, 170, 0);  
   }
    for(int i=6; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }}
     if(light>=601 && light<=700){
    for(int i=0; i<8; i++){
    strip.setPixelColor(i, 168, 186, 200, 0);  
   }
    for(int i=8; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }}
     if(light>=701 && light<=800){
    for(int i=0; i<10; i++){
    strip.setPixelColor(i, 180, 255, 190, 0);  
   }
    for(int i=10; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }}
     if(light>=801 && light<=900){
 for(int i=0; i<12; i++){
    strip.setPixelColor(i, 200, 150, 175, 0);  
   }
    for(int i=12; i<14; i++){
    strip.setPixelColor(i, 0,0,0,0);
    }}
     if(light>=901 && light<=1023){
  for(int i=0; i<14; i++){
    strip.setPixelColor(i, 255, 255, 255, 255);  
   }  
  }
     }
