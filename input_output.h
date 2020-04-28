
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

player play_game(player players[PLAYERS_NUM],square board [BOARD_SIZE][BOARD_SIZE]);

void make_move(player Player,square board[BOARD_SIZE][BOARD_SIZE]);

void place_reserve(player Player,square board[BOARD_SIZE][BOARD_SIZE]);

piece* push(piece *p1,piece *top, int p1_num_pieces);

piece* remove_piece(piece *top);
player count_captured(piece *top,player Player);

void printList( piece *top );