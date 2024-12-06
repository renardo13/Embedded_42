

#include <avr/interrupt.h>
#include <avr/io.h>

#define TIMER1_PRESCALER 1024
#define F_CPU 16000000UL

#define BLUE 3
#define RED 5
#define GREEN 6

ISR(TIMER1_COMPA_vect)
{
	static uint8_t	rgb_color = RED;

	PORTD = 0;
	PORTD |= 1 << rgb_color;
	if (rgb_color == GREEN)
		rgb_color = BLUE;
	else if (rgb_color == BLUE)
		rgb_color = RED;
	else if (rgb_color == RED)
		rgb_color = GREEN;
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

// void set_timer1()
// {
//     TCCR2A |= 1 << COM2B0; /* Toggle OC2B on compare match */
//     TCCR2B = 1 << CS22 | 1 << CS21;

//     TCCR0A |= 1 << COM0B1 | 1 << COM0B0 | 1 << WGM01 | 1 << WGM00;
/* Toggle OC0A and OC0B on compare match */
//     /* WGM pins are configured to be in counting mode FAST PWM */
//     /* Prescalor of 1024 with CS0x for the A*/
//     TCCR0B |= 1 << WGM02 | 1 << CS02;

//     /* PD3 work with OC2B value to compare match
//     PD5 with OC0B
//     PD6 with OC0A */
//     OCR2B = F_CPU / (2 * 1 * 1024);
//     OCR0B = F_CPU / (2 * 1 * 1024);
//     OCR0A = F_CPU / (2 * 1 * 1024);
// }

// int main(void)
// {
//     // PD3 -> Blue ; PD5 -> red ; PD6 -> Green
//     DDRD |= 1 << PD3 | 1 << PD5 | 1 << PD6;

//     // PORTD ^= 1 << PD3;
//     // PORTD ^= 1 << PD5;
//     // PORTD ^= 1 << PD6;
//     while (1)
//     {

//     }
//     return (0);
// }
