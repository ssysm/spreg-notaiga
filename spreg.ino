#include "config.h"
#include <BitVoicer11.h>
#include <FastLED.h>

//Instantiates the BitVoicerSerial class
//初始化BitVocice串口类
BitVoicerSerial bvSerial = BitVoicerSerial();
//初始化FastLED
CRGB leds[NUM_LEDS];

//开机setup
void setup()
{
  //设置bv串口获取方式
  bvSerial.setAnalogReference(BV_EXTERNAL);
  //使用9600波特率
  Serial.begin(9600);
  //LED的东西
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

}
//循环
void loop()
{

}

//This function runs every time serial data is available
//in the serial buffer after a loop
//bv的串口事件
void serialEvent()
{
  //Reads the serial buffer and stores the received data type
  dataType = bvSerial.getData();
 
  //Changes the value of sampleTest if the received data was
  //the start/stop sampling command
  if (dataType == BV_COMMAND)
      sampleTest = bvSerial.cmdData;
 
  //Signals BitVoicer's Speech Recognition Engine to start
  //listening to audio streams after the engineRunning status
  //was received
  if (dataType == BV_STATUS && bvSerial.engineRunning == true)
    bvSerial.startStopListening();
 
  //Checks if the data type is the same as the one in the
  //Voice Schema
  if (dataType == BV_STR)
    setLEDs();
    bvSerial.sendToBV("recive");
}

//Performs the LED changes according to the value in
//bvSerial.strData
//控制LED部分
void setLEDs()
{
  if (bvSerial.strData == "flash")
  {
    digitalWrite(LED_BUILTIN, HIGH); 
    flashON();
    delay(5500);
    digitalWrite(LED_BUILTIN, LOW);
    flashOFF();
  }else{
    digitalWrite(LED_BUILTIN, LOW); 
    lashOFF();
  }

}
//警灯效果
//TODO:让它更好看点....
void flashON(){
  //lp:多少次
   for(int lp = 0;lp<30;lp++){
      for(int i = 0; i <NUM_LEDS / 2; i++){
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    delay(30);
    for(int i = 0; i <NUM_LEDS / 2; i++){
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    delay(20);
    for(int i = 0; i <NUM_LEDS / 2; i++){
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    delay(20);
    for(int i = 0; i <NUM_LEDS / 2; i++){
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    delay(20);
    for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      leds[i] = CRGB::Blue;
      FastLED.show();
    }
    delay(20);
    for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    delay(20);
    for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      leds[i] = CRGB::Blue;
      FastLED.show();
    }
    delay(20);
    
    for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    delay(50);
    }
}
//关闭
void flashOFF(){
  for(int i = 0;i<NUM_LEDS;i++){
    leds[i] = CRGB::Black;
  }
    FastLED.show();
}
