#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

struct timespec start_time;
struct timespec cur_time;

void print_msg(char * msg) {
	clock_gettime(CLOCK_REALTIME, &cur_time);
	long time = ((cur_time.tv_nsec - start_time.tv_nsec) / 1000) + (cur_time.tv_sec - start_time.tv_sec) * 1000000;
	printf("PID: %d\tTime: %lu  \tMessage: %s\n", getpid(), time, msg);
}

void grandparent(pid_t pid) {
	print_msg("grandparent sleeping");
	sleep(6);
	print_msg("grandparent awake");
	print_msg("grandparent starting wait");
	waitpid(pid, NULL, 0);
	print_msg("grandparent wait finished");
	print_msg("grandparent ending process");
	exit(0);
}

void parent() {
	print_msg("parent sleeping");
	sleep(3);
	print_msg("parent awake");
	print_msg("parent ending process");
	exit(0);

}

void child() {
	print_msg("child process");
	print_msg("child waiting for adoption");
	while (getppid() != 1);
	print_msg("child adopted");
	print_msg("child ending process");
	exit(0);
}

int main() {
	clock_gettime(CLOCK_REALTIME, &start_time);

	print_msg("grandparent process");
	pid_t pid = fork();
	if (pid != 0) grandparent(pid);
	else {
		print_msg("parent process");
		pid = fork();
		if (pid != 0) parent();
		else child();
	}
}
