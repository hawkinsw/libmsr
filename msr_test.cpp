#include "msr.hpp"
#include <assert.h>
#include <iostream>
#include <bitset>

/*
 * Put dashes after every 8 bits in the bit set.
 */
std::ostream &operator<<(std::ostream &os, std::bitset<8*sizeof(uint64_t)> bits)
{
	for (int i = (8*sizeof(uint64_t))-1; i>=0; i--) {
		os << bits[i];
		if (!(i%8))
			os << "-";
	}
	os << std::endl;
	return os;
}

int main()
{
	Msr msr;
	uint64_t result = 0;
	std::bitset<8*sizeof(uint64_t)> result_bits;

	/*
	 * Read the TSC and print it.
	 */
	assert(msr.Read(MSR::MSR_IA32_TIME_STAMP_COUNTER, result, 0) == 0);
	std::cout << "TSC: 0x" << std::hex << result << std::endl;

	/*
	 * Read the global performance counter control register.
	 */
	assert(msr.Read(MSR::MSR_CORE_PERF_GLOBAL_CTRL, result, 0) == 0);
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "MSR_CORE_PERF_GLOBAL_CTRL: 0x" << result_bits << std::endl;

	/*
	 * Write to the global performance counter control register.
	 */
	result = 0x70000000f;
	assert(msr.Write(MSR::MSR_CORE_PERF_GLOBAL_CTRL, result, 0) == 0);

	/*
	 * Read from the global performance counter control register
	 * to verify that the write worked properly.
	 */
	assert(msr.Read(MSR::MSR_CORE_PERF_GLOBAL_CTRL, result, 0) == 0);
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "MSR_CORE_PERF_GLOBAL_CTRL: 0x" << result_bits << std::endl;

	assert(msr.Read(MSR::MSR_IA32_PERFEVTSEL0, result, 0) == 0);
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "MSR_IA32_PERFEVTSEL0: 0x" << result_bits << std::endl;

	result = MSR::EVT_BR_MISP_RETIRED |
	         MSR::MASK_BR_MISP_RETIRED_ALL |
	         MSR::EVENT_ENABLE |
	         MSR::EVENT_USER_ENABLE;
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "Result: 0x" << result_bits << std::endl;

	assert(msr.Write(MSR::MSR_IA32_PERFEVTSEL0, result, 0) == 0);
	assert(msr.Read(MSR::MSR_IA32_PERFEVTSEL0, result, 0) == 0);
	result_bits = std::bitset<8*sizeof(uint64_t)>(result);
	std::cout << "MSR_IA32_PERFEVTSEL0: 0x" << result_bits << std::endl;
	return 0;
}
