#include <stdio.h>

typedef enum {
    STATE_INIT = 0u,
    STATE_IDLE,
    STATE_RUNNING,
    STATE_LOW_POWER
} t_state;

typedef enum {
	NO_EVENT_RECEIVED = 0u,
    INIT_RECEIVED,
    IDLE_RECEIVED,
	START_RECEIVED,
    LOW_POWER_RECEIVED
} t_event;

static t_state current_state = STATE_INIT;

// Function to print the current state
static void printf_current_state(void) 
{
	switch (current_state) {
		case STATE_IDLE:
			printf("Idle...\n");
			break;
		
		case STATE_RUNNING:
			printf("Running...\n");
			break;
		
		case STATE_LOW_POWER:
			printf("Low Power...\n");
			break;
		default:
			// Do nothing.
			break;
	}
}

// Function to get input event
static t_event get_event() 
{
    char input_char;
	t_event ret = NO_EVENT_RECEIVED;
	
	printf_current_state();
	
    printf("Enter a character (i for idle, l for low power, r for start): ");
    scanf(" %c", &input_char);
    switch (input_char) {
        case 'i':
            ret = IDLE_RECEIVED;
			break;
		case 'r':
            ret= START_RECEIVED;
			break;
        case 'l':
            ret = LOW_POWER_RECEIVED;
			break;
        default:
            // Do nothing
			break;
    }
	
	return ret;
}

// Function to handle init state
static void state_init(void) 
{
	printf("Initializing...\n");
	current_state = STATE_IDLE;
}

// Function to handle idle state
static void state_idle(const t_event event) 
{
    // check for input to transition to running state
    if (event == START_RECEIVED) {
		current_state = STATE_RUNNING;
	} else if(event == LOW_POWER_RECEIVED) {
		current_state = STATE_LOW_POWER;
	} else if ((event == IDLE_RECEIVED) || (event == NO_EVENT_RECEIVED)) {
		// Do nothing.
	} else {
		printf("Invalid transition from STATE_IDLE\n");
	}
}

// Function to handle running state
static void state_running(const t_event event) 
{
    // check for input to transition to stopped state
    if (event == LOW_POWER_RECEIVED) {
		current_state = STATE_LOW_POWER;
	} else if(event == IDLE_RECEIVED) {
		current_state = STATE_IDLE;
	} else if ((event == START_RECEIVED) || (event == NO_EVENT_RECEIVED)) {
		// Do nothing.
	} else {
		printf("Invalid transition from STATE_RUNNING\n");
	}
}

// Function to handle low power state
static void state_low_power(const t_event event) {
    // check for input to transition to running state
    if (event == START_RECEIVED) {
		current_state = STATE_RUNNING;
	} else if ((event == LOW_POWER_RECEIVED) || (event == NO_EVENT_RECEIVED)) {
		// Do nothing.
	} else {
		printf("Invalid transition from STATE_LOW_POWER\n");
	}
}

// Function to handle the state machine
static void state_machine() 
{	
	const t_event event = get_event();
	
    switch (current_state) {
        case STATE_IDLE:
            state_idle(event);
            break;
        case STATE_RUNNING:
            state_running(event);
            break;
        case STATE_LOW_POWER:
            state_low_power(event);
            break;
    }
}

// Main function
int main() 
{
	state_init();

    while (1) {
        state_machine();
    }
    return 0;
}