#include <avr/io.h>

void binary_counter(uint64_t ms)
{
	for(uint64_t i = 0; i < ms; i++);
}

int main (void)
{
	DDRB |= (1 << 1);
	while(1)
	{
		binary_counter(80000);
		PORTB ^= (1 << 1);
	}
	return(0);
}
