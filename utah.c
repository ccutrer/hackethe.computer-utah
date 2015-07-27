#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

int check_from_frd(char ***cube, int size, int x, int y, int z)
{
  // there are 4 rotations * 2 mirrors * 3 axes = 24 to check

  // z held constant-------------------------------
  // normal utah
  if (x < size - 1 &&
      y < size - 2 &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 2][z] ==
      cube[x][y][z] == cube[x + 1][y + 2][z])
    return 1;
  // mirrored
  if (x > 0 &&
      y < size - 2 &&
      cube[x][y][z] == cube[x - 1][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x - 1][y + 2][z] ==
      cube[x][y][z] == cube[x][y + 2][z])
    return 1;
  // clockwise
  if (x < size - 2 &&
      y < size - 1 &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z] &&
      cube[x][y][z] == cube[x + 2][y][z])
    return 1;
  // clockwise, flipped
  if (x < size - 2 &&
      y < size - 1 &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z] &&
      cube[x][y][z] == cube[x + 2][y + 1][z])
    return 1;
  // half turn
  if (x < size - 1 &&
      y < size - 2 &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y + 2][z])
    return 1;
  // half turn, flipped
  if (x < size - 1 &&
      y < size - 2 &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 2][z])
    return 1;
  // counter-clockwise
  if (x > 0 &&
      y < size - 1 &&
      cube[x][y][z] == cube[x - 1][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z])
    return 1;
  // counter-clockwise, flipped
  if (x < size - 2 &&
      y < size - 1 &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y + 1][z] &&
      cube[x][y][z] == cube[x + 2][y][z] &&
      cube[x][y][z] == cube[x + 2][y + 1][z])
    return 1;

  // y held constant-------------------------------
  // normal utah
  if (x < size - 1 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 2] ==
      cube[x][y][z] == cube[x + 1][y][z + 2])
    return 1;
  // mirrored
  if (x > 0 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x - 1][y][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x - 1][y][z + 2] ==
      cube[x][y][z] == cube[x][y][z + 2])
    return 1;
  // clockwise
  if (x < size - 2 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y][z + 1] &&
      cube[x][y][z] == cube[x + 2][y][z])
    return 1;
  // clockwise, flipped
  if (x < size - 2 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y][z + 1] &&
      cube[x][y][z] == cube[x + 2][y][z + 1])
    return 1;
  // half turn
  if (x < size - 1 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z + 2])
    return 1;
  // half turn, flipped
  if (x < size - 1 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 2])
    return 1;
  // counter-clockwise
  if (x > 0 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x - 1][y][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y][z + 1])
    return 1;
  // counter-clockwise, flipped
  if (x < size - 2 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x + 1][y][z] &&
      cube[x][y][z] == cube[x + 1][y][z + 1] &&
      cube[x][y][z] == cube[x + 2][y][z] &&
      cube[x][y][z] == cube[x + 2][y][z + 1])
    return 1;

  // x held constant-------------------------------
  // normal utah
  if (y < size - 1 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 2] ==
      cube[x][y][z] == cube[x][y + 1][z + 2])
    return 1;
  // mirrored
  if (y > 0 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x][y - 1][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y - 1][z + 2] ==
      cube[x][y][z] == cube[x][y][z + 2])
    return 1;
  // clockwise
  if (y < size - 2 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 1][z + 1] &&
      cube[x][y][z] == cube[x][y + 2][z])
    return 1;
  // clockwise, flipped
  if (y < size - 2 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 1][z + 1] &&
      cube[x][y][z] == cube[x][y + 2][z + 1])
    return 1;
  // half turn
  if (y < size - 1 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z + 2])
    return 1;
  // half turn, flipped
  if (y < size - 1 &&
      z < size - 2 &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 2])
    return 1;
  // counter-clockwise
  if (y > 0 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x][y - 1][z + 1] &&
      cube[x][y][z] == cube[x][y][z + 1] &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 1][z + 1])
    return 1;
  // counter-clockwise, flipped
  if (y < size - 2 &&
      z < size - 1 &&
      cube[x][y][z] == cube[x][y + 1][z] &&
      cube[x][y][z] == cube[x][y + 1][z + 1] &&
      cube[x][y][z] == cube[x][y + 2][z] &&
      cube[x][y][z] == cube[x][y + 2][z + 1])
    return 1;

  return 0;
}

char check_from(char ***cube, int size, int x, int y, int z)
{
  // have to slide our check for two on either side
  int i, j, k;
  char found, best_found = 0;
  cube[x][y][z] = 'X';
  for (i = x - 2; i < x + 2 && i < size; ++i) {
    if (i < 0)
      continue;
    for (j = y - 2; j < y + 2 && j < size; ++j) {
      if (j < 0)
        continue;
      for (k = z - 2; k < z + 2 && k < size; ++k) {
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

  // no win for X, but found a block for O
  if (block_i != -1) {
    cube[block_i][block_j][block_k] = 'X';
    return 1;
  }
  return 0;
}

static const int MAX_SIZE = 10;

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

      if (!find_move(cube, size))
        sleep(1);

      //if (cube_count == 2 && cube[2][2][1] == 'X')
        //sleep(3);
      if (!first_cube) {
        //return 1;
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
