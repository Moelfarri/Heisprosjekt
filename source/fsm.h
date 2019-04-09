#pragma once


//typedef enum states {state_INIT,state_IDLE,state_OPENDOOR,state_MOVE,state_EMERGENCY_STOP} state_t;
typedef enum states {idle, move, door,emergencystop} state_elev;

state_elev state_start();
state_elev state_IDLE();
state_elev state_OPENDOOR();
state_elev state_INIT();
state_elev state_MOVE();
state_elev state_EMERGENCYSTOP();
