#pragma once


//Different states of our Finite State Machine
typedef enum states {idle, move, door,emergencystop} state_elev;

state_elev state_INIT();
state_elev state_IDLE();
state_elev state_MOVE();
state_elev state_OPENDOOR();
state_elev state_EMERGENCYSTOP();

//brukes denne? @avgjør om du skal fjerne den håkon
state_elev state_start();
