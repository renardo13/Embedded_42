#include <avr/io.h>

#define F_CPU 16000000UL

/* First step : Get the frequency of the processor (16MHz).
we have to know the prescalor that we have to use. The prescalor can be 1, 8, 64, 256, 1024. 
Our timer is on 16bits. So the space is memory is 2^16 = 65,536. (Because we are in binary).
So we divide the frequence of the processor by all the prescalor to find a value that fit in the memory range.
We can choose 256 or 1024 for the prescalor. Because 16 000 000 / 256 is inside the range 0 - 65,536 and the same for 1024.
We choose the bigger one 1024.
Now we can apply the formula to find how many cycle the processor has to make for the timer increment 1 (1 second ?);
Cycles_nb = frequency of the processor / prescalor;
We can now calculate the value of OCR1A. Which is the value until the timer has to count. It will compare the output of the timer 
with this value and make an interruption configured by the mode. The formula is :
OCR1A = frequence of the processor / (2 *) frequence_desired * prescalor.






*/

int	main(void)
{
	DDRB |= (1 << PB1);
	 
	TCCR1A = 1 << COM1A0 | 1 << WGM11 | 1 << WGM10;
	/* . . . WGM13 WGM12 CS12 CS11 CS10*/
	TCCR1B = 0b00011101;

	/*TOP value: nb of cycle before OC1A increase*/
	OCR1A = F_CPU / 2 * 2048;
	while (1)
		;
	return (0);
}
