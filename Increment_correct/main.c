#include <stdint.h>

extern void increment(uint8_t *val);

int main(void) {
	uint8_t value = 10;
	for (uint8_t ctr = 0; ctr < 10; ctr++) {
		increment(&value);
	}
}
