/*
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-12-18 14:14:35
 * @LastEditors: Changhua
 * @Description: Smart Robot Car V4.0
 * @FilePath: 
 
 1. {N:101, D1:1} will switch the mode to line tracking.  N:101 says to switch the mode, and D1:1 says to select line tracking
 Line2092 assigns Custom_mode
 2. We have created a custom function with the line tracking code
 3. If we 
      create a mode option for that custom function (DONE)
      create a branch statement for the new mode
      create an app that calls the new mode in N101
 Then we should be able to run line tracking from the custom app, then we can modify that app 
 */

 
#include <avr/wdt.h>
#include <hardwareSerial.h>
#include <stdio.h>
#include <string.h>
#include "ApplicationFunctionSet_xxx0.h"
#include "FastLED.h"
#define PIN_RBGLED 4
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];

int joe(void);
//void Event(void);
int Event(void);

void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init();
  wdt_enable(WDTO_2S);  
  Serial.begin(9600);  
  FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
}
//Look into KeyCommand, SensorDataUpdate, IRrecv, and SerialPortDataAnalysis
void loop()
{
  //put your main code here, to run repeatedly :
  wdt_reset();
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
  Application_FunctionSet.ApplicationFunctionSet_KeyCommand();
  Application_FunctionSet.ApplicationFunctionSet_RGB();
  Application_FunctionSet.ApplicationFunctionSet_Follow();
  Application_FunctionSet.ApplicationFunctionSet_Obstacle();
  Application_FunctionSet.ApplicationFunctionSet_Tracking();
  Application_FunctionSet.ApplicationFunctionSet_Rocker();
  Application_FunctionSet.ApplicationFunctionSet_Standby();
  Application_FunctionSet.ApplicationFunctionSet_IRrecv();
  Application_FunctionSet.ApplicationFunctionSet_AutoPilot();
  //Application_FunctionSet.ApplicationFunctionSet_CustomApp();
  Application_FunctionSet.ApplicationFunctionSet_SerialPortDataAnalysis();
  //int customCommand = Event();
  //if(customCommand == 1){
    //Application_FunctionSet.ApplicationFunctionSet_CustomApp();
    //Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
    //}

  Application_FunctionSet.CMD_ServoControl_xxx0();
  Application_FunctionSet.CMD_MotorControl_xxx0();
  Application_FunctionSet.CMD_CarControlTimeLimit_xxx0();
  Application_FunctionSet.CMD_CarControlNoTimeLimit_xxx0();
  Application_FunctionSet.CMD_MotorControlSpeed_xxx0();
  Application_FunctionSet.CMD_LightingControlTimeLimit_xxx0();
  Application_FunctionSet.CMD_LightingControlNoTimeLimit_xxx0();
  Application_FunctionSet.CMD_ClearAllFunctions_xxx0();
}

 //void Event()
int Event()
{ 
  int answer = 0;
  //int trial = SecondDataAnalysis();
  //int status = CustomSerialPortDataAnalysis();
  //Serial.println("status = " + status);
  int status = joe();  
  if (status)
  {
    switch (status)
    {
      case 1: return 1;break;//Application_FunctionSet.ApplicationFunctionSet_Tracking();break;//Application_FunctionSet.ApplicationFunctionSet_AutoPilot();break;
      case 2: FastLED.showColor(Color(255, 0, 255));break;
      case 3: FastLED.showColor(Color(0, 255, 255)); break;
      case 4: FastLED.showColor(Color(0, 255, 0)); break;
      default: return 0;break;
    }
  }
  return answer;
}

int joe(void)
{
  String SerialPortData = "";
  uint8_t c = "";
  if (Serial.available() > 0)
  {
    while (c != '}' && Serial.available() > 0)
    {
      c = Serial.read();
      SerialPortData += (char)c;
    }
    if (c == '}')
    {
      delay(50);
      return atoi((char*)(SerialPortData.substring(1, SerialPortData.length() - 1).c_str()));
    }
  }
  else
  {
    return 0;
  }
}

uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}

/*
int SerialPortDataAnalysis(void)
{
  String SerialPortData = "";
  if(Serial.available() > 0){
    SerialPortData = Serial.readString();
  }
  Serial.println(SerialPortData);
  return 0;
  /*
  uint8_t c = "";
  if (Serial.available() > 0)
  {
    while (c != '}' && Serial.available() > 0)
    {
      c = Serial.read();
      SerialPortData += (char)c;
    }
    if (c == '}')
    {
      delay(50);
      //Serial.println(SerialPortData);
      return atoi((char*)(SerialPortData.substring(1, SerialPortData.length() - 1).c_str()));
    }
  }
  else
  {
    return 0;
  }
  */
//}
/*
int CustomSerialPortDataAnalysis(void)
{
  String SerialPortData = "";
  String test = "";
  
  uint8_t c = "";
  if (Serial.available() > 0)
  {
    //Test did not print; SerialPortData is returning Deserialize JSON error; ?
    //test = Serial.read();
    //Serial.println(test);
    while (c != '}' && Serial.available() > 0)
    {
      c = Serial.read();
      //Serial.println(c);
      SerialPortData += (char)c;
    }
    if (c == '}')
    {
      //Serial.println(SerialPortData);
      delay(50);
      
      Serial.println(test);
      return atoi((char*)(SerialPortData.substring(1, SerialPortData.length() - 1).c_str()));
    }
  }
  else
  {
    return 0;
  }
}
*/
