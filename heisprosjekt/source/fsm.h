/**
* @file
* @brief A module which controlls what happens in each state.
*/


#pragma once


/**
* @brief The different possible states for the finite state machine.
*/
typedef enum states {idle, move, door, emergencystop} state_elev;

/**
* @brief The intial state, which sets the elevator to the idle state
* which means it is in a floor.
*
* @return The idle state
*/
state_elev state_INIT();

/**
* @brief The idle state, which does nothing except if an 
* order exists, then it moves to the move state.
*
* @return The move state if there is an order, otherwise it returns 
* the idle state.
*/
state_elev state_IDLE();

/**
* @brief The move state, which executes the orders.
*
* @return The door state if there is an order at the current floor,
* otherwise the move state.
*/
state_elev state_MOVE();

/**
* @brief The door state, when the elevator hits a floor and there 
* is an order there, it deletes the order and opens the door.
*
* @return It returns to itself until the 3 second timer has elapsed,
* then it returns the idle state.
*/
state_elev state_OPENDOOR();

/**
* @brief The emergencystop state, which stops the elevator and deletes the orders.
*
* @return It returns the door state if it is stopped at a floor,
* and it returns the idle state if it has been stopped between floors.
*/
state_elev state_EMERGENCYSTOP();