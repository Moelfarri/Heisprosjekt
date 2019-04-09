#include "elev.h"
#include <stdio.h>
#include "hardware.h"
#include "fsm.h"
#include "queue_system.h"

int main(){

    //if between two floors, go to nearest upper floor
    state_elev state = state_INIT();
    while (1) {
    	//scans only if sensor detects a floor
    	hw_scan_floor();

    	//detect a button press and add order to the queue
    	q_add_order();

    	printf("state: %d\n", state);
        
        //detect a stop button press at any time  
    	if(elev_get_stop_signal()){
            state = emergencystop;
    	}

    	
		switch (state) {
			case idle:
			state = state_IDLE();
			break;

			case move:
			state = state_MOVE();
			break;

			case door:
			state = state_OPENDOOR();
	 		break;

	 		case emergencystop:
	 		state = state_EMERGENCYSTOP();
	 		break;
	 	}


	}


    return 0;
}
