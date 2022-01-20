#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void hello(int signum) { write(1, "hello", 6); }

int main(int argc, char **argv) {
  signal(SIGINT, hello);
  while (1)
    ;

  return 0;
}
