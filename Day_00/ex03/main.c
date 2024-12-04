#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	int	flag;

	flag = 0;
	DDRB |= (1 << 0);
	DDRD &= ~(1 << 2);
	while (1)
	{
		if (!(PIND & (1 << 2)))
		{
			if (flag)
				flag = 0;
			else
				flag = 1;
			while (!(PIND & (1 << 2)))
				;
		}
		if (flag)
			PORTB |= (1 << 0); // Allume la LED (PB0 à 1)
		else
			PORTB &= ~(1 << 0);
		_delay_ms(20);
	}
	return (0);
}
