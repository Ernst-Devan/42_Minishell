#include <stdio.h>
#include <unistd.h>

char *argv[10] = { "./pwd.sh", NULL };
int main (void) {
    execve (argv[0], argv, NULL);
   return 0;
}