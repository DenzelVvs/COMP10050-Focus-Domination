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
            }else if(board[x1-1][y1-1].num_pieces < abs(x1-x2) || board[x1-1][y1-1].num_pieces < abs(y1-y2)){
                printf("Invalid move. Displacement of a piece should be less than/equal to the number of pieces in the stack.\n");
            }else if(board[x2-1][y2-1].stack==NULL || board[x2-1][y2-1].stack->p_color != players[i].player_color){
                sameColour2=false;
            }else if(board[x2-1][y2-1].stack->p_color == players[i].player_color){
                printf("You can't capture a piece that matches your colour.\nPlease try again.\n");
            }
        }

        board[--x2][--y2].num_pieces += board[--x1][--y1].num_pieces;
        board[x2][y2].stack = push(board[x1][y1].stack,board[x2][y2].stack,board[x1][y1].num_pieces);
        set_empty(&board[x1][y1]);

        print_board(board);

        printList(board[x2][y2].stack);
        printf("\n");

        if(players[i].captured == 18){
            noMove = true;
        }

        i++;
        sameColour1=false;
        sameColour2=true;
    }



}

piece* push(piece *p1,piece *top, int p1_num_pieces)
{
    piece *sPtr = NULL;
    piece *newTop = NULL;

    for(int i=0;i<p1_num_pieces;i++){
        piece *newNode = malloc(sizeof(piece)); //creates new node

        if(newNode == NULL){ //checks if memory has been allocated
            printf("Memory not allocated.\n");
            exit(1);
        }else{
            newNode->p_color = p1->p_color; //copies value from array element to new node
            newNode->next = NULL;

            piece *previousPtr = NULL;
            piece *currentPtr = sPtr;

            //this loop goes though the list until it reaches the end
            while ( currentPtr != NULL ) {
                previousPtr = currentPtr;
                currentPtr = currentPtr->next;
            }

            if(i==p1_num_pieces-1 && previousPtr != NULL){
                previousPtr->next = newNode;
                newNode->next = top;
            }else if(i==p1_num_pieces-1){
                //previousPtr->next = newNode;
                newNode->next = top;
            }else if ( previousPtr == NULL ) { //this is for inserting a new node at the start of the list
                newNode->next = sPtr;
                sPtr = newNode;
            }else{ //this is for inserting a node at the end of the list
                previousPtr->next = newNode;
                newNode->next = currentPtr;
            }
        }

        p1 = p1->next;
        if(i==0){
            newTop = newNode;
        }
    }

    return newTop;
}

void printList( piece *top )
{
    /* if list is empty */
    if ( top == NULL ) {
        printf( "List is empty.\n\n" );
    } /* end if */
    else {
        printf( "The list is:\n" );

        /* while not the end of the list */
        while ( top != NULL ) {
            if(top->p_color==0){
                printf("RED --> ");
            }else if(top->p_color==1){
                printf( "GREEN --> ");
            }
            top = top->next;
        } /* end while */

        printf( "NULL\n\n" );
    } /* end else */
} /* end function printList */