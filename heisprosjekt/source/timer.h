#pragma once


/*begins the timer by making
timeElapsed take in time(NULL) from time.h library*/
void time_begin_timer();


/*we do not wish to freeze other processes
and use therefore binary logic to element the
3 second rule to the elevator */
int time_is_up();

/* sets time_elapsed back
to default state which is 0*/
void time_end_timer();

/*Get time_elapsed for
external modules*/
int get_time_elapsed();
