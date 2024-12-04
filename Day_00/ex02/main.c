#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	DDRB |= (1 << 0);
	DDRD &= ~(1 << 2);
	while (1)
	{
		// If the button is pressed PIND2 is a zero
		// Turn on the led 0 PORTB0
		if (!(PIND & (1 << 2)))
			PORTB |= (1 << 0);
		else
			PORTB &= ~(1 << 0);
	}
	return (0);
}
