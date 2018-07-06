//game.h
#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10


void init_board(char board[ROWS][COLS], int rows, int cols,char set);
void display_board(char board[ROWS][COLS], int row, int col);
void set_mine(char board[ROWS][COLS], int row, int col);
int remove_mine(char board1[ROWS][COLS], char board2[ROWS][COLS], int row, int col);
int count_show_mine(char board[ROWS][COLS], int row, int col);
void open_board(char board[ROWS][COLS], int x, int y);
int get_mine_count(char board[ROWS][COLS], int row, int col);
void stamp_mine(char board[ROWS][COLS], int row, int col);
#endif//__GAME_H__
