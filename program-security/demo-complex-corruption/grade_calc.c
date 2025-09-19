#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

double calculate_module(char *module_name, int solved, int possible, bool checkpoint);

typedef struct {
	char letter_grade;
	int cutoff;
} grade_pair;


typedef struct {
  char *module_name;
  int solved;
  int possible;
  bool checkpoint;
} graded_module;

void setup_grades(grade_pair *ptr) {
	ptr[0].letter_grade = 'A';
	ptr[0].cutoff = 90;

	ptr[1].letter_grade = 'B';
	ptr[1].cutoff = 80;

	ptr[2].letter_grade = 'C';
	ptr[2].cutoff = 70;

	ptr[3].letter_grade = 'E';
	ptr[3].cutoff = 0;
}


grade_pair grade_cutoffs[4];

int main(int argc, char** argv) {
  graded_module modules[10];

	if ((argc -1) % 4 != 0 || argc == 1) {
		printf("Usage: %s <module_name> <solved> <possible> <checkpoint> ...\n", argv[0]);
    return 1;
	}
	setup_grades(grade_cutoffs);

  int module_count = (argc - 1) / 4;
  for (int i = 0; i < module_count; i++) {
    modules[i].module_name = argv[i * 4 + 1];
    modules[i].solved = atoi(argv[i * 4 + 2]);
    modules[i].possible = atoi(argv[i * 4 + 3]);
    modules[i].checkpoint = !strcmp("t", argv[i * 4 + 4])
  }
  
  return 0;
}


double calculate_module(char *module_name, int solved, int possible, bool checkpoint) {



	return 0;

}

