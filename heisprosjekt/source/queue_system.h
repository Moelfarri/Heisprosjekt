#pragma once
#define N_BUTTONS 3

static int queue_matrix[N_FLOORS][N_BUTTONS] = {};


extern int scanned_floor;

//add and remove matrix functions

/*adds order to the queue matrix by setting 
one of the zeroes in the matrix to one*/
void q_add_order();

/*removes an order from the queue matrix by setting
one of the ones to zero*/
void q_remove_order();

/*deletes all orders and turns off all button lights*/
void q_clear_all_orders();



//Check functions
/*returns 1 if there is any order*/
int q_has_order();

/*returns 1 if there is an order below the elevator
else it returns 0*/
int q_has_orders_below();

/*returns 1 if there is an order above the elevator
else it returns 0*/
int q_has_orders_above();

/*returns 1 if there is an order above the input
else returns 0*/
int q_has_orders_above_with_input(int scanned_floor);

/*returns 1 if there is an order below the input
else returns 0*/
int q_has_orders_below_with_input(int scanned_floor);

/*returns 1 if the elevator should stop on a certain floor
else returns 0*/
int q_should_stop_at_floor(int current_floor);




//Get functions
/*returns 1 if a specific order is 1 otherwise returns 0*/
int q_get_specific_order(int floor, int button);


