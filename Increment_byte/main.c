#include <stdint.h>

extern uint8_t inc(uint8_t val);

int main(void) {
	volatile uint8_t value = 10;

	value = inc(value);
}
