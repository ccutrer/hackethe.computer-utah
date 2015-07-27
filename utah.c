#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

#define CHECK_X(i, j) \
  if (i >= 0 && j >= 0 && i < size && j < size && cube[i][j][z] == cube[x][y][z]) { \
    contiguous += 1; \
    if (max_contiguous < contiguous) \
      max_contiguous = contiguous; \
  } else { \
    contiguous = 0; \
  }

#define CHECK_Y(i, j) \
  if (i >= 0 && j >= 0 && i < size && j < size && cube[x][i][j] == cube[x][y][z]) { \
    contiguous += 1; \
    if (max_contiguous < contiguous) \
      max_contiguous = contiguous; \
  } else { \
    contiguous = 0; \
  }

#define CHECK_Z(i, j) \
  if (i >= 0 && j >= 0 && i < size && j < size && cube[i][y][j] == cube[x][y][z]) { \
    contiguous += 1; \
    if (max_contiguous < contiguous) \
      max_contiguous = contiguous; \
  } else { \
    contiguous = 0; \
  }

int check_from_frd(char ***cube, int size, int x, int y, int z)
{
  int contiguous, max_contiguous;

  contiguous = 0;
  max_contiguous = 0;
  CHECK_X(x - 1, y - 1);
  CHECK_X(x, y - 1);
  CHECK_X(x + 1, y - 1);
  CHECK_X(x + 1, y);
  CHECK_X(x + 1, y + 1);
  CHECK_X(x, y + 1);
  CHECK_X(x - 1, y + 1);
  CHECK_X(x - 1, y);

  CHECK_X(x - 1, y - 1);
  CHECK_X(x, y - 1);
  CHECK_X(x + 1, y - 1);
  if (max_contiguous >= 4)
    return 1;

  contiguous = 0;
  max_contiguous = 0;
CHECK_Y(y - 1, z - 1);
CHECK_Y(y, z - 1);
CHECK_Y(y + 1, z - 1);
CHECK_Y(y + 1, z);
CHECK_Y(y + 1, z + 1);
CHECK_Y(y, z + 1);
CHECK_Y(y - 1, z + 1);
CHECK_Y(y - 1, z);

  CHECK_Y(y - 1, z - 1);
CHECK_Y(y, z - 1);
CHECK_Y(y + 1, z - 1);
  if (max_contiguous >= 4)
    return 1;

    contiguous = 0;
    max_contiguous = 0;
  CHECK_Z(x - 1, z - 1);
  CHECK_Z(x, z - 1);
  CHECK_Z(x + 1, z - 1);
  CHECK_Z(x + 1, z);
  CHECK_Z(x + 1, z + 1);
  CHECK_Z(x, z + 1);
  CHECK_Z(x - 1, z + 1);
  CHECK_Z(x - 1, z);

    CHECK_Z(x - 1, z - 1);
  CHECK_Z(x, z - 1);
  CHECK_Z(x + 1, z - 1);

  if (max_contiguous >= 4)
    return 1;

  return 0;
}

char check_from(char ***cube, int size, int x, int y, int z)
{
  // have to slide our check for two on either side
  int i, j, k;
  char found, best_found = 0;
  cube[x][y][z] = 'X';
  for (i = x - 1; i <= x + 1 && i < size; ++i) {
    if (i < 0)
      continue;
    for (j = y - 1; j <= y + 1 && j < size; ++j) {
      if (j < 0)
        continue;
      for (k = z - 1; k <= z + 1 && k < size; ++k) {
        if (k < 0)
          continue;
        if (cube[i][j][k] != 'X' && cube[i][j][k] != 'O')
          continue;
        cube[x][y][z] = 'X';
        if (check_from_frd(cube, size, i, j, k))
          return 'X';
        cube[x][y][z] = 'O';
        if (check_from_frd(cube, size, i, j, k))
          best_found = 'O';
      }
    }
  }
  // restore the cube
  cube[x][y][z] = '_';

  return best_found;
}

int find_move(char ***cube, int size)
{
  int i, j, k;

  int block_i = -1, block_j = -1, block_k = -1;
  char move_for;

  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      for (k = 0; k < size; ++k) {
        if (cube[i][j][k] == '_') {
          if ((i > 0 && cube[i - 1][j][k] != '_') ||
              (j > 0 && cube[i][j - 1][k] != '_') ||
              (k > 0 && cube[i][j][k - 1] != '_') ||
              (i < size - 1 && cube[i + 1][j][k] != '_') ||
              (j < size - 1 && cube[i][j + 1][k] != '_') ||
              (k < size - 1 && cube[i][j][k + 1] != '_')) {
            // if I move here, will it complete a Utah?
            if ((move_for = check_from(cube, size, i, j, k))) {
              if (move_for == 'X') {
                return 1;
              } else {
                block_i = i;
                block_j = j;
                block_k = k;
              }
            }
          }
        }
      }
    }
  }

  // no win for X, but found a block for O
  if (block_i != -1) {
    cube[block_i][block_j][block_k] = 'X';
    return 1;
  }
  return 0;
}

static const int MAX_SIZE = 11;

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

    int cube_count = 0;
    first_cube = 1;
    while(!feof(file)) {
      ++cube_count;
      int size = MAX_SIZE;
      for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
          for (k = 0; k < size; ++k) {
            char next = fgetc(file);
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

      find_move(cube, size);

      if (!first_cube) {
        putc('\n', stdout);
      }
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
