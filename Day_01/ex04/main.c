#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int	main(void)
{
	// Set led D2 to output and turn it off
	DDRB |= (1 << PB1);
	PORTB &= ~(1 << PB1);

	// Set button SW1 & SW2 to input
	DDRD &= ~((1 << PD2) | (1 << PD4));

	// Configure the timer registers TCCR1A & TCCR1B
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << CS10) | (1 << CS12);

	// Set Top for timer cycle
	/*the result of F_CPU / (2 * 1 * 1024) is 7812, and we have to
	start with a multiple of 10 if we want to work out exactly and
	avoid the round of the division that provoque a loose of information
	for these reason we had minus 2 at the calcul of ICR1*/
	ICR1 = F_CPU / (2 * 1 * 1024) - 2;

	// Set OCR1A to variable percentage to control the duty cycle
	OCR1A = ICR1 / 10;

	int value = OCR1A;

	// Infinite loop to control the incrementation of OCR1A with the switches
	while (1)
	{
		if (!(PIND & (1 << PD2)) && OCR1A < ICR1)
		{
			OCR1A += value;
			while (!(PIND & (1 << PD2)))
				;
		}
		if (!(PIND & (1 << PD4)) && OCR1A > value)
		{
			OCR1A -= value;
			while (!(PIND & (1 << PD4)))
				;
		}
		_delay_ms(1000);
	}
}
