#include <avr/io.h>

#define F_CPU 16000000UL

ISR (PCINT0_vect)
{

}

int	main(void)
{
	DDRD &= ~(0 << PB2);
	SREG |= (1 << 7);

	EIMSK |= (1 << INT0);

	
	while (1)
		;
	return (0);
}
