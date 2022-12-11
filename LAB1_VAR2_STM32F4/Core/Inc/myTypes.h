/*
 * myTypes.h
 *
 *  Created on: Oct 19, 2022
 *      Author: shoko
 */

#ifndef INC_MYTYPES_H_
#define INC_MYTYPES_H_


typedef enum
{
	light,
	change_combination
} 	ledsStates_t;

typedef enum
{
	notpressed,
	pressed
}	buttonStates_t;

typedef enum
{
	wait,
	antibounce
} 	buttonAntibounceStates_t;

typedef enum
{
	terminal_wait,
	resiving,
	transmiting
} 	TerminalStates_t;

typedef struct
{
	unsigned previous_state 			 :1;
	unsigned current_state   			 :1;
}	buttonPinState_t;

typedef struct
{
	unsigned button_action  		 	 :1;
	unsigned terminal_action			 :1;
} 	globalFlags_t;

typedef struct
{
	unsigned rising_edge  		 	 	 :1;
	unsigned falling_edge      			 :1;
} 	buttonAntibounceFlags_t;

typedef struct
{
	unsigned pushed  		 	 		 :1;
	unsigned released        			 :1;
} 	buttonFlags_t;

typedef struct
{
	unsigned RX_data 		 	 	 :1;
	unsigned TX_data 		 	 	 :1;
} 	TerminalFlag_t;
#endif /* INC_MYTYPES_H_ */
