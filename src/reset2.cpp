//============================================================================
// Name        : reset2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <termios.h>
#include <stdio.h>
#include <fstab.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <iostream>
using namespace std;
#include <unistd.h>
#include <errno.h>
#include "Sys.h"

int main(int argc, char *argv[]) {
	int fd, serial;
	char ttyName[256];
	strcpy(ttyName, "/dev/ttyUSB0");
	if (argc > 1)
		strcpy(ttyName, argv[1]);
	if ((fd = open(ttyName, O_RDONLY)) < 0) {
		ERROR("Cannot open %s ",ttyName);
		PERROR();
		return -1;
	}
	if ((ioctl(fd, TIOCMGET, &serial)) < 0) {
		ERROR("Cannot ioctl %s ",ttyName);
		PERROR();
		return -1;
	}
	serial |= TIOCM_RTS;
//	serial |= TIOCM_DTR;
	if ((ioctl(fd, TIOCMSET, &serial)) < 0) {
		ERROR("Cannot ioctl %s ",ttyName);
		PERROR();
		return -1;
	}
	sleep(1);
	if ((ioctl(fd, TIOCMGET, &serial)) < 0) {
		ERROR("Cannot ioctl %s ",ttyName);
		PERROR();
		return -1;
	}
	serial &= TIOCM_RTS;
//	serial |= TIOCM_DTR;
	if ((ioctl(fd, TIOCMSET, &serial)) < 0) {
		ERROR("Cannot ioctl %s ",ttyName);
		PERROR();
		return -1;
	}
	sleep(1);
	close(fd);
}

