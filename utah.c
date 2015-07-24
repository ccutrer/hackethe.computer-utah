#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

int find_move_axis(char ***cube, char team, char axis)
{
  int i, j, k, w;
  int *x, *y, *z;
  if (axis == 'X') {
    x = &i;
    y = &j;
    z = &k;
  } else if (axis == 'Y') {
    x = &j;
    y = &k;
    z = &i;
  } else {
    x = &k;
    y = &i;
    z = &j;
  }

  // compute the number for our team for each column (9 of them)
  int *columns[3];

  for (i = 0; i < 3; ++i) {
    columns[i] = (int *)malloc(sizeof(int) * 3);
    for (j = 0; j < 3; ++j) {
      columns[i][j] = 0;
      for (k = 0; k < 3; ++k) {
        columns[i][j] += (cube[*x][*y][*z] == team ? 1 : 0);
      }
    }
  }

  int result = 0;

  // check axis 1 for columns that have 4 of our team
  for (i = 0; i < 3; ++i) {
    for (w = 0; w < 2; ++w) {
      if (columns[i][w] + columns[i][w + 1] >= 4) {
        // any available corner move is a winner;
        // check all 4:
        // XX
        // __
        // XX
        j = w;
        k = 0;
        if (cube[*x][*y][*z] == '_') {
          cube[*x][*y][*z] = 'X';
          result = 1;
          goto done;
        }
        k = 2;
        if (cube[*x][*y][*z] == '_') {
          cube[*x][*y][*z] = 'X';
          result = 1;
          goto done;
        }
        j = w + 1;
        if (cube[*x][*y][*z] == '_') {
          cube[*x][*y][*z] = 'X';
          result = 1;
          goto done;
        }
        k = 0;
        if (cube[*x][*y][*z] == '_') {
          cube[*x][*y][*z] = 'X';
          result = 1;
          goto done;
        }
        // a move in the middle is only a winner if you own the one next to it
        k = 1;
        if (cube[*x][*y][*z] == team) {
          k = 0;
          if (cube[*x][*y][*z] == '_') {
            cube[*x][*y][*z] = 'X';
            result = 1;
            goto done;
          }
        }
        k = 0;
        if (cube[*x][*y][*z] == team) {
          j = w;
          if (cube[*x][*y][*z] == '_') {
            cube[*x][*y][*z] = 'X';
            result = 1;
            goto done;
          }
        }
      }
    }
  }

  // and now axis 2
    for (w = 0; w < 2; ++w) {
      for (j = 0; j < 2; ++j) {
        if (columns[w][j] + columns[w + 1][j] >= 4) {
          // any available corner move is a winner;
          // check all 4:
          // XX
          // __
          // XX
          i = w;
          k = 0;
          if (cube[*x][*y][*z] == '_') {
            cube[*x][*y][*z] = 'X';
            result = 1;
            goto done;
          }
          k = 2;
          if (cube[*x][*y][*z] == '_') {
            cube[*x][*y][*z] = 'X';
            result = 1;
            goto done;
          }
          i = w + 1;
          if (cube[*x][*y][*z] == '_') {
            cube[*x][*y][*z] = 'X';
            result = 1;
            goto done;
          }
          k = 0;
          if (cube[*x][*y][*z] == '_') {
            cube[*x][*y][*z] = 'X';
            result = 1;
            goto done;
          }
          // a move in the middle is only a winner if you own the one next to it
          k = 1;
          if (cube[*x][*y][*z] == team) {
            i = w;
            if (cube[*x][*y][*z] == '_') {
              cube[*x][*y][*z] = 'X';
              result = 1;
              goto done;
            }
          }
          k = 0;
          if (cube[*x][*y][*z] == team) {
            k = 1;
            if (cube[*x][*y][*z] == '_') {
              cube[*x][*y][*z] = 'X';
              result = 1;
              goto done;
            }
          }
        }
      }
    }

done:

  for (i = 0; i < 3; ++i) {
    free(columns[i]);
  }
  return result;
}

int find_move(char ***cube, char team)
{
  int result = find_move_axis(cube, team, 'X');
  if (result)
    return result;
  result = find_move_axis(cube, team, 'Y');
  if (result)
    return result;
  result = find_move_axis(cube, team, 'Z');
  return result;
}

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

      // If we can't find a winning move for X,
      // find a winning move for O and block it
      if (!find_move(cube, 'X'))
        find_move(cube, 'O');

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
