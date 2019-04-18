#include "elev.h"
#include "io.h"
#include "queue_system.h"

int prev_dir;



void hw_motor_dir(int dir){
	elev_set_motor_direction(dir);
	prev_dir = dir;
}

void hw_door_opener() {
	elev_set_door_open_lamp(1);
}

void hw_door_closer() {
	elev_set_door_open_lamp(0);
}


int hw_floor_sensor_read() {
	//int flr = (elev_get_floor_sensor_signal());
	return (elev_get_floor_sensor_signal());
}

void hw_order_light_outside(int flr) {
	int current_floor = hw_floor_sensor_read();
	if(current_floor != -1){elev_set_floor_indicator(flr);}
}

void hw_scan_floor(){
	int current_floor = hw_floor_sensor_read();
	if(current_floor != -1){ scanned_floor = current_floor;}
}
