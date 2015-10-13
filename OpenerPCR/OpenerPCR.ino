///////////////////////////////////////////////////////////////////
//DIYBio-Groningen. Copyleft.
//version 1.0: the circuit schematic of the high power side is redrawn,
//so that in case the Arduino fails/goes off the Peltier element
//does NOT heat NEITHER cool.
///////////////////////////////////////////////////////////////////
//CIRCUIT SCHEMATIC
//JUMPER between JC-VCC and VCC on the relay board is removed:
//the relays are physically isolated from the control side
//of the circuit.
//The relay board is supplied with external +5VDC connected
//to JD-Vcc and external Ground to board GND.
//The Arduino controls two relays through IN1 and IN2 (signal pin)
//and one common VCC pin (Adruino +5VDC).
//
//The relay board connections on the high power side are illustrated below:
//NO: normally open
//NC: normally closed
//TEC: thermoelectric element
//
//         Relay1                  Relay2
//           *                       *
//          /|\                     /|\
//         / | \                   / | \
//      NO/  |  \NC             NO/  |  \NC
//       |   |   |     _____     |   |   |
//       |   !___|_____|TEC|_____|___!   |
//       !_______|_______________!_______|_______ +12VDC
//               |                       |
//               !_______________________!_______ GND
//
//
// when Arduino pin is:
// LOW == relay Normally Open (NO) == LEDs on
// HIGH == relay Normally Close (NC) == LEDs off
///////////////////////////////////////////////////////////////////

// Pin 2 and 3 control the relay board: relay1 and relay2 respectively.
const int relay_pin1 = 2;
const int relay_pin2 = 3;
const int thermistor_pin = A0;

const double denaturation_temperature_celcius = 95.0;
const double annealing_temperature_celcius = 60.0;
const double extension_temperature_celcius = 72.0;

const double denaturation_time_secs = 30;
const double annealing_time_secs = 20;
const double extension_time_secs = 10;

void setup() {                
  pinMode(relay_pin1, OUTPUT);     
  pinMode(relay_pin2, OUTPUT);     
  pinMode(thermistor_pin,INPUT);
}


void cool() {
  //Relay1 NC
  //Relay2 NO
  //face#1 is cooling
  digitalWrite(relay_pin1, HIGH);
  digitalWrite(relay_pin2, LOW);
}

void heat() {
  //Relay1 NO
  //Relay2 NC
  //face#1 is heating
  digitalWrite(relay_pin1, LOW);
  digitalWrite(relay_pin2, HIGH);
}

double read_temperature() {
  const int value = analogRead(thermistor_pin);
  //Transform the range of value from [0,1023] to [0,100] degrees Celsius
  const double t_stub 
    = static_cast<double>(
     map(value,0,1023,0,100)
   );
  return t_stub;
}

void go_to_temperature(const double target_temperature_celsius)
{
  const double current_temperature = read_temperature();
  const double acceptable_temperature_difference_celsius = 1.0;
  if (abs(target_temperature_celsius - current_temperature) 
    < acceptable_temperature_difference_celsius)
  {
    return;
  }
  //Need to heat or cool to the target temperature
  if (target_temperature_celsius > current_temperature)
  {
    cool();
  }
  else 
  {
    heat(); 
  }
}

void loop() {
  go_to_temperature(denaturation_temperature_celcius);
  delay(denaturation_time_secs * 1000); //delay needs msecs
  
  go_to_temperature(annealing_temperature_celcius);
  delay(annealing_time_secs * 1000); //delay needs msecs
  
  go_to_temperature(extension_temperature_celcius);
  delay(extension_time_secs * 1000); //delay needs msecs
}

