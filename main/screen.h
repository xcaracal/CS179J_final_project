#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

extern int id;
extern int ammo;

int screenTickFct(int state) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setTextSize(1);
  display.setCursor(0,0);
  char id_buffer[16];
  sprintf(id_buffer, "ID: %i", id);
  display.print(id_buffer);
  display.setCursor(0,20);
  display.print("Ammo:");
  display.setCursor(0, 30);
  display.setTextSize(3);
  char ammo_buffer[8];
  sprintf(ammo_buffer, "%d / 10", ammo);  
  display.print(ammo_buffer);
  display.display();
  return 0;
}
