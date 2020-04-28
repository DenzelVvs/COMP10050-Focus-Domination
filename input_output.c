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

int X1=0,Y1=0,X2=0,Y2=0;

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

player play_game(player players[PLAYERS_NUM],square board [BOARD_SIZE][BOARD_SIZE])
{
    int i=0,choice=0;
    bool noMove=false;

    while(!noMove){
        if(i==2){
            i-=2;
        }

        if(players[i].reserve > 0){
            printf("(1)Make a move or (2)Use a reserve piece?\n");

            while(choice!=1 && choice!=2){
                scanf("%d",&choice);
                if(choice!=1 && choice!=2){
                    printf("Please only enter either 1 or 2.\n");
                }
            }

            if(choice == 1){
                make_move(players[i],board);
            }else if(choice == 2){
                place_reserve(players[i],board);
                players[i].reserve--;
                players[i].board_pieces++;
            }

        }else{
            make_move(players[i],board);
        }

        if(i==0){
            players[i+1].board_pieces--;
        }else if(i==1){
            players[i-1].board_pieces--;
        }

        if(board[X2][Y2].num_pieces > 5){
            players[i] = count_captured(board[X2][Y2].stack,players[i]);
            board[X2][Y2].stack = remove_piece(board[X2][Y2].stack);
            board[X2][Y2].num_pieces = 5;
        }

        print_board(board);

        if(i==0){
            printf("%s's Reserve Pieces: %u\n",players[i+1].player_name,players[i+1].reserve);
            printf("%s's Captured Pieces: %u\n",players[i+1].player_name,players[i+1].captured);
        }else if(i==1){
            printf("%s's Reserve Pieces: %u\n",players[i-1].player_name,players[i-1].reserve);
            printf("%s's Captured Pieces: %u\n",players[i-1].player_name,players[i-1].captured);
        }

        printf("\n");
        printList(board[X2][Y2].stack);
        if(i==0){
            printf("%s %d\n",players[i].player_name,players[i].board_pieces);
            printf("%s %d\n",players[i+1].player_name,players[i+1].board_pieces);
        }else if(i==1){
            printf("%s %d\n",players[i-1].player_name,players[i-1].board_pieces);
            printf("%s %d\n",players[i].player_name,players[i].board_pieces);
        }


        if(i==0){
            if(players[i+1].board_pieces == 0){
                noMove = true;
                printf("\nNo moves left for %s.",players[i+1].player_name);
            }
        }else if(i==1){
            if(players[i-1].board_pieces == 0){
                noMove = true;
                printf("\nNo moves left for %s.\n\n",players[i-1].player_name);
            }
        }
        i++;
        choice = 0;
    }


    if(i==0){
        return players[i+1];
    }else if(i==1){
        return players[i-1];
    }
}

void make_move(player Player,square board[BOARD_SIZE][BOARD_SIZE])
{
    bool sameColour1=false, sameColour2=true;

    while(!sameColour1){
        printf("\n%s's turn to move.",Player.player_name);
        printf("\nEnter the coordinates of the piece to move:\nX1:");
        scanf("%d",&X1);
        printf("Y1:");
        scanf("%d",&Y1);

        if(X1<1 || X1>8 || Y1<1 || Y1>8){
            printf("Invalid coordinates. Please try again.\n");
            printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
        }else if(board[X1-1][Y1-1].stack == NULL){
            printf("You have not selected a piece.\nPlease try again.\n");
        }else if(board[X1-1][Y1-1].stack->p_color!=Player.player_color ){
            printf("You did not choose a piece that matches your colour.\n");
            printf("Please try again.\n");
        }else if(board[X1-1][Y1-1].stack->p_color==Player.player_color){
            sameColour1=true;
        }
    }

    while(sameColour2){
        printf("\nEnter the coordinates of the square to be captured:\nX2:");
        scanf("%d",&X2);
        printf("Y2:");
        scanf("%d",&Y2);

        if(X2<1 || X2>8 || Y2<1 || Y2>8){
            printf("Invalid coordinates. Please try again.\n");
            printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
        }else if(board[X2-1][Y2-1].type == INVALID){
            printf("Invalid square. Please choose a valid square.\n");
        }else if(board[X1-1][Y1-1].num_pieces < abs(X1-X2) || board[X1-1][Y1-1].num_pieces < abs(Y1-Y2)){
            printf("Invalid move. Displacement of a piece should be less than/equal to the number of pieces in the stack.\n");
        }else if(board[X2-1][Y2-1].stack==NULL || board[X2-1][Y2-1].stack->p_color != Player.player_color){
            sameColour2=false;
        }else if(board[X2-1][Y2-1].stack->p_color == Player.player_color){
            printf("You can't capture a piece that matches your colour.\nPlease try again.\n");
        }
    }

    board[--X2][--Y2].num_pieces += board[--X1][--Y1].num_pieces;
    board[X2][Y2].stack = push(board[X1][Y1].stack,board[X2][Y2].stack,board[X1][Y1].num_pieces);
    set_empty(&board[X1][Y1]);
}

void place_reserve(player Player,square board[BOARD_SIZE][BOARD_SIZE])
{
    bool sameColour2=true;
    piece *newPiece;

    newPiece = malloc(sizeof(piece));

    if(newPiece == NULL){
        printf("Memory not allocated.\n");
        exit(1);
    }else if(Player.player_color == RED){
        newPiece->p_color = RED;
    }else{
        newPiece->p_color = GREEN;
    }

    while(sameColour2){
        printf("\nEnter the coordinates of the square to be captured:\nX2:");
        scanf("%d",&X2);
        printf("Y2:");
        scanf("%d",&Y2);

        if(X2<1 || X2>8 || Y2<1 || Y2>8){
            printf("Invalid coordinates. Please try again.\n");
            printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
        }else if(board[X2-1][Y2-1].type == INVALID){
            printf("Invalid square. Please choose a valid square.\n");
        }else if(board[X2-1][Y2-1].stack==NULL || board[X2-1][Y2-1].stack->p_color != Player.player_color){
            sameColour2=false;
        }else if(board[X2-1][Y2-1].stack->p_color == Player.player_color){
            printf("You can't capture a piece that matches your colour.\nPlease try again.\n");
        }
    }

    --X2;
    --Y2;
    board[X2][Y2].stack = push(newPiece,board[X2][Y2].stack,1);
    board[X2][Y2].num_pieces++;

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

piece* remove_piece(piece *top)
{
    int i=0;
    piece *previousPtr = NULL;
    piece *currentPtr = top;

    while ( i<5 ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
        i++;
    }

    if(previousPtr!=NULL){
        previousPtr->next = NULL;
    }

    while(currentPtr !=NULL){
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
        free(previousPtr);
    }

    return top;
}

player count_captured(piece *top,player Player)
{
    int i=0;
    piece *currentPtr = top;

    while ( i<5 ) {
        currentPtr = currentPtr->next;
        i++;
    }

    while(currentPtr !=NULL){
        if(currentPtr->p_color == Player.player_color){
            Player.reserve++;
        }else{
            Player.captured++;
        }

        currentPtr = currentPtr->next;
    }

    return Player;
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