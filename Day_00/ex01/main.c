#include <avr/io.h>

/* There are 3 registers to configure the state of the port :

	x -> The number of the port

	DDRx : Confugure if a pin is an output or an input
	PORTx : Configure the state of the pin
	PINx : Get the state of a pin

*/
int	main(void)
{
	// Configure bit 0 (In this case the led 0) of port B as an output
	DDRB |= (1 << 0);
	while (1)
	{
		// Set bit 0 of port B to high (turn on connected led)
		PORTB |= (1 << 0);
	}
	return (0);
}
