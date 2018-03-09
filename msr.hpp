#ifndef __MSR_HPP_
#define __MSR_HPP_

#include <cstdint>
#include <unistd.h>
#include <fcntl.h>

namespace MSR {
	enum {
		MSR_IA32_TIME_STAMP_COUNTER = 0x10,
		MSR_CORE_PERF_GLOBAL_CTRL = 0x38F,
		MSR_IA32_PMC0 = 0xC1,
		MSR_IA32_PMC1 = 0xC2,
		MSR_IA32_PMC2 = 0xC3,
		MSR_IA32_PMC3 = 0xC4,
		/*
		 * 0-7: Event select - choose which unit to monitor
		 * 8-15: Mask - choose which of the unit's stats to monitor
		 * 16: User mode monitoring
		 * 17: Privilege mode monitoring
		 * 22: Enable/Disable
		 */
		MSR_IA32_PERFEVTSEL0 = 0x186,
		MSR_IA32_PERFEVTSEL1 = 0x187,
		MSR_IA32_PERFEVTSEL2 = 0x188,
		MSR_IA32_PERFEVTSEL3 = 0x189,
		MSR_IA32_PERFEVTSEL4 = 0x18A,
		MSR_IA32_PERFEVTSEL5 = 0x18B,
		MSR_IA32_PERFEVTSEL6 = 0x18C,
		MSR_IA32_PERFEVTSEL7 = 0x18D
	};

	enum {
		PERF_EVTSEL0_ENABLE = 0x1,
		PERF_EVTSEL1_ENABLE = 0x2,
		PERF_EVTSEL2_ENABLE = 0x4,
		PERF_EVTSEL3_ENABLE = 0x8,
	};
	enum {
		EVT_BR_INST_RETIRED = 0xC4,
		EVT_BR_MISP_RETIRED = 0xC5,
		EVT_BR_INST_EXEC = 0x88,
		EVT_BR_MISP_EXEC = 0x89,
	};
	enum {
		MASK_BR_INST_RETIRED_ALL = 0x00<<8,
		MASK_BR_MISP_RETIRED_ALL = 0x00<<8,
		MASK_BR_INST_EXEC_ANY = 0x7f<<8,
		MASK_BR_MISP_EXEC_ANY = 0x7f<<8,
	};
	enum {
		EVENT_ENABLE = 0x400000,
		EVENT_DISABLE = ~0x400000,
		EVENT_USER_ENABLE = 0x10000,
		EVENT_USER_DISABLE = ~0x10000,
		EVENT_PRIV_ENABLE = 0x20000,
		EVENT_PRIV_DISABLE = ~0x20000,
	};
}

class Msr {
	public:
		Msr() {};

		int Read(unsigned int reg, uint64_t &value, int cpu=0);
		int Write(unsigned int reg, uint64_t value, int cpu=0);
	private:
};

#endif
