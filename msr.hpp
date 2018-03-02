#ifndef __MSR_HPP_
#define __MSR_HPP_

#include <cstdint>
#include <unistd.h>
#include <fcntl.h>

class Msr {
	public:
		Msr() {};

		int Read(unsigned int reg, uint64_t &value, int cpu=0);
		int Write(unsigned int reg, uint64_t value, int cpu=0);
	private:
};

#endif
