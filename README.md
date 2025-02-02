# State Machine Library (stmachine)

## Overview
This project provides a generic state machine implementation in C, offering a modular and structured approach to defining and handling state transitions. The state machine supports multiple states, transition conditions, and execution methods.

## Features
- **Generic state machine structures**
- **Support for multiple states and transitions**
- **Functions for state entry, execution, and exit**
- **Condition-based transitions**
- **Modular and reusable implementation**
- **Fixed-size state machine with efficient transition handling**

## Files
### 1. `stmachine.h`
Defines the core structures and enumerations for state machine management:
- `stmachine_bool_t`: Boolean type for the state machine.
- `stmachine_method_t`: Enumeration of state machine methods.
- `state_id_t`: Defines the state ID type (supports different integer sizes).
- `transition_t`: Defines a transition type with the next state and the change condition.
- `state_t`: Represents a state with enter, execute, and exit functions, along with transition definitions.
- `stmachine_base_t`: Holds base state machine attributes.
- `stmachine_interface_t`: Defines the available methods for state machine control.
- `stmachine_1_t`: Example state machine with a fixed number of states.

### 2. `stmachine.c`
Implements the state machine logic:
- Defines state transition functions.
- Implements `start`, `stop`, `reset`, and `runnable` methods.
- Handles invalid state cases.
- Implements functions for executing state behavior and evaluating transitions efficiently using a states table.

## How It Works
1. **Initialization**: Define states, transitions using bitmasks, and the state machine structure.
2. **State Execution**: Each state has defined `on_enter`, `on_execute`, and `on_exit` functions.
3. **Transitions**: Each state can transition to different states based on its transitions array.
4. **Handling Invalid States**: A dedicated function handles invalid states.
5. **Running the State Machine**: The `runnable` function checks the current state, executes actions, and evaluates transitions efficiently.

## Usage
1. Define a new state machine structure.
2. Set up states and transitions using arrays.
3. Implement state behavior functions.
4. Use `start`, `stop`, `reset`, and `runnable` methods to control the state machine.

