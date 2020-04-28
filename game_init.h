//
// Created by Denzel on 12/04/2020.
//

#ifndef FOCUS_GAME_INIT_H
#define FOCUS_GAME_INIT_H

#endif //FOCUS_GAME_INIT_H


#define BOARD_SIZE 8
#define PLAYERS_NUM 2

//colors that a piece can have
typedef enum color {
    RED,
    GREEN
}color;

// Square types
//INVALID: squares that are on the sides and where no piece can be placed
//VALID: squares where it is possible to place a piece or a stack
typedef enum square_type {
    VALID,
    INVALID
}square_type;

//Player
typedef struct player{
    //the color associated with the player
    color player_color;
    char player_name[15];
    unsigned int captured;  //number of enemy pieces captured
    unsigned int reserve;   //number of own pieces not on board
    unsigned int board_pieces;  //number of own pieces on board
}player;

// A piece
typedef struct piece {
    //the color associated with a piece
    color p_color;

    // This is a pointer to the next pieces
    // to create a stack. For this lab you do not have to think too much about it.
    struct piece * next;

}piece;

// A Square of the board
typedef struct square {
    // type of the square (VALID/INVALID)
    square_type type;

    //the piece or the top piece on the stack
    piece * stack;

    //number of pieces on the square
    int num_pieces;

}square;

//Function to create the players
void initialize_players(player players[PLAYERS_NUM]);

//functions to initialize squares in the board
void set_invalid(square * s);
void set_empty(square * s);
void set_green(square * s);
void set_red(square * s);

//Function to create the board
void initialize_board(square board[BOARD_SIZE][BOARD_SIZE]);
