//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    int x=1;
    printf("%36s\n","****** The Board ******");
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
    bool noMove=false,sameColour1=false, sameColour2=true;

    while(!noMove){
        if(i==2){
            i-=2;
        }
        while(!sameColour1){
            printf("\n%s's turn to move.",players[i].player_name);
            printf("\nEnter the coordinates of the piece to move:\nx1:");
            scanf("%d",&x1);
            printf("y1:");
            scanf("%d",&y1);

            if(x1<1 || x1>8 || y1<1 || y1>8){
                printf("Invalid coordinates. Please try again.\n");
                printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
            }else if(board[x1-1][y1-1].stack == NULL){
                printf("You have not selected a piece.\nPlease try again.\n");
            }else if(board[x1-1][y1-1].stack->p_color!=players[i].player_color ){
                printf("You did not choose a piece that matches your colour.\n");
                printf("Please try again.\n");
            }else if(board[x1-1][y1-1].stack->p_color==players[i].player_color){
                sameColour1=true;
            }

        }

        while(sameColour2){
            printf("\nEnter the coordinates of the square to be captured:\nx2:");
            scanf("%d",&x2);
            printf("y2:");
            scanf("%d",&y2);

            if(x2<1 || x2>8 || y2<1 || y2>8){
                printf("Invalid coordinates. Please try again.\n");
                printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
            }else if(board[x2-1][y2-1].type == INVALID){
                printf("Invalid square. Please choose a valid square.\n");
            }else if(board[x2-1][y2-1].num_pieces <= abs(x1-x2) || board[x2-1][y2-1].num_pieces <= abs(y1-y2)){
                printf("Invalid move.\nDisplacement of a piece should be less than the number of pieces in the stack.\n");
            }else if(board[x2-1][y2-1].stack==NULL || board[x2-1][y2-1].stack->p_color != players[i].player_color){
                sameColour2=false;
            }else if(board[x2-1][y2-1].stack->p_color == players[i].player_color){
                printf("You can't capture a piece that matches your colour.\n");
                printf("Please try again.\n");
            }
        }

        board[--x2][--y2].num_pieces += board[--x1][--y1].num_pieces;
        board[x2][y2].stack = push(board[x1][y1].stack,board[x2][y2].stack);
        set_empty(&board[x1][y1]);

        print_board(board);

        if(players[i].captured == 18){
            noMove = true;
        }

        i++;
        sameColour1=false;
        sameColour2=true;
    }



}

piece* push(piece *p1,piece *top)
{
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color=p1->p_color;
    top->next=curr;

    return top;
}