#include <sys/types.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_SIZE 64

#define left_to_right(a, b)   \
do {                 \
    int temp = a;    \
    a = b;           \
    b = temp;        \
} while(0)

int get_line(char* buf, int fd) {
    ssize_t line = read(fd, buf, L_SIZE);
    if (1 > line) return line;
    ssize_t loc = 0;
    while(loc < line && buf[loc] != '\n') loc++;
    buf[loc] = '\0';
    lseek(fd, loc - line + 1, SEEK_CUR);
    return loc;
}

int swap(char* buf, int fd, int left, int right, int buf_size) {
	int cur_col = 1;
	char first[L_SIZE];
	char second[L_SIZE];
	int f_size = 0;
	int s_size = 0;
	int i;

	for(i = 0; i < buf_size; i++) {
		if (buf[i] == ' ' || buf[i] == '\t') cur_col++;
		else if (cur_col == left) {
			while (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\0') {
				first[f_size] = buf[i];
				i++;
				f_size++;
			}
			cur_col++;
		} else if (cur_col == right) {
			while (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\0') {
				second[s_size] = buf[i];
				i++;
				s_size++;
			}
			cur_col++;
		}
	}

	cur_col = 1;
	int new_i = 0;
	char new_buf[i + 1];

	for(i = 0; i < buf_size; i++, new_i++) {
		if (buf[i] == ' ' || buf[i] == '\t') {
			new_buf[new_i] = ' ';
			cur_col++; 
		} else if (cur_col == left) {
			for (int j = 0; j < s_size; j++) {
				new_buf[new_i] = second[j];
				new_i++;
			}
			while (buf[i] != ' ' && buf[i] != '\t' &&  buf[i] != '\0') i++;
			cur_col++;
			new_buf[new_i] = ' ';
		} else if (cur_col == right) {
			for (int j = 0; j < f_size; j++) {
				new_buf[new_i] = first[j];
				new_i++;
			}
			while (buf[i] != ' ' && buf[i] != '\t' &&  buf[i] != '\0') i++;
			cur_col++;
			new_buf[new_i] = ' ';
		} else new_buf[new_i] = buf[i];
	}
	new_buf[new_i] = '\n';
	write(fd, new_buf, i + 1);
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 4) return -1;

	char* file = argv[1];
	int left = atoi(argv[2]);
	int right = atoi(argv[3]);
	int in_fd = open(file, O_RDONLY);
	int out_fd = open(file, O_WRONLY | O_APPEND);
	char buf[L_SIZE];

	if (left > right) left_to_right(left, right);
	if (left < 1) return 1;

	write(out_fd, "===\n", 4);

	int rv = get_line(buf, in_fd);
	int num_cols;
	int i;

	while(rv > 0 && strncmp(buf, "===", 3) != 0) {
		num_cols = 1;
		for(i = 0; buf[i] != '\0'; i++) if (buf[i] == ' ' || buf[i] == '\t') num_cols++;
		if (num_cols >= right) swap(buf, out_fd, left, right, i);
		else { write(out_fd, buf, i); write(out_fd, "\n", 1); }
		rv = get_line(buf, in_fd);
	}

	close(in_fd);
	close(out_fd);
	return 0;
}
