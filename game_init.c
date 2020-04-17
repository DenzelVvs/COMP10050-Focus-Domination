//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"

void initialize_players(player players[PLAYERS_NUM]){
    int choice=0;
    for(int i=0;i<PLAYERS_NUM;i++){
        printf("Enter player %d name:",i+1);
        scanf("%s",players[i].player_name);
        if(choice == 1){
            printf("Since %s is RED, %s is GREEN.\n\n",players[i-1].player_name,players[i].player_name);
            players[i].player_color = GREEN;
        }else if(choice == 2){
            printf("Since %s is GREEN, %s is RED.\n\n",players[i-1].player_name,players[i].player_name);
            players[i].player_color = RED;
        }else{
            while(choice!=1 && choice!=2){
                printf("(1)RED or (2)GREEN\nPlease choose your colour:");
                scanf("\n%d",&choice);
                switch (choice){
                    case 1:
                        players[i].player_color = RED;
                        printf("%s is RED.\n\n",players[i].player_name);
                        break;
                    case 2:
                        players[i].player_color = GREEN;
                        printf("%s is GREEN.\n\n",players[i].player_name);
                        break;
                    default:
                        printf("Please only enter 1 or 2.\n\n");
                }
            }
        }
    }
}

//Set Invalid Squares (where it is not possible to place stacks)
void set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
}

//Set squares with a RED piece
void set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

