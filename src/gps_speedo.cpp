#include "application.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

#include <TinyGPS.h>

// LCD pins
#define LCD_SCK D6
#define LCD_MOSI D5
#define LCD_SS D4

Adafruit_SharpMem display(LCD_SCK, LCD_MOSI, LCD_SS);
TinyGPS gps;

#define BLACK 0
#define WHITE 1

void turn_off_status_led()
{
	RGB.control(true);
	RGB.color(0, 0, 0);
}

void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      display.print('*');
    display.print(' ');
  }
  else
  {
    display.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      display.print(' ');
  }
  smartdelay(0);
}

void setup()
{
  // go dark
  WiFi.off();
  turn_off_status_led();

  // init display
  display.begin();
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(4);
  display.setTextColor(BLACK);
  display.refresh();

  // init gps
  Serial1.begin(57600);

  // init debug
  Serial.begin(57600);
}

void loop()
{
  display.clearDisplay();
  display.setCursor(0,0);

  print_float(gps.f_speed_knots(), TinyGPS::GPS_INVALID_F_SPEED, 4, 1);
  display.refresh();

  smartdelay(250);
}

