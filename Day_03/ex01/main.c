

#include <avr/interrupt.h>
#include <avr/io.h>

#define TIMER1_PRESCALER 1024
#define F_CPU 16000000UL

#define BLUE 3
#define RED 5
#define GREEN 6

ISR(TIMER1_COMPA_vect)
{
	int	red[7] = {1, 0, 0, 1, 0, 1, 1};
	int	green[7] = {0, 1, 0, 1, 1, 0, 1};
	int	blue[7] = {0, 0, 1, 0, 1, 1, 1};
	static uint8_t	i = 0;

	if (i == 7)
		i = 0;
	PORTD = 0;
	PORTD |= (red[i] << RED);
	PORTD |= (green[i] << GREEN);
	PORTD |= (blue[i] << BLUE);
	i++;
}

int	main(void)
{
	SREG |= (1 << 7); // uthorize the global interrupt
	DDRD |= (1 << PD6) | (1 << PD5) | (1 << PD3);
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = F_CPU / TIMER1_PRESCALER;
	while (1)
		;
}
