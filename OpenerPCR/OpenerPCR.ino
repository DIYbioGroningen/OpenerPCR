//#include <Serial.h>
#include <math.h>


const int pin_h_bridge_L1 = 2;
const int pin_h_bridge_L2 = 3;
const int pin_h_bridge_H1 = 4;
const int pin_h_bridge_H2 = 5;

#include <LiquidCrystal.h>

const int pin_lcd_rs =   8; //Arduino pin that connects to R/S pin of LCD display
const int pin_lcd_e  =   9; //Arduino pin that connects to E   pin of LCD display
const int pin_lcd_d4 =  10; //Arduino pin that connects to D4  pin of LCD display
const int pin_lcd_d5 =  11; //Arduino pin that connects to D5  pin of LCD display
const int pin_lcd_d6 =  12; //Arduino pin that connects to D6  pin of LCD display
const int pin_lcd_d7 =  13; //Arduino pin that connects to D7  pin of LCD display

const int pin_thermistor = A0;

LiquidCrystal lcd(
  pin_lcd_rs,
  pin_lcd_e,
  pin_lcd_d4,
  pin_lcd_d5,
  pin_lcd_d6,
  pin_lcd_d7
);

void setup()
{
  pinMode(pin_h_bridge_L1,OUTPUT);
  pinMode(pin_h_bridge_L2,OUTPUT);
  pinMode(pin_h_bridge_H1,OUTPUT);
  pinMode(pin_h_bridge_H2,OUTPUT);
  pinMode(pin_thermistor,INPUT);

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("Hello");
  lcd.setCursor(0,1);  
  lcd.print("DIYbio");
  
  Serial.begin(4800);
}

double ReadTemperature()
{
  const float  a = -4.9145424779468669;
  const float  b = -1.0664166888283678E+03;
  const float  c =  5.7516561818484919E-02;
  const float  offset = -2.2215338995072266E+01;

  const double value = static_cast<double>(analogRead(pin_thermistor));
  const double temperature = (a * value / (b + value) + c * value) + offset;
  return temperature;
}

void loop()
{

  digitalWrite(pin_h_bridge_L1,LOW);
  digitalWrite(pin_h_bridge_L2,LOW);
  digitalWrite(pin_h_bridge_H1,LOW);
  digitalWrite(pin_h_bridge_H2,LOW);

  const double temperature = ReadTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  lcd.setCursor(9,0);
  lcd.print("T = ");
  lcd.setCursor(9,1);
  lcd.print(temperature);
  
  delay(1000);
}
