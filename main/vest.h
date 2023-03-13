#ifndef __VEST_H__
#define __VEST_H__

int photo_sensor = A0; //ADC0
int blue_LED = 13; //0
int red_LED = 12; //2
int white_LED = 11; //14
int buzzer = 10; //12
unsigned char j;
unsigned char curr_respawn_time = 0; //the time player is at currently during respawn
const int total_respawn_time = 50; //period = 200 ms => respwan time = 10 secs of total respawn time
const int ps_threshold = 1000; //>= 900? means photosensor registers laser input

enum Vest_States { Vest_Init, Vest_Hit, Vest_NotHit, Vest_Respawning };

int Vest_TickFct(int state) {
  switch (state) {
    case Vest_Init:
      if(analogRead(photo_sensor) >= ps_threshold) 
        state = Vest_Hit;
      if(analogRead(photo_sensor) < ps_threshold) 
        state = Vest_NotHit;
      break;
    case Vest_Hit:
      state = Vest_Respawning;
      break;
    case Vest_NotHit:
      if(analogRead(photo_sensor) >= ps_threshold) 
        state = Vest_Hit;
      if(analogRead(photo_sensor) < ps_threshold) 
        state = Vest_NotHit;
      break;
    case Vest_Respawning:
      if(curr_respawn_time < total_respawn_time)
        state = Vest_Respawning;
      if(curr_respawn_time >= total_respawn_time)
        state = Vest_NotHit;
      break;
    default:
      state = Vest_Init;
      break;
  }

  switch (state) {
    case Vest_Init:
    case Vest_Hit:
      digitalWrite(blue_LED, LOW);
      digitalWrite(white_LED, LOW);
      digitalWrite(red_LED, HIGH);
      digitalWrite(alivePin, HIGH);
      for(j = 0; j < 100; j++){
        digitalWrite(buzzer, HIGH);
        delay(2);
        digitalWrite(buzzer, LOW);
        delay(2);
      }
      curr_respawn_time = 0;
      break;
    case Vest_NotHit:
      digitalWrite(blue_LED, HIGH);
      digitalWrite(white_LED, HIGH);
      digitalWrite(red_LED, LOW);
      digitalWrite(buzzer, LOW);
      digitalWrite(alivePin, LOW);
      break;
    case Vest_Respawning:
      digitalWrite(blue_LED, LOW);
      digitalWrite(white_LED, LOW);
      digitalWrite(red_LED, HIGH);
      curr_respawn_time++;
      break;
    default:
      break;
  }
  
  return state;
}

#endif //__VEST_H__