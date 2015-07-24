#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

int find_utah(char ***cube, int size, int i1, int j1, char team, char my_team, char axis, int horizontal)
{
  int i, j, k, w, count, middle_count;
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

  if (horizontal)
  {
    int *temp = x;
    x = y;
    y = temp;
  }

  for (k = 0; k < size; ++k) {
    count = 0;
    middle_count = 0;
    for (i = i1; i < i1 + 3; ++i) {
      for (j = j1; j < j1 + 2; ++j) {
        if (cube[*x][*y][*z] == team) {
          ++count;
          if (j - j1 == 1)
           ++middle_count;
        }
      }
    }

    if (count == 5 || (count == 4 && middle_count != 0)) {
      // find the available space
      // check the middle first
      j = j1 + 1;
      i = i1;
      if (cube[*x][*y][*z] == '_') {
        cube[*x][*y][*z] = my_team;
        return 1;
      }
      ++i;
      if (cube[*x][*y][*z] == '_') {
        cube[*x][*y][*z] = my_team;
        return 1;
      }
      // now the corners
      j = j1;
      i = i1;
      if (cube[*x][*y][*z] == '_') {
        cube[*x][*y][*z] = my_team;
        return 1;
      }
      ++i;
      if (cube[*x][*y][*z] == '_') {
        cube[*x][*y][*z] = my_team;
        return 1;
      }
      j = j1 + 2;
      i = i1;
      if (cube[*x][*y][*z] == '_') {
        cube[*x][*y][*z] = my_team;
        return 1;
      }
      ++i;
      if (cube[*x][*y][*z] == '_') {
        cube[*x][*y][*z] = my_team;
        return 1;
      }
    }
  }

  return 0;
}

int find_move_axis(char ***cube, int size, char team, char my_team, char axis)
{
  int i, j;

  for (i = 0; i <= size - 3; ++i) {
    for (j = 0; j <= size - 2; ++j) {
      if (find_utah(cube, size, i, j, team, my_team, axis, 0))
        return 1;
      if (find_utah(cube, size, j, i, team, my_team, axis, 1))
        return 1;
    }
  }

  return 0;
}

int find_move(char ***cube, int size, char team, char my_team)
{
  if (find_move_axis(cube, size, team, my_team, 'X'))
    return 1;
  if (find_move_axis(cube, size, team, my_team, 'Y'))
    return 1;
  if (find_move_axis(cube, size, team, my_team, 'Z'))
    return 1;
  return 0;
}

static const int MAX_SIZE = 1000;

int main(int argc, char **argv)
{
    char **cube[MAX_SIZE];
    int i, j, k, first_cube;;

    for (i = 0; i < MAX_SIZE; ++i) {
      cube[i] = (char **)malloc(sizeof(char *) * MAX_SIZE);
      for (j = 0; j < MAX_SIZE; j++) {
        cube[i][j] = (char *)malloc(sizeof(char) * MAX_SIZE);
      }
    }

    FILE *file = stdin;
    if (argc == 2)
      file = fopen(argv[1], "r");

    first_cube = 1;
    while(!feof(file)) {
      int size = MAX_SIZE;
      for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
          for (k = 0; k < size; ++k) {
            char next = fgetc(file);
            // well crap, we're not big enough
            if (k == MAX_SIZE - 1) {
              sleep(5);
              return 1;
            }
            if (next == ' ') {
              size = k;
              break;
            }
            cube[i][j][k] = next;
          }
          // space or newline; except when we detected it above
          if (i != 0 || j != 0)
            fgetc(file);
        }
      }
      // blank newline
      fgetc(file);

      // If we can't find a winning move for X,
      // find a winning move for O and block it
      if (0 && !find_move(cube, size, 'X', 'X')) {
        if (!find_move(cube, size, 'O', 'X')) {
          //sleep(2);
        }
      }

      if (!first_cube)
        putc('\n', stdout);
      first_cube = 0;
      for (i = 0; i < size; ++i) {
        if (i != 0)
          putc('\n', stdout);
        for (j = 0; j < size; ++j) {
          if (j != 0)
            putc(' ', stdout);
          for (k = 0; k < size; ++k) {
            putc(cube[i][j][k], stdout);
          }
        }
      }
      putc('\n', stdout);
    }

    for (i = 0; i < MAX_SIZE; ++i) {
      for (j = 0; j < MAX_SIZE; j++) {
        free(cube[i][j]);
      }
      free(cube[i]);
    }

    return 0;
}
