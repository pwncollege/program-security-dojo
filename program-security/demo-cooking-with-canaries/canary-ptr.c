#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void challenge_func() {
	char STACK_STRING[] = "This is a value on the stack";
	struct {
		char buf[256];
		char *vulnerable_pointer;
	} a;
	a.vulnerable_pointer = STACK_STRING;


	read(0, &a.buf, 0x1000);

	printf("Here is the string on the stack: %s\n", a.vulnerable_pointer);
}

void win() {
	char flag_buf[64];
	int fd = open("/flag", O_RDONLY);
	int bytes_read = read(fd, flag_buf, 64);
	printf("Here is your flag: %s\n", flag_buf);
}

void main() {
	puts("About to call challenge_func!");
	challenge_func();
	challenge_func();
}
