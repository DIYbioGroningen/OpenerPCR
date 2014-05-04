
The [[OpenPCR]] Electronics group

===== Bill Of Materials =====

Consist of components and autonomous parts

==== Components ====

Consist of connectors and active/passive components

=== Connectors ===

We did not use any connectors. Instead we soldered everything directly to the PCB

| # | Brand official | Serial # | Description | Notes |
| 1 | FCI | 68001-416HLF | Headers, 0.1" pitch, 16 pins | Solder this instead |
| 2 | FCI | 68002-408HLF | Headers, 0.1" pitch, 8 pins | Solder this instead |
| 2 | FCI | 68002-406HLF | Headers, 0.1" pitch, 6 pins | Solder this instead |
| 1 | Molex | 39-29-9242 | ATX connector, 24 pin | Solder this instead |
| 1 | Molex | 22-23-2031 | 3 pin connector for fan | Solder this instead |
| 1 | Molex | 22-23-2021 | 2 pin connector for thermistor | Solder this instead |
| 2 | Molex | 16020101 | Terminal connector, 34 AWG | Solder this instead |
| 1 | Molex | 50-57-9502 | Terminal housing, 2 pin | Solder this instead |

=== Active/passive components ===

{| class="wikitable" 
|- # 
| Brand official 
| Serial # 
| Description 
| SMD 
| What we really bought
|- 
|2 
|Yageo 
| SQP10AJB-4R7 
| Resistor, 4.7 Ohm, 10 W 
| No 
| http://www.conrad.nl/ce/nl/product/411850/Draadweerstand-11W-47Ohm-Axiaal-Hoge-belasting-47-11-W-10-
|- 
| 1 
| Panasonic 
| ERG-2SJ160 
| Resistor, 16 Ohm 
| No 
| 3 resistors circuit: (10 + 22) + 10 |
|- 
|2 
|Yageo 
| MFP-25BRD52-2K2 
| Resistor, 2.2k Ohm, 0.1% 
| No 
| Resistor, 2.2k Ohm, 1%
|- 
|1 
|Tyco 
| 282834-6 
| Terminal block, 6 connector 
| No 
|
|- 
|2 
|Panasonic 
| ERJ-3GEYJ332V 
| Resistor, 3.3k Ohm 
| Yes
| 3 resistors circuit: (22K + 22K) + 22
|- 
|4 
|Panasonic 
| ERJ-3GEYJ102V 
| Resistor, 1k Ohm 
| Yes 
| As is
|- 
|1 
| Panasonic 
| ERG-1SJ510 
| Resistor, 51 Ohm, 1 W 
| No 
| [http://www.okaphone.com/artikel.asp?id=468110 Okaphone RC56E]: Resistor, 56 Ohm, 1 W
|- 
|1 
| Fairchild 
| RFD3055LE 
| Transistor, MOSFET N-Ch 
| No 
|
|- 
|1 
| Microchip 
| MCP3551-E/SN 
| ADC, 22 bit 
| No 
| [http://www.okaphone.com/artikel.asp?id=476677 Okaphone MCP3551-E/MS]
|- 
|1 
| Panasonic 
| ECA-1CM332 
| Capacitor, 3300 uF 
| No 
| http://www.conrad.nl/ce/nl/product/421937/Panasonic-Radiale-condensator-serie-FC-EEUFC1C332-x-h-125-mm-x-35-mm-Rastermaat-5-mm-3300-F-16-V
|- 
|1 
| Panasonic 
| ECA-1CM102 
| Capacitor, 1000 uF 
| No 
| http://www.conrad.nl/ce/nl/product/441666/Panasonic-Radiale-elektrolytische-condensator-ECA-ECA1CM102-x-l-10-mm-x-16-mm-Rastermaat-5-mm-1000-F-16-V?queryFromSuggest=true
|- 
|1 
| ST 
| VNH3SP30 
| H-Bridge IC 
| Yes 
| [http://www.okaphone.com/artikel.asp?id=476678 Okaphone VNH3SP30-E]
|- 
|1 
| Custom 
|  
| Peltier, Qmax = 84 W, dT = 78 K, Imax = 7.8 A 
| No 
| [http://www.okaphone.com/artikel.asp?id=471426 Okaphone PELTIER21]: Qmax = 71 W, dT = 67 K, Imax = 8.0 A
|- 
|1 
| US Sensor 
| USP11553 rev none 
| Thermistor / PTC 
| No 
| HEISSLEITER S861/5K/1%/F40, 541-086-23, 500670, EAN: ...46 6996 O (the character capital-O)  3/18, 10671-348, 9549804009 546432717
|- 
|1 
| Custom 
|  
| Kapton Heater, 25 W, 11.3 V 
| No 
|
|}

==== Autonomous parts ====

Things to connect components with/on/to

{| class="wikitable" 
|- # 
| Part 
| What we really bought
|- 1 
| Arduino Uno 
| As is
|- 1 
| MicroATX power supply, 200 W, 14 A on 12 V rail, fan temperature control disabled, 24 pin ATX connector only 
| Scavanged
|- 1 
| Ribbon cable, 16 pin, female - female, 24" 
| ?Hive5
|- 1 
| LCD, HD44780 compatible, 20 chars, 4 rows, blue backlight 
| [http://www.okaphone.com/artikel.asp?id=421513 Okaphone LCD1602LC]: LCD 16 chars, 2 rows 
|
|- 1 
| PC Board 
| Etched, in possession
|- 1 
| USB Cable, A to B, 6 feet 
| In possession
|- 1 
| PSU Power Cord, USA plug, 6 feet 
|
|}


Original wiring of HD44780 compatible LCD display OpenPCR used [http://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller#Architecture Wikipedia]:

<code>
1    Ground
2    VCC (+3.3 to +5V)
3    Contrast adjustment (VO)
4    Register Select (RS). RS=0: Command, RS=1: Data
5    Read/Write (R/W). R/W=0: Write, R/W=1: Read
6    Clock (Enable). Falling edge triggered
7    Bit 0 (Not used in 4-bit operation)
8    Bit 1 (Not used in 4-bit operation)
9    Bit 2 (Not used in 4-bit operation)
10    Bit 3 (Not used in 4-bit operation)
11    Bit 4
12    Bit 5
13    Bit 6
14    Bit 7
15    Backlight Anode (+)
16    Backlight Cathode (-)
</code>

The LCD that was ordered has exactly the same interface (that is: its pins serve exactly the same function)
