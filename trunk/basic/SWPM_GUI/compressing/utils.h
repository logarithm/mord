#ifndef UTILS_H
#define UTILS_H

#include "types.h"

class Utils {
public:
	static BYTE getBit(int data, int bitIndex) {
		return (BYTE) ((data >> bitIndex) & 0x01);
	}

	static void setBit(int& data, int bitIndex) {
		data |= (0x1 << bitIndex);
	}

	static void clearBit(int& data, int bitIndex) {
		data &= ~(0x1 << bitIndex);
	}
};

#endif // UTILS_H
