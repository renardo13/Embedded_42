#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#define BLUE 3
#define RED 5
#define GREEN 6

/*
    - Look at the board diagrams to see where the pins are and what they are connected to.
    - Specifically search for the modes we want (use tables to help);
    - Make a list of the pins we need to activate.
    - Find the registers for the pins, set them to 1.
    -> For the timers, we need to configure how the timer interrupt is interpreted, the counting mode (PWM, etc.), the prescaler, and the output compare value.
*/

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    // Use OCRxx to set the match value to know how many time you have to let the led turn on (which give a sort of intensity)
    OCR0B = r;  // Value for red LED (OCR0B controls red)
    OCR0A = g;  // Value for green LED (OCR0A controls green)
    OCR2B = b;  // Value for blue LED (OCR2B controls blue)
}

// Function to initialize the PWM for RGB LEDs
void init_rgb()
{
    // Configure the pins as output
    DDRD |= (1 << GREEN) | (1 << RED) | (1 << BLUE);  // Green and Red on PORTD

    // Configure Timer0 (for red and green LEDs)
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);  // Clear OC0A/OC0B on compare match (PWM mode)
    TCCR0A |= (1 << WGM01) | (1 << WGM00);    // Fast PWM mode for Timer0
    TCCR0B |= (1 << CS02) | (1 << CS00);      // Prescaler = 1024 for Timer0

    // Configure Timer2 (for blue LED)
    TCCR2A |= (1 << COM2B1);   // Clear OC2B on compare match (PWM mode)
    TCCR2A |= (1 << WGM21) | (1 << WGM20);  // Fast PWM mode for Timer2
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  // Prescaler = 1024 for Timer2
}

// Function to create a smooth color transition (RGB wheel effect)
void wheel(uint8_t pos)
{
    pos = 255 - pos;  // Reverse position for color progression
    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);  // Red to Blue transition
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);  // Blue to Green transition
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);  // Green to Red transition
    }
}

int main(void)
{
    init_rgb();  // Initialize timers and pins for RGB LEDs

    // Loop to cycle through colors with smooth transitions and set the compare match values
    for (uint8_t pos = 0; pos < 256; pos++)
    {
        wheel(pos);   
        _delay_ms(100);
    }
    while (1){
    }
}
