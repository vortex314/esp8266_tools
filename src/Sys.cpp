/*
 * Sys.cpp
 *
 *  Created on: Sep 22, 2015
 *      Author: lieven
 */

/*
 * Sys.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: lieven
 */
#include "errno.h"
#include "string.h"
#include "Sys.h"

#include "stdarg.h"
#include <malloc.h>
//#include <linux/time.h>
#include <time.h>

uint64_t Sys::millis() { // time in msec since boot, only increasing
	struct timespec deadline;
	clock_gettime(CLOCK_MONOTONIC, &deadline);
	return deadline.tv_sec * 1000 + deadline.tv_nsec / 1000000;
}

void SysLog(const char* level,const char* file, const char* function, const char * format, ...) {
	char buffer[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 256, format, args);
	va_end(args);

	uint64_t time = Sys::millis();

	printf("%06ld.%03ld |%s| %10s %10s | %s\r\n", time / 1000, time % 1000, level,file,function, buffer);
}

//extern "C" void SysLog(const char* file, const char* function, const char * format, va_list);

void Sys::log(const char*level,const char* file, const char* function, const char * format,
		...) {

	va_list args;
	va_start(args, format);
	SysLog(level,file, function, format, args);
	va_end(args);

}
