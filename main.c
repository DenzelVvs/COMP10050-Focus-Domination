//
// Created by Lili on 26/03/2020.

#include <stdio.h>
#include "input_output.h"

int main() {
    player Winner;

    //declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];
    initialize_players(players);

    initialize_board(board);

    print_board(board);

    Winner = play_game(players,board);

    if(Winner.player_color==0){
        printf("\n\nRED wins!!!\n");
    }else if(Winner.player_color==1){
        printf("\n\nGREEN wins!!!\n");
    }

    printf("Pieces left on board: %u\nReserve pieces: %u\nCaptured enemy pieces: %u\n\nCONGRATULATIONS %s!!!\n",
            Winner.board_pieces,Winner.reserve,Winner.captured,Winner.player_name);

    return 0;
}
