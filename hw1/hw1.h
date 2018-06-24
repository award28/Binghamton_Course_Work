#ifndef __HW1_H__
#define __HW1_H__

#include <stdio.h>

#define printf myprintf

#define MYMSG(format, ...) \
	printf("Original message --> %s:%d: " format, __FILE__, __LINE__, __VA_ARGS__)

int str_manip(char * str, char * substr);
int myprintf(const char * format, ...);

#endif //__HW1_H__
