//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    int x=1;
    printf("\t     ****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|     ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G-%d ",board[i][j].num_pieces);
                    else printf("| R-%d ",board[i][j].num_pieces);
                }
            }
            else{
                printf("|  -  ");
            }
        }
        printf("|  %d\n",x++);
    }
    for(int i=0;i<BOARD_SIZE;i++){
        printf("   %d  ",i+1);
    }
    printf("\n");
}

void make_move(player players[PLAYERS_NUM],square board [BOARD_SIZE][BOARD_SIZE])
{
    int i=0,x1=0,y1=0,x2=0,y2=0;
    piece *top=NULL;
    printf("\n%s's turn to move.",players[i].player_name);
    printf("\nEnter the coordinates of the piece to move:\nx1:");
    scanf("%d",&x1);
    printf("y1:");
    scanf("%d",&y1);
    printf("\nEnter the coordinates of the square to be captured:\nx2:");
    scanf("%d",&x2);
    printf("y2:");
    scanf("%d",&y2);

    board[--x2][--y2].num_pieces++;
    board[x2][y2].stack=push(board[--x1][--y1].stack,board[x2][y2].stack);
    set_empty(&board[x1][y1]);

}

piece* push(piece *p1,piece *p2)
{
    piece *curr = p2;
    p2 = malloc(sizeof(piece));
    p2->p_color=p1->p_color;
    p2->next=curr;
}