
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200  // Bit rate
#define TIMER1_PRESCALER 1024  // Prescaler for Timer1
#define TIMER1_FREQ 0.5      // Desired frequency (1 Hz)

// Function to transmit a character via UART
void uart_tx(char c)
{

    while (!(UCSR0A & (1 << UDRE0))); // Wait for transmit buffer to be empty
    UDR0 = c;           // Send the character
}

char uart_rx()
{
    while (!(UCSR0A & (1 << RXC0))); // transmission register
    return(UDR0);           // Return the character
}

// Function to initialize UART
void uart_init(void)
{
    unsigned int ubrr;

    ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1); // Calculate baud rate register value
    UBRR0H = ubrr >> 8;                      // Set high byte of baud rate
    UBRR0L = ubrr;                           // Set low byte of baud rate
    UCSR0B = (1 << TXEN0)| (1 << RXEN0);                   // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits, no parity, 1 stop bit
}


int main(void)
{
    uart_init();  // Initialize UART
    while (1)
    {
        char c = uart_rx(); // Receive a character
        uart_tx(c);         // Transmit the received character back
    }
    return 0;
}

