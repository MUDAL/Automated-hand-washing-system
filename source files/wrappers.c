/*
 * wrappers.c
 *
 * Created: 05/01/2021 2:18:22 PM
 *  Author: OLAOLUWA
 */ 
#include <avr/io.h>
#include "wrappers.h"

void ConfigAnalogComparator(void){
	/*
	* Description:
	* Configures the ATtiny13's analog comparator.
	*
	* Parameter:
	* None
	*
	* Returns:
	* None
	*
	*/
	DDRB |=(1<<DDB4); //PB4 as output [soap pump]
	DDRB |=(1<<DDB2); //PB2 as output [water pump]
	ADCSRB &= ~(1<<ACME); //AIN1 as -ve input of comparator (reference voltage)
	ACSR &= ~(1<<ACBG); //AIN0 as +ve input of comparator (connected to an infrared sensor)
	ACSR |= (1<<ACIE)|(1<<ACIS0)|(1<<ACIS1); //Enable interrupt on Analog Comparator Output rising edge
}

void ConfigTimer0(void){
	/*
	* Description:
	* Configures Timer 0 on the ATtiny13.
	*
	* Parameter:
	* None
	*
	* Returns:
	* None
	*
	*/
	TCCR0B |= (1<<CS01); //Prescalar = 8
	TCCR0A |= (1<<WGM01); //CTC mode
	OCR0A = 150; //1ms timer value
	TIMSK0 |= (1<<OCIE0A); //Enable Timer 0 compare match A interrupt
}

void BlockingDelay(uint32_t numberOfIncrements){
	/*
	* Description:
	* Waits for a short time before device restarts operation.
	* It prevents the device from instantly resuming operation when it just finished one. As the device isn't a real-time system, 
	* this doesn't jeopardize its operation but care must be taken with the value of the parameter 'numberOfIncrements'.
	*
	* Parameter:
	* numberOfIncrements -> number of times a dead loop runs in order to create a delay.
	* if numberOfIncrements is too large, the device takes significant time to resume operation
	* if numberOfIncrements is too small, the device instantly resumes operation (if the user hasn't removed his/her palm)
	* thinking the user wants to wash his/her palm.
	*
	* Trial and error can be used to obtain a considerable value or a better delay() routine can be written.
	*
	* Returns:
	* None
	*
	*/
	volatile uint32_t waitingTime = 0;
	while (waitingTime < numberOfIncrements){
		waitingTime++;
	}
}

void StartSoapPump(void){
	/*
	* Description:
	* Starts the pump for dispensing soap
	*
	* Parameter:
	* None
	*
	* Returns:
	* None
	*
	*/
	PORTB |= (1<<PORTB4); 
}

void StopSoapPump(void){
	/*
	* Description:
	* Stops the pump for dispensing soap
	*
	* Parameter:
	* None
	*
	* Returns:
	* None
	*
	*/
	PORTB &= ~(1<<PORTB4); 
}

void StartWaterPump(void){
	/*
	* Description:
	* Starts the pump for dispensing water
	*
	* Parameter:
	* None
	*
	* Returns:
	* None
	*
	*/
	PORTB |= (1<<PORTB2); 
}

void StopWaterPump(void){
	/*
	* Description:
	* Stops the pump for dispensing water
	*
	* Parameter:
	* None
	*
	* Returns:
	* None
	*
	*/
	PORTB &= ~(1<<PORTB2); 
}
