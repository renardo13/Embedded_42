#include <avr/io.h>

# define F_CPU 16000000UL

/* DAY01 EX02 */
/* TCCR: TIMER/COUNTER CONTROL REGISTER
* COMAx's defines OCx behaviour: OC1A switches on TOP
* WGMx defines which top value to use: 14
* CSx defines the clock prescaler  clkio/1024 */
int	main(void)
{
	DDRB |= 1 << PB1;	//Set led D2 as output

	/* We have to set COM1A1 at 1, the mode is "the Clear OC1A on Compare Match (Set output to low level)".
	We have to use the mode "PWM, Phase correct" mode 10, */
	TCCR1A |= 1 << COM1A1 | 1 << WGM11;
	/*Always the same prescalor with CS10 and CS12*/
	TCCR1B |=  1 << WGM13 | 1 << CS10 | 1 << CS12;
	/*TOP value is ICR1 in this mode, this is the nb of cycle before OC1A increase*/
	ICR1 = F_CPU / (2 * 1 * 1024); //F_CPU / (2 * desired_frequence * prescaler)
	OCR1A = ICR1 / 10;
	while (1){}
}

