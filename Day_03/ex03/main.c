#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int		ft_atoi_base(const char *str, char *base);

#define BLUE 3
#define RED 5
#define GREEN 6

#define UART_BAUDRATE 115200
#define F_CPU 16000000

void	set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	// Use OCRxx to set the match value to know how many time you have to let the led turn on (which give a sort of intensity)
	OCR0B = r; // Value for red LED (OCR0B controls red)
	OCR0A = g; // Value for green LED (OCR0A controls green)
	OCR2B = b; // Value for blue LED (OCR2B controls blue)
}

// Function to initialize the PWM for RGB LEDs
void	init_rgb(void)
{
	// Configure the pins as output
	DDRD |= (1 << GREEN) | (1 << RED) | (1 << BLUE); // Green and Red on PORTD
	// Configure Timer0 (for red and green LEDs)
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
	// Clear OC0A/OC0B on compare match (PWM mode)
	TCCR0A |= (1 << WGM01) | (1 << WGM00); // Fast PWM mode for Timer0
	TCCR0B |= (1 << CS02) | (1 << CS00);   // Prescaler = 1024 for Timer0
	// Configure Timer2 (for blue LED)
	TCCR2A |= (1 << COM2B1);
	// Clear OC2B on compare match (PWM mode)
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	// Fast PWM mode for Timer2
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
	// Prescaler = 1024 for Timer2
}

void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;     // Wait for transmit buffer to be empty
	UDR0 = c; // Send the character
}

char	uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		;          // transmission register
	return (UDR0); // Return the character
}

// Function to initialize UART
void	uart_init(void)
{
	unsigned int	ubrr;

	ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1);
	// Calculate baud rate register value
	UBRR0H = ubrr >> 8;
	// Set high byte of baud rate
	UBRR0L = ubrr;
	// Set low byte of baud rate
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	// Set frame format: 8 data bits,
	// no parity,
	// 1 stop bit
}
void	uart_printstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		uart_tx(str[i++]);
	}
}
void	get_color(char *color)
{
	char	c;

    int i = 0;
	while (i < 2)
	{
		c = uart_rx();
		uart_tx(c);
		if (c == 127 && i > 0)
		{
			color[--i] = '\0';
			uart_printstr("\b \b");
		}
		else if(c != '#')
			color[i++] = c;
	}
	color[2] = '\0';
}

int	main(void)
{
	char	r[2];
	char	g[2];
	char	b[2];

	init_rgb();
	uart_init();
	while (1)
	{
		get_color(r);
		get_color(g);
		get_color(b);
		uart_printstr("\r\n");
		set_rgb(ft_atoi_base(r, "123456789ABCDEF"), ft_atoi_base(g,
				"123456789ABCDEF"), ft_atoi_base(b, "123456789ABCDEF"));
	}
	return (0);
}
