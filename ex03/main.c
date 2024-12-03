#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	DDRB = (1 << 0);
	DDRD = (0 << 2);
	while (1)
	{
		if (!(PIND & (1 << 2)))                     // Si le bouton est pressé (PD2 à 0)
			PORTB |= (1 << 0); // Allume la LED (PB0 à 1)
		if (!(PIND & (0 << 2)))
			PORTB = (0 << 0); // Éteint la LED (PB0 à 0)
	}
	return (0);
}
