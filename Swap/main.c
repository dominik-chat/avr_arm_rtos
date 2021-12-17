#include <stdint.h>

extern void swap(uint32_t *p_val_1, uint32_t *p_val_2);

int main(void) {
	uint32_t value_1 = 0x12345678;
	uint32_t value_2 = 0x87654321;

	swap(&value_1, &value_2);
}
