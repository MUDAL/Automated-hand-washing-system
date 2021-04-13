/*
 * AutoWash.c
 *
 * Created: 17/06/2020 3:20:00 PM
 *  Author: OLAOLUWA
 *
 * FIRMWARE FOR AUTOMATED HAND WASHING SYSTEM
 */ 

/*
NB: Default clock source = 1.2MHz (9.6MHz internal oscillator with prescaler = 8)
This project is an automated hand washing system.

Principle of operation:
The user's hands are brought close to an infrared sensor, the microcontroller activates a pump to supply
water for 5 seconds. After 20 seconds, the microcontroller triggers another pump to supply water indefinitely till the 
user is satisfied with how much water they've used to wash their hands. To stop the flow of water, the user gets his/her 
palms close to the infrared sensor again.

*/

#define F_CPU 1200000U
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "APIs.h"

volatile uint8_t hands_close = 0;
volatile uint8_t soapy_hands = 0;
volatile uint8_t start_count = 0;
volatile uint16_t counter = 0;


int main(void)
{
	
	cli(); //disable all interrupts
	ConfigAnalogComparator();
	ConfigTimer0();
	sei(); //enable interrupts
	
	while(1){
		
		if (!soapy_hands){
			if (hands_close && counter == 0){
				StartSoapPump();
				start_count = 1;
				hands_close = 0;
			}
		}
		else{
			if(hands_close){
				StopWaterPump();
				BlockingDelay(120000); 
				soapy_hands = 0;
				counter = 0;
				hands_close = 0;
			}
		}		
	}
}


ISR(ANA_COMP_vect){
	/*
	* Description:
	* Interrupt handler for ATtiny13's analog comparator.
	* This ISR is called once AIN0 > AIN1 (an event that occurs when the 
	* hands are close to the infrared sensor).
	* 
	* The Proteus simulation uses a potentiometer in place of the IR sensor
	*
	*/
	if (counter == 0 || counter == 25000) hands_close = 1;
}

ISR(TIM0_COMPA_vect){
	/*
	* Description:
	* Interrupt handler for ATtiny13's Timer 0.
	* This ISR is called every millisecond based on the Timer 0 configurations
	* made in ConfigTimer0().
	* 
	* It increments a variable which is used as a reference for timing the device's
	* operation.
	*
	*/
	
	if (start_count){
		counter++;
		if (counter == 5000) {
			StopSoapPump();
		}
		if (counter == 25000){
			StartWaterPump();
			soapy_hands = 1;
			start_count = 0;
		}
	}
}




