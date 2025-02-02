#ifndef STMACHINE_H
#define STMACHINE_H
#include <stdint.h> 

#define STM_NULL_PTR    (void*)(NULL)

typedef enum stmachine_boolean {
    FALSE = 0,
    TRUE
} stmachine_bool_t;

typedef enum stmachine_method {
    STM_START_METHOD = 0,
    STM_STOP_METHOD,
    STM_RESET_METHOD,
    STM_RUNNABLE_METHOD,
    STM_METHOD_INVALID
} stmachine_method_t;

/* Type definition for states id
 * Possibles data types: 
 * int8_t:  for state machines with 255 or less states
 * int16_t: for state machines with 65535 or less states 
 * int32_t: for state machines with 4294967295 or less states  
 */
typedef uint8_t state_id_t; 

/* Generic structures for all the state machines */

typedef struct transition {
    state_id_t next_state; 
    stmachine_bool_t (*condition)(void);
} transition_t;

typedef struct state {
    void (*on_enter)(void);
    void (*on_execute)(void);
    void (*on_exit)(void);
    transition_t *transitions;
} state_t;

typedef struct stmachine_base {
    stmachine_bool_t stmachine_run_flag;
    state_id_t current_state; 
    state_id_t last_state;
} stmachine_base_t;

typedef struct stmachine_interface {
    void (*start)(void *);    
    void (*stop)(void *);     
    void (*reset)(void *);    
    void (*runnable)(void *); 
    void (*handle_invalid_state)(void);
} stmachine_interface_t;

/* END OF GENERIC STRUCTURES */

#define STMACHINE_1_STATES  3

#define STM1_STATE_1        0
#define STM1_STATE_2        1
#define STM1_STATE_3        2
#define STM1_STATE_INVALID  3

typedef struct stmachine_1 {
    stmachine_base_t base;
    stmachine_interface_t interface;
    state_t state_table[STMACHINE_1_STATES];
} stmachine_1_t;

#endif /* STMACHINE_H */
