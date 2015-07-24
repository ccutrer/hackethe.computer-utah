#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char **cube[3];
    int i, j, k, first_cube;;

    for (i = 0; i < 3; ++i) {
      cube[i] = (char **)malloc(sizeof(char *) * 3);
      for (j = 0; j < 3; j++) {
        cube[i][j] = (char *)malloc(sizeof(char) * 3);
      }
    }

    FILE *file = stdin;
    file = fopen("example1", "r");

    first_cube = 1;
    while(!feof(file)) {
      for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
          for (k = 0; k < 3; ++k) {
            cube[i][j][k] = fgetc(file);
          }
          // space or newline
          fgetc(file);
        }
      }
      // blank newline
      fgetc(file);

      if (!first_cube)
        putc('\n', stdout);
      first_cube = 0;
      for (i = 0; i < 3; ++i) {
        if (i != 0)
          putc('\n', stdout);
        for (j = 0; j < 3; ++j) {
          if (j != 0)
            putc(' ', stdout);
          for (k = 0; k < 3; ++k) {
            putc(cube[i][j][k], stdout);
          }
        }
      }
      putc('\n', stdout);
    }

    return 0;
}
