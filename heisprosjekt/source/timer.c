#include <time.h>
#include "stdio.h"


/*time variable that
keeps track of how many seconds have elapsed*/
int time_elapsed = 0;

//begins timer
void time_begin_timer() {
	time_elapsed = time(NULL);
}

//checks if timer has passed the 3 second threshold
int time_is_up() {
	printf("tid %ld", (time(NULL) - time_elapsed));
	if ((time(NULL) - time_elapsed) >= 3) {
		return 1;
	}
	return 0;
}

//resets timer to 0
void time_end_timer() {
	time_elapsed = 0;
}

//gets time elapsed variable
int get_time_elapsed(){
	return time_elapsed;
}
