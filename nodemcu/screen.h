#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "holder.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int screenTickFct(int state) {
  if(!_ALIVE) {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(0,30);
    display.print("DEAD");
    display.display();
  }
  else {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setTextSize(1);
  display.setCursor(0,0);
  char id_buffer[16];
  sprintf(id_buffer, "ID: %i", _ID);
  display.print(id_buffer);
  display.setCursor(0,20);
  display.print("Ammo:");
  display.setCursor(0, 30);
  display.setTextSize(3);
  char ammo_buffer[8];
  sprintf(ammo_buffer, "%d / 10", _AMMO);  
  display.print(ammo_buffer);
  display.display();
  }
  return 0;
}
