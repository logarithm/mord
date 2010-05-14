#ifndef UTILS_H
#define UTILS_H

#include "types.h"

BYTE getBit(int data, int bitIndex) {
	return (BYTE) ((data >> bitIndex) & 0x01);
}

void setBit(int& data, int bitIndex) {
	data |= (0x1 << bitIndex);
}

void clearBit(int& data, int bitIndex) {
	data &= ~(0x1 << bitIndex);
}

#endif // UTILS_H
