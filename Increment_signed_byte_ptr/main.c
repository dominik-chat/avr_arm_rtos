#include <stdint.h>

extern void inc(int8_t *val);

int main(void) {
	int8_t value = -10;

	inc(&value);
}
