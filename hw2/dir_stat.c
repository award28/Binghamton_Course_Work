#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define p_length 1000

typedef struct stat {
    int dirs;
    int syms;
    int reg;
} dir_stat;

void get_dirs(DIR* dp, dir_stat* stats, char p[p_length]) {
    if (dp == NULL) return;
    int type;
    DIR* sub;
    char subp[p_length];
    struct dirent* start = readdir(dp);

    while (start) {
	type = start->d_type;
        if (type == DT_REG) stats->reg++;
	else if (type ==  DT_LNK) stats->syms++;
	else if (type == DT_DIR) {
		if (strncmp(start->d_name, ".", p_length) != 0 && strncmp(start->d_name, "..", p_length) != 0) {
			stats->dirs++;
			strncpy(subp, p, p_length);
			strncat(subp, "/", p_length);
			strncat(subp, start->d_name, p_length);
			sub = opendir(subp);
			get_dirs(sub, stats, subp);
		}
	}
	start = readdir(dp);
    }
}

int main(int argc, char* argv[]) {
    DIR* dp;
    if (argc != 2 || !(dp = opendir(argv[1]))) return 1;

    char p[p_length] = "./";
    dir_stat *stats = malloc(sizeof(dir_stat));

    stats->reg = 0;
    stats->dirs = 0;
    stats->syms = 0;

    get_dirs(dp, stats, p);

    printf("Regular files: %i\n", stats->reg);
    printf("Directories: %i\n", stats->dirs);
    printf("Sym-links: %i\n", stats->syms);
}
