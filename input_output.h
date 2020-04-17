
//
// Created by Lili on 24/03/2020.
//

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H

#define PLAYERS_NUM 2

#include "game_init.h"

//Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);

void make_move(player players[PLAYERS_NUM],square board [BOARD_SIZE][BOARD_SIZE]);

piece* push(piece *p1,piece *p2);