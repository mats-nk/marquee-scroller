ToDo
====

Other ToDo
==========
- Change display off behaviour. Inside display off = Display off even if it is restarted within display off.
- Button for display on/off
- LDR to automate light intensity
- PIR for proximity detection
- The font for weather on web page is incoherent, font size differs
- Add local language file
- Add lang= to OpenWeather
- Alexa support
- HTTP API for display on/off and dimming

- Add a locally connect Temp Sensor and add to display / alternating time/temp at a set period
- An LDR to adjust the brightness of LED Display based on ambient light
- A Proximity sensor, so if display off then the movement will turn on.



OpenWeatherMapClient.cpp
------------------------
Commented out:
Convert to kph from m/s

Row 128, Commented out "Convert to kph from m/s"

Row 241, `String arr[] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};`
Wind directions

Row 290ish has weekday names


TimeDB.cpp
----------
Row 126 Month names


Other tasks from "feature requests"
-----------------------------------

### No 1

I only want to see the current time and temperature and therefore want do disable scrolling. (If all additional modules are disabled, weather is scrolling even it is displayed on the main page)

I disabled scrolling by commenting out line 413 in marquee.ino [ //scrollMessage(msg); ]

Maybe you could wrap this with an if and make it configurable in the Web UI. eg. "Minutes between scrolling Data"  = 0?


### No 2

To get the weather in different language sis quite simple; just add lang=

See: https://openweathermap.org/current#multi

Example: `https://api.openweathermap.org/data/2.5/weather?id="city id"&appid="API key"&lang=de`