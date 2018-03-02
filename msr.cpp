#include "msr.hpp"
#include <sstream>
#include <iostream>

extern int errno;

using namespace std;

int Msr::Read(unsigned int reg, uint64_t &value, int cpu) {
	int fd;
	stringstream msr_filename;
	int retval = 0;
	int read_count = 0;

	fd = -1;
	msr_filename << "/dev/cpu/" << cpu << "/msr";

	if ((fd = open(msr_filename.str().c_str(), O_RDONLY)) < 0) {
		return errno;
	}

	if (lseek(fd, (off_t)reg, SEEK_SET)<0) {
		retval = errno;
	}

	if (!retval) {
		read_count = read(fd, &value, 8);
		if (read_count == -1)
			retval = errno;
		else if (read_count != 8)
			retval = -1;
	}
	close(fd);
	return errno;
}

int Msr::Write(unsigned int reg, uint64_t value, int cpu) {
	int fd;
	stringstream msr_filename;
	int retval = 0;
	int write_count = 0;

	fd = -1;
	msr_filename << "/dev/cpu/" << cpu << "/msr";

	if ((fd = open(msr_filename.str().c_str(), O_WRONLY)) < 0) {
		return errno;
	}

	if (lseek(fd, (off_t)reg, SEEK_SET)<0) {
		retval = errno;
	}

	if (!retval) {
		write_count = write(fd, &value, 8);
		if (write_count  == -1)
			retval = errno;
		else if (write_count != 8)
			retval = -1;
	}
	close(fd);
	return errno;
}
