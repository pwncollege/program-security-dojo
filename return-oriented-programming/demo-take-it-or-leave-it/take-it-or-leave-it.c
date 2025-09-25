#include <stdio.h>
#include <unistd.h>

void some_gadgets() {
  __asm__(
    ".intel_syntax noprefix\n"
    "pop rdi\n"
    "ret\n"
    "pop rsi\n"
    "ret\n"
    "pop rdx\n"
    "ret\n"
    "pop rcx\n"
    "ret\n"
    "syscall\n"
    "ret\n"
  );
}


void challenge() {
  char chal_buffer[64];

  puts("Inside challenge!");
  printf("chal_buffer is located at: %p\n", chal_buffer);

  read(0, chal_buffer, 96);


}


int main(int argc, char** argv, char **envp) {
  printf("Welcome to %s!", argv[0]);

  puts("Calling challenge!");
  challenge();


}
