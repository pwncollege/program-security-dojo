#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void write_file(char *filename, int offset);

int main(int argc, char **argv) {
  int offset = 0;

  char filename[256] = "";

  while (1) {
    memset(filename, 0, sizeof(filename));
    printf("filename (or EXIT): ");
    scanf("%s", filename);

    if (strcmp(filename, "EXIT") == 0) {
      break;
    }

    printf("offset: ");
    scanf("%d", &offset);

    write_file(filename, offset);
  } 
}

void write_file(char *filename, int offset) {
  volatile struct {
    char buf[256];
    int file_size;
    char *offset_ptr;
    struct stat statbuf;
    int fd;
  } locals;


  locals.offset_ptr = locals.buf + offset;

  // open the file and get the size
  locals.fd = open(filename, O_RDONLY);

  if (locals.fd < 0) {
    perror("open");
    exit(2);
  }


  fstat(locals.fd, &locals.statbuf);
  locals.file_size = locals.statbuf.st_size;

  // read and write the file
  read(locals.fd, &locals.buf, locals.file_size);
  if (close(locals.fd) < 0) {
    perror("close");
    exit(3);
  }
  printf("%s\n", locals.offset_ptr);
}
