#include <time.h>
#include "stdio.h"

int time_elapsed = 0;


void time_begin_timer() {
	time_elapsed = time(NULL);
}

int time_is_up() {
	printf("tid %ld", (time(NULL) - time_elapsed));
	if ((time(NULL) - time_elapsed) >= 3) {
		return 1;
	}
	return 0;
}


void time_end_timer() {
	time_elapsed = 0;
}

int get_time_elapsed(){
	return time_elapsed;
}
