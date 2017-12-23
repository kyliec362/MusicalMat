#include <Wire.h>
#include <Keyboard.h>
int LDC = 0x2A;
int CH0MSB = 0x00;
int CH0LSB = 0x01;
int CH1MSB = 0x02;
int CH1LSB = 0x03;
int CH2MSB = 0x04;
int CH2LSB = 0x05;
int CH3MSB = 0x06;
int CH3LSB = 0x07;
long initial2 = 0;
long initial1 = 0;
long initial0 = 0;
long initial3 = 0;
long min0, min1, min2, min3;

//the up, down, left, and right input panels for the mat were mapped to keyboard keys A, B, C, D

unsigned long readChannel0()
{
  unsigned long val = 0;
  word c = 0; //a word stores a 16-bit unsigned number
  word d = 0;
  c = readValue(LDC, CH0MSB);
  d = readValue(LDC, CH0LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}


unsigned long readChannel3()
{
  unsigned long val = 0;
  word c = 0; //a word stores a 16-bit unsigned number
  word d = 0;
  c = readValue(LDC, CH3MSB);
  d = readValue(LDC, CH3LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}


unsigned long readChannel1()
{
  unsigned long val = 0;
  word c = 0; //a word stores a 16-bit unsigned number
  word d = 0;
  c = readValue(LDC, CH1MSB);
  d = readValue(LDC, CH1LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}

unsigned long readChannel2()
{
  unsigned long val = 0;
  word c = 0;
  word d = 0;
  c = readValue(LDC, CH2MSB);
  d = readValue(LDC, CH2LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}

void Calibrate()
{
  Serial.println("calibrate ch0: ");
  initial0 = readChannel0();
  min0 = getMin(0);
  Serial.println("min0=" + min0);
  delay(1000);
  Serial.println("calibrate ch1: ");
  initial1 = readChannel1();
  min1 = getMin(1);
  Serial.println("min1=" + min1);
  delay(1000);
  Serial.println("calibrate ch2: ");
  initial2 = readChannel2();
  min2 = getMin(2);
  Serial.println("min2=" + min2);
  delay(1000);
  Serial.println("calibrate ch2: ");
  initial3 = readChannel3();
  min3 = getMin(3);
  Serial.println("min3=" + min3);
  delay(1000);
}

long getMin(int ch_Num)
{
  long time0 = millis();
  long time1;
  long min = 4200000000;
  while (ch_Num == 0 && ((time1 - time0) < 6000)) //6 seconds to gather data
  {
    unsigned long data0 = readChannel0();
    if ((data0 - initial0) < min && data0 != 0)
    {
      min = (data0 - initial0);
    }
    time1 = millis();
  }
  while (ch_Num == 1 && ((time1 - time0) < 6000)) //6 seconds to gather data
  {
    unsigned long data1 = readChannel1();
    if ((data1 - initial1) < min && data1 != 0)
    {
      min = (data1 - initial1);
    }
    time1 = millis();
  }
  while (ch_Num == 2 && ((time1 - time0) < 6000)) //6 seconds to gather data
  {
    unsigned long data2 = readChannel2();
    if ((data2 - initial2) < min && data2 != 0)
    {
      min = (data2 - initial2);
    }
    time1 = millis();
  }
  while (ch_Num == 0 && ((time1 - time0) < 6000)) //6 seconds to gather data
  {
    unsigned long data3 = readChannel3();
    if ((data3 - initial3) < min && data3 != 0)
    {
      min = (data3 - initial3);
    }
    time1 = millis();
  }
  return min;

}


word readValue (int LDC, int reg)
{
  int a = 0;
  int b = 0;
  word value = 0;
  Wire.beginTransmission(LDC);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(LDC, 2);
  while (Wire.available())
  {
    a = Wire.read();
    b = Wire.read();
  }
  value = a;
  value <<= 8;
  value += b;
  return value;
}


void writeConfig(int LDC, int reg, int MSB, int LSB)
{
  Wire.beginTransmission(LDC);
  Wire.write(reg);
  Wire.write(MSB);
  Wire.write(LSB);
  Wire.endTransmission();
}

void Configuration()
{
  writeConfig(LDC, 0x14, 0x10, 0x02);//CLOCK_DIVIDERS_CH0
  writeConfig(LDC, 0x1E, 0x90, 0x00);//DRIVE_CURRENT_CH0
  writeConfig(LDC, 0x10, 0x00, 0x0A);//SETTLECOUNT_CH0
  writeConfig(LDC, 0x08, 0x04, 0xD6);//RCOUNT_CH0
  writeConfig(LDC, 0x15, 0x10, 0x02);//CLOCK_DIVIDERS_CH1
  writeConfig(LDC, 0x1F, 0x90, 0x00);//DRIVE_CURRENT_CH1
  writeConfig(LDC, 0x11, 0x00, 0x0A);//SETTLECOUNT_CH1
  writeConfig(LDC, 0x09, 0x04, 0xD6);//RCOUNT_CH1
  writeConfig(LDC, 0x16, 0x10, 0x02);//CLOCK_DIVIDERS_CH2
  writeConfig(LDC, 0x20, 0x90, 0x00);//DRIVE_CURRENT_CH2
  writeConfig(LDC, 0x12, 0x00, 0x0A);//SETTLECOUNT_CH2
  writeConfig(LDC, 0x0A, 0x04, 0xD6);//RCOUNT_CH2
  writeConfig(LDC, 0x17, 0x10, 0x02);//CLOCK_DIVIDERS_CH3
  writeConfig(LDC, 0x21, 0x90, 0x00);//DRIVE_CURRENT_CH3
  writeConfig(LDC, 0x13, 0x00, 0x0A);//SETTLECOUNT_CH3
  writeConfig(LDC, 0x0B, 0x04, 0xD6);//RCOUNT_CH3
  writeConfig(LDC, 0x19, 0x00, 0x00);//ERROR_CONFIG
  writeConfig(LDC, 0x1B, 0xC2, 0x0C);//MUX_CONFIG
}


void setup()
{
  Wire.begin();
  Keyboard.begin();
  Serial.begin(9600);
  Configuration();
  delay(3000);
  Calibrate();
}

void loop()
{
  unsigned long data0 = readChannel0();
  unsigned long data1 = readChannel1();
  unsigned long data2 = readChannel2();
  unsigned long data3 = readChannel3();
  Serial.println(data0);
  //Serial.println(data1);
 // Serial.println(data2);
  //Serial.println(data3);
  if ((data0 - initial0) < 4200000000 && (data0 - initial0) > min0)
  {
    Keyboard.write(65); //A key
  }
  
  if ((data1 - initial1) < 4200000000 && (data1 - initial1) > min1)
  {
    Keyboard.write(66); //B key
  }
  if ((data2 - initial2) < 4200000000 && (data2 - initial2) > min2)
  {
    Keyboard.write(67); //C key
  }
  if ((data3 - initial3) < 4200000000 && (data3 - initial3) > min3)
  {
    Keyboard.write(68); //D key
  }
  
  delay(500);
}








