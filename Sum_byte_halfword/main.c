#include <stdint.h>

extern uint16_t sum(uint16_t arg_u16, uint8_t arg_u8);

int main(void) {
	uint16_t arg_u16 = 0xFF01;
	uint8_t arg_u8 = 0x0E;

	volatile uint16_t result = sum(arg_u16, arg_u8);
}
