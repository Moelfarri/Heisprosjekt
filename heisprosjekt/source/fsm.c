#include "hardware.h"
#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include "queue_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//used to determine the direction for move state
int dir;

//used for emergencystop state to reset to move correctly after a stop situation
state_elev prev_state;



// puts the elevator in the idle state
state_elev state_INIT(){
	elev_init();
	if(!(elev_init())) {
		 printf("Could not initialize \n");
	}

	while(1){
		if(hw_floor_sensor_read()<0) { //If sensor doesnt read floor it returns -1
			hw_motor_dir(DIRN_UP);
		}
		if(hw_floor_sensor_read()>=0) {
			elev_set_floor_indicator(hw_floor_sensor_read());
			hw_motor_dir(DIRN_STOP);
			return idle;
		}
	}
}


// stays in the idle state unless there is an order
state_elev state_IDLE(){
	if(q_has_order()){
		return move;
	}
	return idle;
}




// executes the orders
state_elev state_MOVE(){
	int current_floor = hw_floor_sensor_read();
	hw_order_light_outside(current_floor);
  	state_elev state = move;


	if(current_floor != -1){

		for (int floor=0; floor< N_FLOORS; floor++){
			for(int button=0; button<N_BUTTONS; button++ ){
				if (q_get_specific_order(floor, button)){
					if(floor==current_floor && q_should_stop_at_floor(floor)) {
						state = door;
					}
					else if(q_has_orders_above() && prev_dir == 1){
						hw_motor_dir(DIRN_UP);
					}
					else if(q_has_orders_below() && prev_dir == -1){
						hw_motor_dir(DIRN_DOWN);
					}
					else if(q_has_orders_above() && prev_dir == -1){
						hw_motor_dir(DIRN_DOWN);
					}
					else if(q_has_orders_below() && prev_dir == 1){
						hw_motor_dir(DIRN_UP);
					}
					else {
						dir = ((floor-scanned_floor)/(abs(floor-scanned_floor))); //calculates direction
						hw_motor_dir(dir);
					}

				}
			}
		}
		//if the elevator hits a floor, it checks if it should stop
		if (q_should_stop_at_floor(scanned_floor)){
				state = door;
		}
	}



	//between floors and prev_state was emergency stop.
	else if(current_floor == -1 && prev_state == emergencystop ){
		if(prev_dir== 1){

			//check orders coming from above
			if(q_has_orders_above()){
				dir = 1;
				hw_motor_dir(DIRN_UP);
			}
			//check orders coming from below as well as the previously scanned floor hence the +1
			else if(q_has_orders_below_with_input(scanned_floor+1)){
				dir = -1;
				hw_motor_dir(DIRN_DOWN);
				scanned_floor++;

			}


		}

		else if( prev_dir == -1){
			if(q_has_orders_below()){
				dir = -1;
				hw_motor_dir(DIRN_DOWN);
			}

			//check orders coming from above as well as the previously scanned floor hence the -1
			else if(q_has_orders_above_with_input(scanned_floor-1)){
				dir = 1;
				hw_motor_dir(DIRN_UP);
				scanned_floor--;
			}

		}
		prev_state = move;

	}


	return state;

}


state_elev state_OPENDOOR(){

	//restart timer if any button in the same floor is pressed again
	if( q_get_specific_order(scanned_floor, 0) || q_get_specific_order(scanned_floor, 1) || q_get_specific_order(scanned_floor, 2)){
		time_end_timer();
	}

	if(get_time_elapsed() == 0){
		q_remove_order();
		time_begin_timer();
	}
	hw_motor_dir(DIRN_STOP);
	hw_door_opener();
	if(time_is_up()){
		time_end_timer();
		hw_door_closer();
		return idle;
	}
  return door;
}



state_elev state_EMERGENCYSTOP(){
	int current_floor = hw_floor_sensor_read();
	state_elev state = emergencystop;
	prev_state = emergencystop;
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	q_clear_all_orders();

   //DONT DO ANYTHING ELSE IF THIS IS TURNED ON
	while(elev_get_stop_signal()){if(current_floor != -1){hw_door_opener();}} //oppfyller kravspesifikasjon D3

	if(current_floor != -1){
		if(get_time_elapsed()== -1){ //open the door!
			time_begin_timer();
		}

		elev_set_stop_lamp(0);
		state = door;

	}

	//Elevator has stopped between floors
	else if(current_floor == -1){
        	hw_door_closer();
		elev_set_stop_lamp(0);
		state = idle;

	}



return state;
}
