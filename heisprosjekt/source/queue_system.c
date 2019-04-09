
#include "hardware.h"
#include "elev.h"
#include "queue_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int scanned_floor;


//adds order to the matrix and turns on approperiate lamp
void q_add_order(){
	for (int floor = 0; floor < N_FLOORS; floor++) { 	//N_FLOORS-1 = 3
		for (int button = 0; button < N_BUTTONS; button++) {
			if (elev_get_button_signal(button, floor)) {
				queue_matrix[floor][button] = 1;
				elev_set_button_lamp(button,floor,1);
			}
		}
	}
}

//removes order from the matrix and turns of appropriate lamp
void q_remove_order(){
	int current_floor = hw_floor_sensor_read();

	if(current_floor != -1){
	for(int button=0; button<N_BUTTONS; button++ ){
		queue_matrix[current_floor][button] = 0;
		elev_set_button_lamp(button,current_floor,0);
	}
	}
}



//removes all matrix orders and clear all button lights
void q_clear_all_orders(){ 
	for (int floor=0; floor< N_FLOORS; floor++){
	   for(int button=0; button<N_BUTTONS; button++ ){
	   		queue_matrix[floor][button] = 0;
	   		elev_set_button_lamp(button, floor, 0);


        }
    }
}


//checks if there is an order above the most recent scanned floor
int q_has_orders_above(){
	for (int floor=scanned_floor+1; floor < N_FLOORS; floor++){
		for(int button=0; button<N_BUTTONS; button++ ){
			if(queue_matrix[floor][button]){
				return 1;
			}
		}
	}
	return 0;
}



//checks if there is an order below the most recent scanned floor
int q_has_orders_below(){
	for (int floor=0; floor < scanned_floor; floor++){
		for(int button=0; button<N_BUTTONS; button++ ){
			if(queue_matrix[floor][button]){
				return 1;
			}
		}
	}
	return 0;
}



//Used to call upon the matrix externally of this module
int q_get_specific_order(int floor, int button){
  if (queue_matrix[floor][button]){ return 1;}
  return 0;

}



//variation of the first two above and below functions that allows for input
int q_has_orders_above_with_input(int scanned_floor){
	for (int floor=scanned_floor+1; floor < N_FLOORS; floor++){
		for(int button=0; button<N_BUTTONS; button++ ){
			if(queue_matrix[floor][button]){
				return 1;
			}
		}
	}
	return 0;
}




//variation of the first two above and below functions that allows for input
int q_has_orders_below_with_input(int scanned_floor){
	for (int floor=0; floor < scanned_floor; floor++){
		for(int button=0; button<N_BUTTONS; button++ ){
			if(queue_matrix[floor][button]){
				return 1;
			}
		}
	}
	return 0;
}





//Checks if the queue has any order
int q_has_order(){
	for (int floor=0; floor< N_FLOORS; floor++){ 	
		for(int button=0; button<N_BUTTONS; button++ ){
			if (queue_matrix[floor][button]) {  
				return 1;
			}
		}
	}
	return 0;
}




/*checks if the matrix has reached the satisfied 
floor such that this function can be called upon and stop*/
int q_should_stop_at_floor(int current_floor){
	for(int button=0; button<N_BUTTONS; button++ ){
		if(queue_matrix[current_floor][button]){
			if(button == 0 && prev_dir == 1){
				return 1;
			}
			else if(button == 1 && prev_dir == -1){
				return 1;
			}
			else if(button == 2){
				return 1;
			}
			else if(button == 1 && !q_has_orders_above()){
				return 1;
			}
			else if(button == 0 && !q_has_orders_below()){
				return 1;
			}
		}
	}
	return 0;
}
