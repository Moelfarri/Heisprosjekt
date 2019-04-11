#pragma once

extern int prev_dir;

//Door
/*sets door light on*/
void hw_door_opener();

/*sets door light off*/
void hw_door_closer();



//Sensor and lights
/*reads the sensor position at all times returns -1
if not at a floor otherwise returns 0-3 which represents first to fourth floor*/
int hw_floor_sensor_read();

/*turns the floor light on approperiately to what floor we are on*/
void hw_order_light_outside(int flr);

/*turns appropriate button light on*/
void hw_turn_on_button_light(int flr, int dir);

/*turns appropriate button light off*/
void hw_turn_off_button_light(int flr, int dir);

/*returns only 0-3 values such that it reads a floor if and only if
the sensor is on a floor*/
void hw_scan_floor();



//Motor
/*turns motor on by returning 1 as up, 0 as stop and -1 as down direction*/
void hw_motor_dir(int dir);
