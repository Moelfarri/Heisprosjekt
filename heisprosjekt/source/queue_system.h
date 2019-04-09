#pragma once
#define N_BUTTONS 3

static int queue_matrix[N_FLOORS][N_BUTTONS] = {};


extern int scanned_floor;

//add and remove matrix functions
void q_add_order();
void q_remove_order();
void q_clear_all_orders();

//Check functions
int q_has_order();
int q_has_orders_below();
int q_has_orders_above();
int q_has_orders_above_with_input(int scanned_floor);
int q_has_orders_below_with_input(int scanned_floor);
int q_should_stop_at_floor(int current_floor);


//Get functions
int q_get_specific_order(int floor, int button);


