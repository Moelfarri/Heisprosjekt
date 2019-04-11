#pragma once


/*begins the timer by making
time_elapsed take in time(NULL) from time.h library and start counting*/
void time_begin_timer();


/*we do not wish to freeze other processes
and use therefore binary logic to element the
3 second rule to the elevator. Returns 1 if time_Elapsed = 3 */
int time_is_up();

/* sets time_elapsed back
to default state which is 0*/
void time_end_timer();

/*Get time_elapsed for
external modules*/
int get_time_elapsed();
