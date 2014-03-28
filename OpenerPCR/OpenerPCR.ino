//#include <Serial.h>
#include <math.h>

const int pin_relay_L1 = 2;
const int pin_relay_L2 = 3;

#include <LiquidCrystal.h>

const int pin_lcd_rs = 8; //Arduino pin that connects to R/S pin of LCD display
const int pin_lcd_e = 9; //Arduino pin that connects to E pin of LCD display
const int pin_lcd_d4 = 10; //Arduino pin that connects to D4 pin of LCD display
const int pin_lcd_d5 = 11; //Arduino pin that connects to D5 pin of LCD display
const int pin_lcd_d6 = 12; //Arduino pin that connects to D6 pin of LCD display
const int pin_lcd_d7 = 13; //Arduino pin that connects to D7 pin of LCD display

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
  pinMode(pin_relay_L1,OUTPUT);
  pinMode(pin_relay_L2,OUTPUT);
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
  const float a = -4.9145424779468669;
  const float b = -1.0664166888283678E+03;
  const float c = 5.7516561818484919E-02;
  const float offset = -2.2215338995072266E+01;
  const double value = static_cast<double>(analogRead(pin_thermistor));
  const double temperature = (a * value / (b + value) + c * value) + offset;
  return temperature;
}

void DisplayTemperature()
{
  const double temperature = ReadTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  lcd.setCursor(9,0);
  lcd.print("T = ");
  lcd.setCursor(9,1);
  lcd.print(temperature);
  //delay(1); //Really needed?
}

void Heating(const double target_temperature)
{
  if(ReadTemperature() < target_temperature)
  {
    digitalWrite(pin_relay_L1,LOW);
    digitalWrite(pin_relay_L2,HIGH);
    DisplayTemperature();
  }
}

void Cooling(const double target_temperature)
{
  if(ReadTemperature() > target_temperature)
  {
    digitalWrite(pin_relay_L1,HIGH);
    digitalWrite(pin_relay_L2,LOW);
    DisplayTemperature();
  }
}

void HoldTemperature(const int hold_time_sec)
{
  digitalWrite(pin_relay_L1,HIGH);
  digitalWrite(pin_relay_L2,HIGH);
  DisplayTemperature();
  delay(hold_time_sec*1000);
}

void CycleTemperature(const double cold_target_temperature, const int hold_time_cold, const double hot_target_temperature, const int hold_time_hot, int cycles)
{
  for(int i =0; i!=cycles; ++i)
  {
    DisplayTemperature();
    Heating(hot_target_temperature);
    DisplayTemperature();
    HoldTemperature(hold_time_hot);
    DisplayTemperature();
    Cooling(cold_target_temperature);
    DisplayTemperature();
    HoldTemperature(hold_time_cold);  
  }
}

void loop()
{
  const int cycles = 6;
  const int hold_time_hot_sec = 3;
  const int hold_time_cold_sec = 3;
  const double temp_hot = 0.0;
  const double temp_cold = 80.0;
  const double temperature = ReadTemperature();
  
      digitalWrite(pin_relay_L1,LOW);
    digitalWrite(pin_relay_L2,HIGH);
  //Heating(temp_hot);
  //CycleTemperature(temp_hot, hold_time_hot_sec, temp_cold, hold_time_cold_sec, cycles);
  
}