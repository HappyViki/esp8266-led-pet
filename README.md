# ESP8266 LED Pet

I used this project to learn C and about ESP8266 programming.

## Quick Start

### Prerequisites

[Setup hardware from here](https://github.com/Qrome/marquee-scroller)

#### Software

- [git](https://git-scm.com/downloads)
- [node](https://nodejs.org/en/download/)
- [platformio](https://docs.platformio.org/en/stable/installation.html)

#### Commands

`git clone https://github.com/HappyViki/esp8266-led-pet.git`

- Go to /src/main.cpp and change `IPAddress server(0,0,0,0);` to where the NodeJS server is going to be publicly located.
- Plug your device into the computer.

```
cd esp8266-led-pet
npm install
pio run --target upload
node server.js
```

If the device is connected to the server correctly, it should start animating sad faces. If it's not, it will just perpetually be happy.

Go to http://localhost:8080/ in your browser and click the carrot button.

You should see an eating animation on the device.

_Credits and helpful links coming soon._
