#include <stdio.h>
#include "stmachine.h"

#define ITERATIONS  10
uint16_t number = 0;

void stm_handle_nullPtr(stmachine_method_t stm_method) {
    /* Use this callback for null pointer errors */
    switch (stm_method) {
        case STM_START_METHOD:
            {
                /* FILL THIS CASE */
            }
            break;
        case STM_STOP_METHOD:
            {
                /* FILL THIS CASE */
            }
            break;
        case STM_RESET_METHOD:
            {
                /* FILL THIS CASE */
            }
            break;
        case STM_RUNNABLE_METHOD:
            {
                /* FILL THIS CASE */
            }
            break;
        default:
            {
                /* FILL THE INVALID CASE */
            }
            break;
    }
}

/* State Start Functions */
void stm1_state1_on_enter(void) {
    printf("Starting State machine 1: State 1\n");
}

void stm1_state2_on_enter(void) {
    printf("Starting State machine 1: State 2\n");
}

void stm1_state3_on_enter(void) {
    printf("Starting State machine 1: State 3\n");
}

/* State Execution Functions */
void stm1_state1_on_execute(void) {
    printf("Executing State machine 1: State 1\n");
}

void stm1_state2_on_execute(void) {
    printf("Executing State machine 1: State 2\n");
}

void stm1_state3_on_execute(void) {
    printf("Executing State machine 1: State 3\n");
}

/* State Exit Functions */
void stm1_state1_on_exit(void) {
    printf("Exiting State machine 1: State 1\n");
}

void stm1_state2_on_exit(void) {
    printf("Exiting State machine 1: State 2\n");
}

void stm1_state3_on_exit(void) {
    printf("Exiting State machine 1: State 3\n");
}

/* State Transition Functions */
stmachine_bool_t stm1_state1_to_state2(void) {
    stmachine_bool_t condition_flag = FALSE; 

    if (/* INSERT CONDITION */ 0 == number % 2) {
        condition_flag = TRUE; 
    }
    else {
        /* do nothing */
    } 
    return (condition_flag);
}

stmachine_bool_t stm1_state1_to_state3(void) {
    stmachine_bool_t condition_flag = FALSE; 

    if (/* INSERT CONDITION */ 0 == number % 3) {
        condition_flag = TRUE; 
    }
    else {
        /* do nothing */
    } 
    return (condition_flag);
}

stmachine_bool_t stm1_state2_to_state3(void) {
    stmachine_bool_t condition_flag = FALSE; 

    if (/* INSERT CONDITION */ 1 == number % 2) {
        condition_flag = TRUE; 
    }
    else {
        /* do nothing */
    } 
    return (condition_flag);
}

stmachine_bool_t stm1_state3_to_state1(void) {
    stmachine_bool_t condition_flag = FALSE; 

    if (/* INSERT CONDITION */ 0 == number % 2) {
        condition_flag = TRUE; 
    }
    else {
        /* do nothing */
    } 
    return (condition_flag);
}

/* Dummy function to setup invalid transition */
stmachine_bool_t always_false(void) {
    return FALSE;
}

void stm1_start(void* stm) {
    if (STM_NULL_PTR != stm) {
        stmachine_base_t* base = (stmachine_base_t*)(stm);
        (*base).current_state = STM1_STATE_1;
        (*base).stmachine_run_flag = TRUE;
    }
    else {
        /* Handle for null pointer input parameter */
        stm_handle_nullPtr(STM_START_METHOD);
    }
}

void stm1_stop(void* stm) {
    if (STM_NULL_PTR != stm) {
        stmachine_base_t* base = (stmachine_base_t*)(stm);
        (*base).stmachine_run_flag = FALSE; 
    }
    else {
        /* Handle for null pointer input parameter */
        stm_handle_nullPtr(STM_STOP_METHOD);
    }
}

void stm1_reset(void* stm) {
    if (STM_NULL_PTR != stm) {
        stmachine_base_t* base = (stmachine_base_t*)(stm);
        (*base).current_state = STM1_STATE_INVALID;
        (*base).stmachine_run_flag = FALSE;
    }
    else {
        /* Handle for null pointer input parameter */
        stm_handle_nullPtr(STM_RESET_METHOD);        
    }
}

void stm1_runnable(void* stm) {
    if (STM_NULL_PTR != stm) {
        stmachine_1_t* stm1 = (stmachine_1_t*)(stm);

        if (TRUE == stm1->base.stmachine_run_flag) {
            /* Get the current state of the states machine */
            state_id_t current_id = stm1->base.current_state;
            state_t *state = &(stm1->state_table[current_id]);

            /* Execute the routine for the current state */
            if (STM1_STATE_INVALID != current_id) {
                if (STM_NULL_PTR != state->on_execute) {
                    /* Execute the current state routine */
                    state->on_execute();
                } 
                else {
                    /* Handle the null pointer */
                    stm_handle_nullPtr(STM_RUNNABLE_METHOD);
                }
            }
            else {
                /* Handle the invalid state */
                stm1->interface.handle_invalid_state();
            }
            
            /* Check the transitions */
            state_id_t t_cont = 0; 
            
            while (STMACHINE_1_STATES > t_cont) {
                if (STM1_STATE_INVALID != state->transitions[t_cont].next_state) {
                    if (STM_NULL_PTR != state->transitions[t_cont].condition) {
                        if (TRUE == state->transitions[t_cont].condition()) {
                            if (STM_NULL_PTR != state->on_exit) {
                                /* Execute the exit routine for the current state */
                                state->on_exit();        
                            }                            
                            else {
                                /* Handle the null pointer */
                                stm_handle_nullPtr(STM_RUNNABLE_METHOD);
                            }

                            /* Update the states machine status */ 
                            stm1->base.last_state = stm1->base.current_state;
                            stm1->base.current_state = state->transitions[t_cont].next_state;

                            /* Update the current state pointer */
                            state = &(stm1->state_table[stm1->base.current_state]);

                            if (STM_NULL_PTR != state->on_enter) {
                                /* Execute the enter routine for the new current state */
                                state->on_enter();        
                            }                            
                            else {
                                /* Handle the null pointer */
                                stm_handle_nullPtr(STM_RUNNABLE_METHOD);
                            }
                        } 
                        else {
                            /* Do nothing, no transition */
                        }
                    } 
                    else {
                        /* Handle the null pointer */
                        stm_handle_nullPtr(STM_RUNNABLE_METHOD);
                    }
                }
                else {
                    /* Exit the transitions revision */
                    break;
                }
                ++t_cont;
            }
        }
    }
    else {
        /* Handle the null pointer */
        stm_handle_nullPtr(STM_RUNNABLE_METHOD); 
    }

    
}

void stm1_handle_invalid_state() {
    /* Fill with the routine for invalid state */
}

void stm1_init(void* stm) {
    stmachine_1_t* stm1 = (stmachine_1_t*)(stm);
    
    /* State Machine 1 status variables */
    static stmachine_base_t base = {
        .stmachine_run_flag = FALSE,
        .current_state = STM1_STATE_INVALID,
        .last_state = STM1_STATE_INVALID
    };

    /* State Machine 1 methods */
    static stmachine_interface_t interface = {
        .start = stm1_start,
        .stop = stm1_stop,
        .reset = stm1_reset,
        .runnable = stm1_runnable,
        .handle_invalid_state = stm1_handle_invalid_state   
    };

    /* State Machine 1 transitions */
    static transition_t stm1_transitions_state1[] = {
        {STM1_STATE_2, stm1_state1_to_state2},
        {STM1_STATE_3, stm1_state1_to_state3},
        {STM1_STATE_INVALID, always_false}
    };

    static transition_t stm1_transitions_state2[] = {
        {STM1_STATE_3, stm1_state2_to_state3},
        {STM1_STATE_INVALID, always_false}
    };

    static transition_t stm1_transitions_state3[] = {
        {STM1_STATE_1, stm1_state3_to_state1},
        {STM1_STATE_INVALID, always_false}
    };

    /* State Machine 1 states */
    static state_t state_table[STMACHINE_1_STATES] = {
        /* STATE 1 */
        [STM1_STATE_1] = (state_t){
            .on_enter = stm1_state1_on_enter,
            .on_execute = stm1_state1_on_execute,
            .on_exit = stm1_state1_on_exit,
            .transitions = stm1_transitions_state1
        },
        /* STATE 2 */
        [STM1_STATE_2] = (state_t){
            .on_enter = stm1_state2_on_enter,
            .on_execute = stm1_state2_on_execute,
            .on_exit = stm1_state2_on_exit,
            .transitions = stm1_transitions_state2
        },
        /* STATE 3 */
        [STM1_STATE_3] = (state_t){
            .on_enter = stm1_state3_on_enter,
            .on_execute = stm1_state3_on_execute,
            .on_exit = stm1_state3_on_exit,
            .transitions = stm1_transitions_state3 
        }
    };

    /* State Machine 1 initialization */    
    stm1->base = base;     
    stm1->interface = interface; 
    stm1->state_table[STM1_STATE_1] = state_table[STM1_STATE_1];
    stm1->state_table[STM1_STATE_2] = state_table[STM1_STATE_2];
    stm1->state_table[STM1_STATE_3] = state_table[STM1_STATE_3];
}

int main() {
    stmachine_1_t stm1;

    stm1_init(&stm1);
    stm1.interface.start(&stm1);

    for(uint8_t loop_c = 0 ;; ++loop_c) {
        printf("CLK iterator %d : number value %d\n",loop_c, number);
        if (ITERATIONS <= loop_c) {
            stm1.interface.stop(&stm1);
            break;
        }
        stm1.interface.runnable(&stm1); 
        ++number;
        printf("\n");
    }
}
