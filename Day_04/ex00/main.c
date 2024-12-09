#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

ISR(INT0_vect)
{
	
	PORTB ^= (1 << PB1);
}

int	main(void)
{
	DDRD &= ~(1 << PB2);
	DDRB |= (1 << PB1);
	PORTB |= (0 << PB1);
	SREG |= (1 << 7);

	EIMSK |= (1 << INT0);

	
	while (1)
	{
	}
	return (0);
}
