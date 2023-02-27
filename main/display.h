#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

enum Screen_States { Screen_Init, Screen_Game, Screen_Respawn, Screen_Reload };

int Screen_TickFct(int state) {
	switch (state) {
		case Screen_Init:
			
			break;
		case Screen_Game:

			break;
		case Screen_Respawn:

			break;
		case Screen_Reload:

			break;
		default:
			state = Screen_Init;
			break;
	}
	switch (state) {	
		case Screen_Init:
			
			break;
		case Screen_Game:
			lcd.setCursor(0,0);
			lcd.print("SCORE: ");
			break;
		case Screen_Respawn:
			lcd.setCursor(0,0);
			lcd.print("RESPAWNING IN...");
			break;
		case Screen_Reload:
			lcd.setCursor(0,0);
			lcd.print("Reloading...");
			break;
		default:
			state = Screen_Init;
			break;
	}
  return state;
}

#endif //__DISPLAY_H__
