//#include <Serial.h>
#include <math.h>


const int pin_relay_L1 = 2;
const int pin_relay_L2 = 3;

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

//function to read the temperature 
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

//function to display temperature
void DisplayTemperature();
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

void loop()
{
  const int time_hot_sec = 5;
  const int time_low_sec = 5;
  const double temp_hot = 40.0;
  const double temp_low = 25.0;
  const double temperature = ReadTemperature();
  
  //while temp is below hot target, continue heating
  while(temperature < temp_hot)
  {
    //assuming this is heating
    digitalWrite(pin_h_bridge_L1,LOW);
    digitalWrite(pin_h_bridge_L2,HIGH);
  
    //display temperature
    DisplayTemperature();
  }
  
  //hold for hot time
  digitalWrite(pin_h_bridge_L1,LOW);
  digitalWrite(pin_h_bridge_L2,LOW);
  delay(time_hot_sec*1000);
  
  //while temp is below low target, continue cooling
  while(temperature > temp_low)
  {
    //assuming this is cooling
    digitalWrite(pin_h_bridge_L1,HIGH);
    digitalWrite(pin_h_bridge_L2,LOW);
  
    //display temperature
    DisplayTemperature();
  }
  
  //hold for cold time
  digitalWrite(pin_h_bridge_L1,LOW);
  digitalWrite(pin_h_bridge_L2,LOW);
  delay(time_low_sec*1000);
}
