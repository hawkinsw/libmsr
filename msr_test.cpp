#include "msr.hpp"
#include <assert.h>
#include <iostream>
#include <bitset>

int main() {
	Msr msr;
	uint64_t result = 0;
	std::bitset<8*sizeof(uint64_t)> result_bits;
	assert(msr.Read(0x10, result, 0) == 0);
	std::cout << "TSC: 0x" << std::hex << result << std::endl;

	assert(msr.Read(0x38F, result, 0) == 0);
	/*
	std::cout << "MSR_CORE_PERF_GLOBAL_CTRL: 0x";

	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	for (int i = (8*sizeof(uint64_t))-1; i>=0; i--) {
		std::cout << result_bits[i];
		if (!(i%8))
			std::cout << "-"; 
	}
	std::cout << std::endl;
	*/
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "MSR_CORE_PERF_GLOBAL_CTRL: 0x" << result_bits << std::endl;

	result = 0x70000000f;
	//result = 0x0;
	assert(msr.Write(0x38F, result, 0) == 0);
	assert(msr.Read(0x38F, result, 0) == 0);
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "MSR_CORE_PERF_GLOBAL_CTRL: 0x" << result_bits << std::endl;
	return 0;
}
