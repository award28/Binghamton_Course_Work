#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct info {
    char type;
    char * str;
    char ch;
    int val;
    struct info * next;
} INFO;

static INFO* info_constructor(char t, char ch, char * str, int val) {
	INFO *type = malloc(sizeof(INFO));
	type->type = t;
	type->str = str;
	type->ch = ch;
	type->val = val;
	type->next = NULL;
	return type;
}

int print(const char * str, int start, int size) {
	for (int i = start; i < size; i++) {
		if (str[i] == '%') return i + 2;
		printf("%c", str[i]);
	}
	return size;
}

int myprintf(const char * format, ...) {
	va_list args;
	int index = 0;
	int size = strlen(format);
	const char *temp = format;
	INFO * types = NULL;
	INFO * head = NULL;
	INFO * type = NULL;

	index = print(format, index, size);
	va_start(args, format);

	while((temp = strstr(temp, "%"))) {
		temp++;
		if (temp == strstr(temp, "c")) {
			type = info_constructor('c', va_arg(args, int), "", 0);
			printf("%c", type->ch);
		} else if (temp == strstr(temp, "s")) {
			type = info_constructor('s', '\0', va_arg(args, char *), 0);
			printf("%s", type->str);
		} else if (temp == strstr(temp, "d")) {
			type = info_constructor('d', '\0', "", va_arg(args, int));
			printf("%d", type->val);
		} else {
			printf("\n\nError: Incomplete format specifier.\n");
			return -1;
		}
		
		index = print(format, index, size);
		if (!types) {
			types = type;
			head = types;
		} else {
			types->next = type;
			types = types->next;
		}
	}
	va_end(args);
	
	printf("\nArgument list:\n");
	while(head) {
		type = head;
		switch(type->type) {
			case 'c':
				printf("Char-->%c\n", type->ch);
				break;
			case 's':
				printf("String-->%s\n", type->str);
				break;
			case 'd':
				printf("Integer-->%d\n", type->val);
				break;
		}
		head = head->next;
		free(type);
	}
	return 0;
}
