/**
 * @file elevator.c
 * @brief Elevator system with states for movement and door control.
 */

#include <stdbool.h>

/**
 * @brief Possible states of the elevator.
 */
typedef enum {
    STATE_IDLE,     /**< Elevator is idle. */
    STATE_MOVING_UP,/**< Elevator is moving up. */
    STATE_MOVING_DOWN /**< Elevator is moving down. */
} ElevatorState;

/**
 * @brief Possible door states.
 */
typedef enum {
    DOOR_OPEN,  /**< Door is open. */
    DOOR_CLOSED /**< Door is closed. */
} DoorState;

/**
 * @brief Elevator state variables.
 */
typedef struct {
    int currentFloor;     /**< Current floor of the elevator. */
    int targetFloor;      /**< Target floor for the elevator. */
    ElevatorState state;  /**< Current state of the elevator. */
    DoorState doorState;  /**< Current state of the door. */
} Elevator;

/**
 * @brief Initializes the elevator.
 * @param elevator Pointer to the elevator state.
 */
void initElevator(Elevator *elevator) {
    elevator->currentFloor = 1;
    elevator->targetFloor = 1;
    elevator->state = STATE_IDLE;
    elevator->doorState = DOOR_CLOSED;
}

/**
 * @brief Sets the target floor and closes the door.
 * @param elevator Pointer to the elevator state.
 * @param floor Target floor (must be valid).
 */
void setTargetFloor(Elevator *elevator, int floor) {
    if (floor >= 1 && floor <= 10 && floor != elevator->currentFloor) {
        elevator->targetFloor = floor;
        elevator->state = (floor > elevator->currentFloor) ? STATE_MOVING_UP : STATE_MOVING_DOWN;
        elevator->doorState = DOOR_CLOSED;
    }
}

/**
 * @brief Moves the elevator up by one floor.
 * @param elevator Pointer to the elevator state.
 */
void moveUp(Elevator *elevator) {
    if (elevator->state == STATE_MOVING_UP && elevator->currentFloor < elevator->targetFloor) {
        elevator->currentFloor++;
        if (elevator->currentFloor == elevator->targetFloor) {
            elevator->state = STATE_IDLE;
            elevator->doorState = DOOR_OPEN;
        }
    }
}

/**
 * @brief Moves the elevator down by one floor.
 * @param elevator Pointer to the elevator state.
 */
void moveDown(Elevator *elevator) {
    if (elevator->state == STATE_MOVING_DOWN && elevator->currentFloor > elevator->targetFloor) {
        elevator->currentFloor--;
        if (elevator->currentFloor == elevator->targetFloor) {
            elevator->state = STATE_IDLE;
            elevator->doorState = DOOR_OPEN;
        }
    }
}

/**
 * @brief Keeps the elevator idle with the door closed.
 * @param elevator Pointer to the elevator state.
 */
void idleElevator(Elevator *elevator) {
    if (elevator->currentFloor == elevator->targetFloor) {
        elevator->state = STATE_IDLE;
        elevator->doorState = DOOR_CLOSED;
    }
}

