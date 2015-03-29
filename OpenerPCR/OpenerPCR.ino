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
int relay1 = 2;
int relay2 = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(relay1, OUTPUT);     
  pinMode(relay2, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  //IMPORTANT: face#1 is per definition touching the tube block
  //(metal block with the wells for the PCR tubes)
  
  //Relay1 NO
  //Relay2 NC
  //face#1 is heating
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  delay(60000); //time during which the metal block heating
  
  //Relay1 NC
  //Relay2 NC
  //face#1 is NOT cooling NEITHER heating
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  delay(2000); //time during which the metal block temp. is not contrlled

  //Relay1 NC
  //Relay2 NO
  //face#1 is cooling
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  delay(60000); //time during which the metal block cooled
    
  //Relay1 NC
  //Relay2 NC
  //face#1 is NOT cooling NEITHER heating
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  delay(10000); //time during which the metal block temp. is not contrlled

}

