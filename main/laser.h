#ifndef __LASER_H__
#define __LASER_H__

int LASER_OUTPUT = 5;
int BUTTON_INPUT = 4;

enum Laser_States { Laser_Init, Laser_Depress, Laser_Press1, Laser_Press2, Laser_Wait };

int Laser_TickFct(int state) {
  switch (state) {
    case Laser_Init:
      state = Laser_Depress;
      break;
    case Laser_Depress:
       if (digitalRead(BUTTON_INPUT) == HIGH) state = Laser_Press1;
      break;
    case Laser_Press1:
      state = Laser_Press2;
      break;
    case Laser_Press2:
      state = Laser_Wait;
      break;
    case Laser_Wait:
      if (digitalRead(BUTTON_INPUT) == LOW) state = Laser_Depress;
      break;
    default:
      state = Laser_Init;
      break;
  }

  switch (state) {
    case Laser_Init:
    case Laser_Depress:
    case Laser_Wait:
      digitalWrite(LASER_OUTPUT, LOW);
      break;
    case Laser_Press1:
    case Laser_Press2:
      digitalWrite(LASER_OUTPUT, HIGH);
      break;
    default:
      break;
  }
  
  return state;
}

#endif //__LASER_H__
