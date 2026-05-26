#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 8 /**< Board size. */

/**
 * Knight move offsets
 *
 * Moves that a knight can make relative to the current position.
 * For example,
 * x += MOVES_X[0]; y += MOVES_Y[0]
 * corresponds to one of the eight moves that a knight can make, where `x` and
 * `y` represent the current position.
 */
#define MOVE_COUNT 8 /**< Number of moves that a knight can make */
const int MOVES_X[MOVE_COUNT] = {2, 1, -1, -2, -2, -1, 1, 2};
const int MOVES_Y[MOVE_COUNT] = {1, 2, 2, 1, -1, -2, -2, -1};

typedef unsigned int board_t[SIZE][SIZE];

/** Determines whether a move is possible from a starting position.
 *
 * @param move_id One of the 8 moves that the knight wants to make [0, 7]
 * @param x Current horizontal position
 * @param y Current vertical position
 * @param visited A two-dimensional array that represents the squares. If a
 * value is positive, then the corresponding field was visited before.
 * @return True if the move is possible, else false.
 */
bool move_is_possible(size_t move_id, size_t x, size_t y, board_t visited) {
  int newX = x + MOVES_X[move_id];
  int newY = y + MOVES_Y[move_id];
  if (newX < 0 || newX >= SIZE) {
    return false;
  }
  if (newY < 0 || newY >= SIZE) {
    return false;
  }
  if (visited[newX][newY] <= 0) {
    return true;
  } else {
    return false;
  }
}

/** Attempts a tour by picking the first accessible square.
 *
 * @param start_x Horizontal starting position on the board
 * @param start_y Vertical starting position on the board
 * @return The number of visited squares
 * @note An array is created for the attempt
 */
unsigned int tour_greedy(size_t start_x, size_t start_y) {
  board_t visited = {{0}};
  int x = start_x;
  int y = start_y;
  visited[x][y] = 1;
  int visited_squares = 1;
  bool moreMoves = true;

  while (moreMoves) {
    for (int i = 0; i < MOVE_COUNT; i++) {
      if (move_is_possible(i, x, y, visited)) {
        // do the move
        x += MOVES_X[i];
        y += MOVES_Y[i];
        // update the visited board
        visited[x][y] = 1;
        visited_squares += 1;
        break;
      } else if (i == 7) {
        moreMoves = false;
      }
    }
  }

  return visited_squares;
}

/** Attempts tours beginning from each square available on the board
 * and annotates the number of visited squares like this:
 *
 * 15  8 15 15
 * 10  6  4 15
 *  8 10 14 14
 * 14 14 14 11
 */
void greedy_tour_from_each_square() {
  for (int i = 0; i < SIZE; i++) {
    int tourArray[SIZE];
    for (int j = 0; j < SIZE; j++) {
      int visited_squares = tour_greedy(j, i);
      tourArray[j] = visited_squares;
      printf("%d ", visited_squares);
    }
    printf("\n");
  }
}

//final