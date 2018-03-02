#include <stdint.h>

uint8_t toto;

void essai(uint8_t val)
{
	toto += val;
}

void main(void)
{
	toto = 0x42;
	essai(5);
	while(1) {};
}
