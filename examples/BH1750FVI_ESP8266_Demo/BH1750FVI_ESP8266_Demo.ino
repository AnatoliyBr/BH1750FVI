/***************************************************************************************************/
/* 
  Example for ROHM BH1750FVI Ambient Light Sensor library

  Power supply voltage: 2.4 - 3.6v
  Default range:        1 - 65'535 lux
  Measurement accuracy: ±20%, possible to calibrate
  Peak wave length:     560nm, yellow-green

  written by : enjoyneering79
  sourse code: https://github.com/enjoyneering/

  This chip uses I2C bus to communicate, specials pins are required to interface
  Board:                                    SDA                    SCL                    Level
  Uno, Mini, Pro, ATmega168, ATmega328..... A4                     A5                     5v
  Mega2560................................. 20                     21                     5v
  Due, SAM3X8E............................. 20                     21                     3.3v
  Leonardo, Micro, ATmega32U4.............. 2                      3                      5v
  Digistump, Trinket, ATtiny85............. 0/physical pin no.5    2/physical pin no.7    5v
  Blue Pill, STM32F103xxxx boards.......... PB7                    PB6                    3.3v/5v
  ESP8266 ESP-01........................... GPIO0/D5               GPIO2/D3               3.3v/5v
  NodeMCU 1.0, WeMos D1 Mini............... GPIO4/D2               GPIO5/D1               3.3v/5v
  ESP32.................................... GPIO21/D21             GPIO22/D22             3.3v

  Frameworks & Libraries:
  ATtiny Core           - https://github.com/SpenceKonde/ATTinyCore
  ESP32 Core            - https://github.com/espressif/arduino-esp32
  ESP8266 Core          - https://github.com/esp8266/Arduino
  ESP8266 I2C lib fixed - https://github.com/enjoyneering/ESP8266-I2C-Driver
  STM32 Core            - https://github.com/rogerclarkmelbourne/Arduino_STM32

  GNU GPL license, all text above must be included in any redistribution, see link below for details:
  - https://www.gnu.org/licenses/licenses.html
*/
/***************************************************************************************************/
#include <Wire.h>        //for esp8266 use bug free i2c driver https://github.com/enjoyneering/ESP8266-I2C-Driver
#include <BH1750FVI.h>
#include <ESP8266WiFi.h>

/*
BH1750FVI(address, resolution, sensitivity, accuracy)

BH1750_DEFAULT_I2CADDR            - address pin LOW
BH1750_SECOND_I2CADDR             - address pin HIGH

BH1750_CONTINUOUS_HIGH_RES_MODE   - continuous measurement, 1.0 lx resolution
BH1750_CONTINUOUS_HIGH_RES_MODE_2 - continuous measurement, 0.5 lx resolution
BH1750_CONTINUOUS_LOW_RES_MODE    - continuous measurement, 0.5 lx resolution
BH1750_ONE_TIME_HIGH_RES_MODE     - one measurement & power down, 1.0 lx resolution
BH1750_ONE_TIME_HIGH_RES_MODE_2   - one measurement & power down, 0.5 lx resolution
BH1750_ONE_TIME_LOW_RES_MODE      - one measurement & power down, 4.0 lx resolution

sensitivity                       - value have to be between 0.45 - 3.68, default 1.00 or use macros BH1750_SENSITIVITY_DEFAULT
accuracy                          - value have to be between 0.96 - 1.44, default 1.20 or use macros BH1750_ACCURACY_DEFAULT
*/
BH1750FVI myBH1750(BH1750_DEFAULT_I2CADDR, BH1750_CONTINUOUS_HIGH_RES_MODE_2, BH1750_SENSITIVITY_DEFAULT, BH1750_ACCURACY_DEFAULT);


void setup()
{
  WiFi.persistent(false);                               //disable saving wifi config into SDK flash area
  WiFi.forceSleepBegin();                               //disable AP & station by calling "WiFi.mode(WIFI_OFF)" & put modem to sleep

  Serial.begin(115200);
  Serial.println();

  while (myBH1750.begin(D2, D1) != true)                //SDA - D2, SCL - D1
  {
    Serial.println(F("ROHM BH1750FVI is not present")); //(F()) saves string to flash & keeps dynamic memory free
    delay(5000);
  }

  Serial.println(F("ROHM BH1750FVI is present"));
}

/*
    setSensitivity()

    This option is used to compensate the influence of the optical filter.
    For example, when transmission rate of optical window is 50% (measurement
    result becomes 0.5 times lower), influence of optical window is ignored
    by changing sensor sensitivity from default 1.0 to 2.0 times
*/

void loop()
{
  /* DEMO - 1 */
  Serial.println(F("DEMO 1: Sensitivity - 1.0, Continuous High Res II Mode"));
  Serial.print(F("Light level.........: ")); Serial.print(myBH1750.readLightLevel());     Serial.println(F(" +-0.5 lx"));
  Serial.print(F("Power for 555nm wave: ")); Serial.print(myBH1750.readLightLevel()/683); Serial.println(F(" Watt/m^2"));


  /* DEMO - 2 */
  Serial.println(F("DEMO 2: Sensitivity - 2.00, Continuous High Res II Mode"));
  myBH1750.setSensitivity(2.00);

  Serial.print(F("Light level.........: ")); Serial.print(myBH1750.readLightLevel());     Serial.println(F(" +-0.5 lx"));


   /* DEMO - 3 */
  Serial.println(F("DEMO 3: Sensitivity - 0.50, Continuous High Res II Mode"));
  myBH1750.setSensitivity(0.50);

  Serial.print(F("Light level.........: ")); Serial.print(myBH1750.readLightLevel());     Serial.println(F(" +-0.5 lx"));


  /* DEMO - 4 */
  Serial.println(F("DEMO 4: Sensitivity - 3.68, Power Down High Res   Mode"));
  myBH1750.setSensitivity(3.68);
  myBH1750.setResolution(BH1750_ONE_TIME_HIGH_RES_MODE);

  Serial.print(F("Light level.........: ")); Serial.print(myBH1750.readLightLevel());     Serial.println(F(" +-1.0 lx"));

 
  /* DEMO - 5 */
  Serial.println(F("DEMO 5: Sensitivity - 0.45, Continuous High Res II Mode"));
  myBH1750.setSensitivity(0.45);
  myBH1750.setResolution(BH1750_CONTINUOUS_HIGH_RES_MODE_2);

  Serial.print(F("Light level.........: ")); Serial.print(myBH1750.readLightLevel());     Serial.println(F(" +-0.5 lx"));


  /* DEMO - 6 */
  Serial.println(F("DEMO 6: Sensitivity - 1.00, Power Down High Res II Mode"));
  myBH1750.setSensitivity(1.00);
  myBH1750.setResolution(BH1750_ONE_TIME_HIGH_RES_MODE_2);

  Serial.print(F("Light level.........: ")); Serial.print(myBH1750.readLightLevel());     Serial.println(F(" +-0.5 lx"));


  /* DEMO - 7 */ 
  Serial.println(F("DEMO 7: Manual Reset & Power Down"));
  myBH1750.reset();
  myBH1750.powerDown();


  /* back to lib. default resolution */
  myBH1750.setResolution(BH1750_CONTINUOUS_HIGH_RES_MODE_2);

  Serial.print(F("DEMO: Starts over again in 5 sec."));
  delay(5000);
}
