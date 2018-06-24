#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int lower(int c) {
    if(c > 64 && c < 91) {
        c += 32;
    }
    return c;	
}

int str_manip(char* str, char* substr) {
	if (!str || !strlen(str) || !substr || !strlen(substr)) return -1;

	int count = 0;
	int len = strlen(str);
	int substr_len = strlen(substr);

	char *l_str = malloc(len + 1);
	char *r_str = malloc(len + 1);
	char *l_substr = malloc(substr_len + 1);
	
	for(int i = 0; str[i]; i++) {
		l_str[i] = lower(str[i]);
		r_str[len - i - 1] = lower(str[i]);
	}

	for(int i = 0; substr[i]; i++) {
		l_substr[i] = lower(substr[i]);
	}

	const char *l_tmp = l_str;
	const char *r_tmp = r_str;

	while ((l_tmp = strstr(l_tmp, l_substr))) {
		count++;
		l_tmp++;
	}
	while ((r_tmp = strstr(r_tmp, l_substr))) {
		count++;
		r_tmp++;
	}
	
	printf("str %s\n", str);
	printf("newstr %s%s\n", l_str, r_str);
	printf("substr %s\n", substr);
	printf("occurences %d\n", count);
	free(l_str);
	free(r_str);
	free(l_substr);
	return 0;
}
