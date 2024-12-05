#include <avr/io.h>

#define F_CPU 16000000UL

/* First step : Get the frequency of the processor (16MHz).
we have to know the prescalor that we have to use. The prescalor can be 1, 8,
	64, 256, 1024.
Our timer is on 16bits. So the space is memory is 2^16 = 65,536. (Because we are in binary).
So we divide the frequence of the processor by all the prescalor to find a value that fit in the memory range.
We can choose 256 or 1024 for the prescalor. Because 16000000 / 256 is inside the range 0 - 65,536 and the same for 1024.
We choose the bigger one 1024.
Now we can apply the formula to find how many cycle the processor has to make for the timer increment 1 (1 second ?);
Cycles_nb = frequency of the processor / prescalor;
We can now calculate the value of OCR1A. Which is the value until the timer has to count. It will compare the output of the timer
with this value and make an interruption (it can be switch off/on a led) configured by the mode. The formula is :
OCR1A = frequence of the processor / 2 * frequence_desired * prescalor.
*/

int	main(void)
{
	// Need to specifie that the led2 is an output
	DDRB |= 1 << PB1;

	/* TCCR1x are the 8bits registers that controlled the modes of the timer.
	COM1A0 is set at 1 and COM1A1 is implicitely set at 0. "01" mode toggle the OC1A (linked to the led2)*/
	/*  The 2 pins WGM1x serve to activate the mode of the timer,
		the way that it counts.
	ex : 12345 and when it reach the TOP 4321, and so on. Or,
		12345 and after the top, 12345 and so on.
	Here the mode is 1111,
		it is called fast PWM (so it counts 12345 12345...) */
	TCCR1A |= 1 << COM1A0 | 1 << WGM11 | 1 << WGM10;
	TCCR1B |= 1 << WGM13 | 1 << WGM12 | 1 << CS12 | 1 << CS10;

	/*OCR1A is the TOP value: nb of cycle before OC1A increase*/
	/* We know that 1Hz = 1seconde, and that in fast PWM a complete cycle (full on/off cycle) takes 2 periode. So We have to divide by 2 */
	OCR1A = F_CPU / (2 * 1 * 1024);
	while (1)
		;
	return (0);
}
