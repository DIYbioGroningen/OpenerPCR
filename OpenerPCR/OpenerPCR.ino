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

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("        Hello");
  lcd.setCursor(0,1);  
  lcd.print("        DIYBio");
}

void loop()
{

  digitalWrite(pin_h_bridge_L1,LOW);
  digitalWrite(pin_h_bridge_L2,LOW);
  digitalWrite(pin_h_bridge_H1,LOW);
  digitalWrite(pin_h_bridge_H2,LOW);

//  lcd.setCursor(1,0);
  //lcd.print(millis());

  delay(1000);
}
