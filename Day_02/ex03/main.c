
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200  // Bit rate
#define TIMER1_PRESCALER 256  // Prescaler for Timer1
#define TIMER1_FREQ 1         // Desired frequency (1 Hz)

void uart_tx(char c);
// ISR for UART Receive Complete
ISR(USART_RX_vect)
{    
    if(UDR0 >= 'A' && UDR0 <= 'Z')
        uart_tx(UDR0 + 32);
    else 
        uart_tx(UDR0 - 32);
}

// Function to transmit a character via UART
void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for transmit buffer to be empty
    UDR0 = c;                        // Send the character
}

// Function to initialize UART
void uart_init(void)
{
    unsigned int ubrr;

    ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1); // Calculate baud rate register value
    UBRR0H = ubrr >> 8;                      // Set high byte of baud rate
    UBRR0L = ubrr;  
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);                   // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits, no parity, 1 stop bit
}

int main(void)
{
    SREG = (1 << 7);
    uart_init();  // Initialize UART
    while (1){}
    return 0;
}

