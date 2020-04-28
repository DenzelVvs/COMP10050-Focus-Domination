//
// Created by Denzel on 12/04/2020.
//

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H

#define PLAYERS_NUM 2

#include "game_init.h"

//Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);

//function to play the game
player play_game(player players[PLAYERS_NUM],square board [BOARD_SIZE][BOARD_SIZE]);

//function to move a piece on the board
void make_move(player Player,square board[BOARD_SIZE][BOARD_SIZE]);

//function to place a reserve piece back on the board
piece* place_reserve(player Player,square board[BOARD_SIZE][BOARD_SIZE]);

//function to join two pieces/stacks together
piece* push(piece *p1,piece *top, int p1_num_pieces);

//function to maintain stack size of 5
piece* remove_piece(piece *top);

//function to count number of enemy pieces captured and number of own pieces reserved
player count_captured(piece *top,player Player);