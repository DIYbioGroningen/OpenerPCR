#include <Arduino.h>

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
  //lcd.setCursor(0,0);
  //lcd.print("Hello");
  //lcd.setCursor(0,1);
  //lcd.print("DIYbio");

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

void DisplayPhase(const char * const a, const char * const b)
{
  lcd.setCursor(0,0);
  lcd.print("        ");
  lcd.setCursor(0,0);
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print("        ");
  lcd.setCursor(0,1);
  lcd.print(b);
}

void DisplayTemperature()
{
  const double temperature = ReadTemperature();
  //Serial.print("Temperature: ");
  //Serial.println(temperature);
  lcd.setCursor(9,0);
  lcd.print("T = ");
  lcd.setCursor(9,1);
  lcd.print(temperature);
}

void Heat()
{
  digitalWrite(pin_relay_L1,HIGH);
  digitalWrite(pin_relay_L2,HIGH);
}

void Cool()
{
  digitalWrite(pin_relay_L1,LOW);
  digitalWrite(pin_relay_L2,LOW);
}

void Rest()
{
  digitalWrite(pin_relay_L1,LOW);
  digitalWrite(pin_relay_L2,HIGH);
}

/*
void CycleTemperature(const double cold_target_temperature, const int hold_time_cold, const double hot_target_temperature, const int hold_time_hot, int cycles)
{
  for(int i =0; i!=cycles; ++i)
  {
    DisplayTemperature();
    Heating();
    DisplayTemperature();
    HoldTemperature();
    DisplayTemperature();
    Cooling();
    DisplayTemperature();
    HoldTemperature();
  }
}
*/

void loop()
{
  const int n_cycles = 6;
  const int hold_time_denaturation_msec = 3000;
  const int hold_time_elongation_msec = 3000;
  const int hold_time_annealing_msec = 3000;
  const double temperature_annealing_celsius = 25.0; //68.0;
  const double temperature_elongation_celsius = 30.0; //72.0;
  const double temperature_denaturation_celsius = 35.0; //95.0;

  const double temperature = ReadTemperature();

  digitalWrite(pin_relay_L1,LOW);
  digitalWrite(pin_relay_L2,HIGH);
  //Heating(temp_hot);
  //CycleTemperature(temp_hot, hold_time_hot_sec, temp_cold, hold_time_cold_sec, cycles);


  //Perform a cycle
  for (int cycle = 0; cycle!= n_cycles; ++cycle)
  {
    //Stage 1: denaturation
    {
      //Heat to denaturation
      while (ReadTemperature() < temperature_denaturation_celsius)
      {
        Heat();
        DisplayTemperature();
        DisplayPhase("Heat to","Den.");
        delay(1);
      }
      //Stay at denaturation
      const int start_time_msec = millis();
      while (1)
      {
        const int current_time_msec = millis();
        const int duration_msec = current_time_msec - start_time_msec;
        Serial.println(duration_msec);
        if (duration_msec > hold_time_denaturation_msec) break;

        if(ReadTemperature() < temperature_denaturation_celsius)
        {
          Heat();
        }
        else if(ReadTemperature() > temperature_denaturation_celsius)
        {
          Rest();
        }
        DisplayTemperature();
        DisplayPhase("Stay at","Den.");
        delay(10);
      }

    }
    //Stage 2: annealing
    {
      //Heat to annealing
      while (ReadTemperature() > temperature_annealing_celsius)
      {
        Cool();
        DisplayTemperature();
        DisplayPhase("Cool to","Ann.");
        delay(1);
      }
      //Stay at annealing
      const int start_time_msec = millis();
      while (1)
      {
        const int current_time_msec = millis();
        const int duration_msec = current_time_msec - start_time_msec;
        Serial.println(duration_msec);
        if(duration_msec > hold_time_annealing_msec) break;

        DisplayPhase("Stay at","Ann.");
        if(ReadTemperature() < temperature_annealing_celsius)
        {
          Heat();
        }
        else if(ReadTemperature() > temperature_annealing_celsius)
        {
          Rest();
        }
        DisplayTemperature();
        delay(10);
      }
    }

    //Stage 3: elongation
    {
      //Heat to elongation
      while (ReadTemperature() < temperature_elongation_celsius)
      {
        Heat();
        DisplayTemperature();
        DisplayPhase("Heat to","Elo.");
        delay(1);
      }
      //Stay at elongation
      const int start_time_msec = millis();
      while (1)
      {
        const int current_time_msec = millis();
        const int duration_msec = current_time_msec - start_time_msec;
        Serial.println(duration_msec);
        if(duration_msec > hold_time_elongation_msec) break;
        DisplayPhase("Stay at","Elo.");
        if(ReadTemperature() < temperature_elongation_celsius)
        {
          Heat();
        }
        else if(ReadTemperature() > temperature_elongation_celsius)
        {
          Rest();
        }
        DisplayTemperature();
        delay(1);
      }
    }
  }
}
