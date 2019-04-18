/**
* @file
* @brief A module for controlling the sensors and lights for the elevator.
*/


#pragma once
/**
* @brief A variable which tells the last direction of the elevator.
*/
extern int prev_dir;

/**
* @brief A function which opens the door.
*/
//Door
/*sets door light on*/
void hw_door_opener();

/**
* @brief A function which closes the door.
*/
/*sets door light off*/
void hw_door_closer();

/**
* @brief A function which reads the sensor position at all times returns -1
* if not at a floor otherwise returns 0-3 which represents first to fourth floor.
*
* @return -1 if the elevator is between floors and 0-3 representing
* the four floors in ascending order.
*/
//Sensor and lights
/*reads the sensor position at all times returns -1
if not at a floor otherwise returns 0-3 which represents first to fourth floor*/
int hw_floor_sensor_read();

/**
* @brief A function which turns on the floor indicators on
* the outside of the elevator.
*
* @param flr An int for which floor it is on.
*/
/*turns the floor light on approperiately to what floor we are on*/
void hw_order_light_outside(int flr);

/**
* @brief A function which will only change value if the 
* elevator is on a floor.
*/
/*returns only 0-3 values such that it reads a floor if and only if
the sensor is on a floor*/
void hw_scan_floor();

/**
* @brief A function which sets the motor direction.
* 
* @param dir The direction of the elevator, 1 as up, 0 as stop and -1 as down direction.
*/
//Motor
/*turns motor on by returning 1 as up, 0 as stop and -1 as down direction*/
void hw_motor_dir(int dir);
