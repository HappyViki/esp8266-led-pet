#include <Arduino.h>
#include <esp8266_pins.h>
#include <esp8266WIFI.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <max7219.h>
#include <fonts.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// 1) Config secrets-config.h with your wifi user/pass and server's network ip,
// 2) Rename secrets-config.h -> secrets.h
#include <secrets.h>

IPAddress server(IP);

// Initialize the client library
WiFiClient client;
HTTPClient http;

//default brightness - can be from 0x0 to 0xF
#define DEFAULT_BRIGHTNESS 0x6U

//this is the offset between EEPROM data values in bytes:
#define EEPROM_BYTE_OFFSET 4U

//this is how many bytes of EEPROM are reserved for storing settings data (Number of bytes per item stored * number of items being stored +2 bytes for ):
#define NUM_EEPROM_BYTES (EEPROM_BYTE_OFFSET * 6U)

//this timeout is for initial connections to the wifi. It will only try for this many ms.
#define WIFI_TIMEOUT 10000UL

//this tracks the last wifi connection time for reconnect attempts:
uint32_t last_wifi_connection_attempt = 0;

// Pet stats
int age = 0;

bool connect_to_wifi(void)
{
  uint32_t wifi_connection_timeout = millis();
  last_wifi_connection_attempt = millis();

  WiFi.begin(WIFI_NAME, WIFI_PASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    if(millis() >= wifi_connection_timeout + WIFI_TIMEOUT){
      Serial.println();
      Serial.println("Unable to connect.");
      return false;
    }
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

const uint8_t face[] PROGMEM = {5,
B01010, B01010, B00000, B10001, B11111, // :)
B01010, B01010, B00000, B11111, B00000, // :|
B01010, B01010, B00000, B11111, B10001, // :(
B01010, B01010, B11111, B10001, B11111, // :o
B01010, B01010, B00000, B11111, B11111, // :||
};

const uint8_t carrot[] PROGMEM = {8,
B01010, B10001, B11001, B10011, B11001, B10011, B01010, B00100, // body
};

void display_food(int foodIndex)
{
  static int i;
  static int carrotLength = pgm_read_byte(carrot);
  for (i=0;i<carrotLength;i++){
    scr[i+8] = pgm_read_byte(carrot + i + 1 + carrotLength * foodIndex);
  }
  refreshAll();
}

void display_face(int faceIndex, int speed = 1000)
{
  static int i;
  static int faceLength = pgm_read_byte(face);
  for (i=0;i<faceLength;i++){
    scr[i] = pgm_read_byte(face + i + 1 + faceLength * faceIndex);
  }
  refreshAll();
  delay(speed);
}

void display_eating_pet()
{
  display_face(0);
  display_face(3);
  display_face(1);
  display_face(3);
  display_face(1);
  display_face(3);
  display_face(1);
  display_face(0);
}

void display_hungry_pet()
{
  display_face(2);
  display_face(4, 500);
  display_face(2);
  display_face(4, 500);
  display_face(2, 500);
  display_face(4, 500);
  display_face(2);
}

// ref: https://stackoverflow.com/a/2603254/1053092
static unsigned char lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

uint8_t reverse(uint8_t n) {
   // Reverse the top and bottom nibble then swap them.
   return (lookup[n&0b1111] << 4) | lookup[n>>4];
}

void display_letter(char letter)
{
  uint16_t row_count = NUM_MAX*8;
  uint8_t font_width = pgm_read_byte(font);
  unsigned int font_row = font_width * (letter - 32) + 1;
  uint8_t letter_width = pgm_read_byte(font + font_row);

  uint8_t current_letter_pixel = 0;

  while(letter_width > current_letter_pixel)
  {
    scr[row_count - (letter_width + current_letter_pixel + 1)] =
    reverse(pgm_read_byte(font + font_row + current_letter_pixel + 1));
    current_letter_pixel++;
  }
  refreshAllRot90();
}

void setup()
{
  //set up the EEPROM section of the flash:
  EEPROM.begin(NUM_EEPROM_BYTES);

  Serial.begin(115200);
  Serial.println();

  //init displays:
  initMAX7219();
  sendCmdAll(CMD_SHUTDOWN, 1); //turn shutdown mode off
  sendCmdAll(CMD_INTENSITY, DEFAULT_BRIGHTNESS); //set brightness

  //print an init message to the display:
  display_face(0);

  //connect_to_wifi();
}

void loop()
{
  // if (client.connect(server, 8080)) {
  //   http.begin(client,"http://localhost:8080/feed_pet_from_basket");
  //   int statusCode = http.GET();
  //   Serial.println(statusCode);
  //   Serial.println(http.getString());
  //   if (http.getString() == "carrot" || http.getString() == "cake")
  //   {
  //     display_eating_pet();
  //   }
  //   else
  //   {
  //     display_hungry_pet();
  //   }
  //   http.end();
  // }
  // else
  // {
  //   display_food(0);
  // }
  display_food(0);
  delay(500);
  age += 500;
}
