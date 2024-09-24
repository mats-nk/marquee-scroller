/****************************** The MIT License (MIT) *******************************************************

Copyright (c) 2018 David Payne, see included file LICENSE.txt

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without
limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 ************************************************************************************************************/

/************************************************************************************************************
 * NOTE: The settings here are the default settings for the first loading.
 * After loading you will manage changes to the settings via the Web Interface.
 * If you want to change settings again in the settings.h, you will need to erase the file system on the
 * Wemos or use the “Reset Settings” option in the Web Interface.
 ************************************************************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiManager.h>                    // https://github.com/tzapu/WiFiManager
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "FS.h"
#include <SPI.h>
#include <Adafruit_GFX.h>                   // https://github.com/adafruit/Adafruit-GFX-Library
#include <Max72xxPanel.h>                   // https://github.com/markruys/arduino-Max72xxPanel
#include <pgmspace.h>
#include "OpenWeatherMapClient.h"
#include "TimeDB.h"                         // https://github.com/PaulStoffregen/Time
                                            // https://github.com/squix78/json-streaming-parser


//******************************
// Default Settings
//******************************

// OpenWeather settings
String TIMEDBKEY = "";                      // Your API Key from https://timezonedb.com/register
String APIKEY = "";                         // Your API Key from http://openweathermap.org/
int CityIDs[] = { 00000 };                  // Default City Location (use http://openweathermap.org/find

// Time
boolean IS_METRIC = true;                   // false = Imperial or true = Metric
boolean IS_24HOUR = true;                   // 24 hour clock
boolean IS_PM = false;                      // Show PM indicator on Clock when in AM/PM mode

String marqueeMessage = "";

// Web interface
const int WEBSERVER_PORT = 80;              // The port you can access this device on over HTTP
const boolean WEBSERVER_ENABLED = true;     // Device will provide a web interface via http://[ip]:[port]/
boolean IS_BASIC_AUTH = false;              // Use Basic Authorization for Configuration security on Web Interface
char* www_username = "";                    // User account for the Web Interface
char* www_password = "";                    // Password for the Web Interface

int minutesBetweenDataRefresh = 15;         // Time in minutes between data refresh (default 15 minutes)
int minutesBetweenScrolling = 1;            // Time in minutes between scrolling data (default 1 minutes and max is 10)
int displayScrollSpeed = 25;                // In milliseconds -- Configurable by the web UI (slow = 35, normal = 25, fast = 15, very fast = 5)
boolean flashOnSeconds = true;              // When true the : character in the time will flash on and off as a seconds indicator

// Display Settings
// ----------------
// Display wiring  |  CLK -> D5 (SCK)
//                 |  CS  -> D6 (Configurable via pinCS)
//                 |  DIN -> D7 (MOSI)
const int pinCS = D6;                       // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int displayIntensity = 1;                   // (This can be set from 0 - 15)
const int numberOfHorizontalDisplays = 12;  // Default 4 for standard 4 x 1 display Max size of 16
const int numberOfVerticalDisplays = 1;     // Default 1 for a single row height
int ledRotation = 3;                        // Set ledRotation for LED Display panels (3 is default)
                                            // 0: No rotation           |   2: 180 degrees
                                            // 1: 90 degrees clockwise  |   3: 90 degrees counter clockwise (default)

String timeDisplayTurnsOn = "06:30";        // 24 Hour Format HH:MM -- Leave blank for always on. (ie 05:30)
String timeDisplayTurnsOff = "22:00";       // 24 Hour Format HH:MM -- Leave blank for always on. Both must be set to work.

boolean ENABLE_OTA = true;                  // This will allow you to load firmware to the device over WiFi (see OTA for ESP8266)
String OTA_Password = "";                   // Set an OTA password here -- leave blank if you don't want to be prompted for password


// ******************************
//         End Settings
// ******************************
