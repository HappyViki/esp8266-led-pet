# ESP8266 LED Pet

I used this project to learn C and about ESP8266 programming.

[Watch video of it in action!](https://photos.app.goo.gl/nQjPjED9Z29yTqBX8)

## Quick Start

### Prerequisites
[Setup hardware from here](https://www.thingiverse.com/thing:2867294)

#### Software

- [git](https://git-scm.com/downloads)
- [node](https://nodejs.org/en/download/)
- [platformio](https://docs.platformio.org/en/stable/installation.html)

### Commands

`git clone https://github.com/HappyViki/esp8266-led-pet.git`

- Config secrets-config.h with your wifi user/pass and server's network ip
- Rename secrets-config.h -> secrets.h
- Plug your device into the computer

```
cd esp8266-led-pet
npm install
pio run --target upload
node server.js
```

If the device is connected to the server correctly, it should start animating sad faces.

If it's not, it will just perpetually be happy.

Go to http://localhost:8080/ in your browser and click the carrot button.

You should see an eating animation on the device.

## Helpful Links

- [C Essential Training: 1 The Basics](https://www.lynda.com/C-tutorials/C-Essential-Training-1-Basics/772324-2.html) (Free with some library cards)
- [Original code that got me to make this](https://github.com/Qrome/marquee-scroller)
- [PlatformIO baud rate](https://docs.platformio.org/en/latest/projectconf/section_env_monitor.html#monitor-speed)
- [Connect ESP8266 to server](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html)
- [Guide to PROGMEM on ESP8266 and Arduino IDE](https://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html)
