#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void challenge_func() {
	char buf[256] = { 0 };

	read(0, buf, 0x1000);

	printf("You said: %s\n", buf);
	puts("About to return from challenge_func!");
}

void win() {
	char flag_buf[64];
	int fd = open("/flag", O_RDONLY);
	int bytes_read = read(fd, flag_buf, 64);
	printf("Here is your flag: %s\n", flag_buf);
}

void main() {
	printf("win is located at: %p");
	puts("About to call challenge_func!");
	challenge_func();
}
