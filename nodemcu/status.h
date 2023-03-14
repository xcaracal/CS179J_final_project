#ifndef __STATUS_H__
#define __STATUS_H__
#include "wifi.h"
#include "holder.h"

const int shootPin = D5;
const int reloadPin = D6;
const int alivePin = D8;
int shootStatus = 0;
int reloadStatus = 0;
int aliveStatus = 0;

enum ShootStates {ShootLow, ShootHigh};
int shootTickFct(int state) {
    shootStatus = digitalRead(shootPin);
    switch(state) {
        case ShootLow:
        if(shootStatus == HIGH) {
            state = ShootHigh;
            _AMMO = shoot(_ID);
        }
        else {
            state = ShootLow;
        }
        break;
        case ShootHigh:
            if(shootStatus == LOW) {
                state = ShootLow;
            }
            else {
                state = ShootHigh;
            }
        break;
        default:
            state = ShootLow;
        break;
    }
    return state;
}

enum ReloadStates {ReloadLow, ReloadHigh};
int reloadTickFct(int state) {
    reloadStatus = digitalRead(reloadPin);
    switch(state) {
        case ReloadLow:
        if(reloadStatus == HIGH) {
            state = ReloadHigh;
            _AMMO = reload(_ID);
        }
        else {
            state = ReloadLow;
        }
        break;
        case ReloadHigh:
        if(reloadStatus == LOW) {
            state = ReloadLow;
        }
        else {
            state = ReloadHigh;
        }
        break;
        default:
            state = ReloadLow;
        break;
    }
    return state;
}

enum AliveStates {AliveIdle, AliveDead};
int aliveTickFct(int state) {
    aliveStatus = digitalRead(alivePin);
    switch(state) {
        case AliveIdle:
        if(aliveStatus == HIGH) {
            state = AliveDead;
            _ALIVE = false;
            dead(_ID);
        }
        else {  
            state = AliveIdle;
        }
        break;
        case AliveDead:
        if(aliveStatus == LOW) {
            state = AliveIdle;
            _ALIVE = true;
            alive(_ID);
        }
        else {
            state = AliveDead;
        }
        break;
        default:
            state = AliveIdle;
        break;
    }
    return state;
}

#endif //__STATUS_H__
