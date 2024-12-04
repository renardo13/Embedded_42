#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	int	value;

	value = 0;
	DDRB |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 4); //0b00010111
	// DDRB |= (1 << 0);
	// DDRB |= (1 << 1);
	// DDRB |= (1 << 2);
	// DDRB |= (1 << 4);
	DDRD &= ~((1 << 2) | (1 << 4));
	//DDRD &= ~(1 << 4);
	while (1)
	{
		if (!(PIND & (1 << 2)) && value < 15)
		{
			value++;
			_delay_ms(1000);
		}
		if (!(PIND & (1 << 4)) && value > 0)
		{
			value--;
			_delay_ms(1000);
		}
		/* All the bits of PORTB represent the leds,
			one bit one led. So we can controlled all the led together
		only with the value of PORTB. We compared the bits of value with 15 who is 1111 in binary.
		Considere that the 4 firs bit are zero. (a decimal value is represented with 8 bits).
		Thanks to that we will isolate the 4 bits of the end and not the 4 bit of the beginning
		which correspond to nothing in our port b with the operator & (and).
		So the bits of value which are at 1 will be one in PORTB so the led will be turn on. */
		PORTB = (value & 8) << 1 | (value & 7); 
		_delay_ms(1000);
	}
	return (0);
}
