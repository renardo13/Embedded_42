#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	int	value;

	value = 0;
	DDRB = (1 << 0);
	DDRB = (1 << 1);
	DDRB = (1 << 2);
	DDRB = (1 << 3);
	DDRD = (0 << 2);
	DDRD = (0 << 4);
	while (1)
	{
		if (!(PIND & (1 << 2)) && value < 15)
		{
			value++;
		}
		if (!(PIND & (1 << 4)) && value >= 0)
		{
			value--;
		}
		if(value & (1 << value))
		// for (int i = 0; i < 4; i++)
		// 	PORTB |= (1 << 0);
		// if (!(PIND & (0 << 2)))
		// 	PORTB = (0 << 0);
	}
	return (0);
}
