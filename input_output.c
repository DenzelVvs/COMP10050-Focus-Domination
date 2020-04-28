//
// Created by Denzel on 12/04/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_output.h"

int X1=0,Y1=0,X2=0,Y2=0;    //global variables

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    int x=1;
    printf("%36s\n","****** The Board ******");     //makes sure that it is centred

    //loop goes through every square and prints corresponding data
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)   //checks if square is empty
                    printf("|     ");
                else{
                    if (board[i][j].stack->p_color == GREEN)    //checks if square has a green piece
                        printf("| G-%d ",board[i][j].num_pieces);
                    else printf("| R-%d ",board[i][j].num_pieces);
                }
            }
            else{
                printf("|  -  ");   //this is for invalid squares
            }
        }
        printf("|  %d\n",x++);      //this is for the numbers at the side (row number)
    }

    //this loops is for the numbers at the bottom (column number)
    for(int i=0;i<BOARD_SIZE;i++){
        printf("   %d  ",i+1);
    }
    printf("\n");
}

player play_game(player players[PLAYERS_NUM],square board [BOARD_SIZE][BOARD_SIZE])
{
    int i=0,choice=0;
    bool noMove=false;
    piece *newPiece;

    //this loop allows the game to continue until noMove is true (no more moves left)
    while(!noMove){
        if(i==2){   //this is to make sure the players switch after each loop
            i-=2;
        }

        printf("\n%s's turn to move. ",players[i].player_name);  //prompts player to move

        //This gives the player a choice of moving pieces or placing reserves if they have reserves
        if(players[i].reserve > 0){
            printf("(1)Make a move or (2)Use a reserve piece?\n");

            //keeps looping until player enters 1 or 2
            while(choice!=1 && choice!=2){
                scanf("%d",&choice);
                if(choice!=1 && choice!=2){
                    printf("Please only enter either 1 or 2.\n");
                }
            }

            if(choice == 1){
                make_move(players[i],board);    //calls function to move a piece
                //this subtracts board_piece count by one as one when destination is not NULL
                if(i==0 && board[X2-1][Y2-1].stack!=NULL){
                    players[i+1].board_pieces--;
                }else if(i==1 && board[X2-1][Y2-1].stack!=NULL){
                    players[i-1].board_pieces--;
                }

                board[--X2][--Y2].num_pieces += board[--X1][--Y1].num_pieces;   //adds the num pieces of two stacks
                //joins to stacks together
                board[X2][Y2].stack = push(board[X1][Y1].stack,board[X2][Y2].stack,board[X1][Y1].num_pieces);
                set_empty(&board[X1][Y1]);  //empties initial square
            }else if(choice == 2){
                newPiece = place_reserve(players[i],board);    //calls function to place a reserve back on board
                //this subtracts board_piece count by one as one when destination is not NULL
                if(i==0 && board[X2-1][Y2-1].stack!=NULL){
                    players[i+1].board_pieces--;
                }else if(i==1 && board[X2-1][Y2-1].stack!=NULL){
                    players[i-1].board_pieces--;
                }
                --X2;
                --Y2;
                //moves piece on board
                board[X2][Y2].stack = push(newPiece,board[X2][Y2].stack,1);
                board[X2][Y2].num_pieces++;         //increases num_pieces counter by one
                players[i].reserve--;               //subtracts player reserve by one
                players[i].board_pieces++;          //increases piece count on board by one
            }

        }else{
            make_move(players[i],board);    //calls function move a piece

            //this subtracts board_piece count by one as one
            if(i==0 && board[X2-1][Y2-1].stack!=NULL){
                players[i+1].board_pieces--;
            }else if(i==1 && board[X2-1][Y2-1].stack!=NULL){
                players[i-1].board_pieces--;
            }

            board[--X2][--Y2].num_pieces += board[--X1][--Y1].num_pieces;   //adds the num pieces of two stacks
            //joins to stacks together
            board[X2][Y2].stack = push(board[X1][Y1].stack,board[X2][Y2].stack,board[X1][Y1].num_pieces);
            set_empty(&board[X1][Y1]);  //empties initial square
        }

        //checks if stack is greater than 5
        if(board[X2][Y2].num_pieces > 5){
            players[i] = count_captured(board[X2][Y2].stack,players[i]);    //counts number of reserves/captured
            board[X2][Y2].stack = remove_piece(board[X2][Y2].stack);        //makes stack size equal 5
            board[X2][Y2].num_pieces = 5;
        }

        print_board(board);     //prints contents of board

        //displays the number of reserves/captured of player
        if(i==0){
            printf("%s's Reserve Pieces: %u\n",players[i+1].player_name,players[i+1].reserve);
            printf("%s's Captured Pieces: %u\n",players[i+1].player_name,players[i+1].captured);
        }else if(i==1){
            printf("%s's Reserve Pieces: %u\n",players[i-1].player_name,players[i-1].reserve);
            printf("%s's Captured Pieces: %u\n",players[i-1].player_name,players[i-1].captured);
        }

        //checks for winning condition (no more pieces left to move)
        if(i==0){
            if(players[i+1].board_pieces == 0){
                noMove = true;
                printf("\nNo moves left for %s.",players[i+1].player_name);
            }
        }else if(i==1){
            if(players[i-1].board_pieces == 0){
                noMove = true;
                printf("\nNo moves left for %s.",players[i-1].player_name);
            }
        }
        i++;
        choice = 0;
    }

    //this is to make sure correct player is returned
    if(i==0){
        i++;
    }else if(i==1){
        i--;
    }
    return players[i];
}

void make_move(player Player,square board[BOARD_SIZE][BOARD_SIZE])
{
    bool sameColour1=false, sameColour2=true;

    //keeps looping until chosen piece has same colour as player and rules are followed
    while(!sameColour1){
        printf("\nEnter the coordinates of the piece to move:\nX1:");   //prompts pick a piece
        scanf("%d",&X1);
        printf("Y1:");
        scanf("%d",&Y1);

        if(X1<1 || X1>8 || Y1<1 || Y1>8){       //checks if coordinates goes out of bounds
            printf("Invalid coordinates. Please try again.\n");
            printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
        }else if(board[X1-1][Y1-1].stack == NULL){      //checks if coordinates has a piece
            printf("You have not selected a piece.\nPlease try again.\n");
        }else if(board[X1-1][Y1-1].stack->p_color!=Player.player_color ){   //checks if the piece has same colour as player
            printf("You did not choose a piece that matches your colour.\n");
            printf("Please try again.\n");
        }else if(board[X1-1][Y1-1].stack->p_color==Player.player_color){    //returns true is same colour
            sameColour1=true;
        }
    }

    //keeps looping until chosen stack doesnt have same colour as player and rules are followed
    while(sameColour2){
        printf("\nEnter the coordinates of the square to be captured:\nX2:");   //picks a piece/stack
        scanf("%d",&X2);
        printf("Y2:");
        scanf("%d",&Y2);

        if(X2<1 || X2>8 || Y2<1 || Y2>8){       //checks if coordinates are out of bounds
            printf("Invalid coordinates. Please try again.\n");
            printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
        }else if(board[X2-1][Y2-1].type == INVALID){    //checks if destination is an invalid square
            printf("Invalid square. Please choose a valid square.\n");
        }else if(abs(X1-X2)>0 && abs(Y1-Y2)>0){     //checks if move is diagonal
            printf("Invalid move. You cannot move a piece/stack diagonally.\n");
        }else if(board[X1-1][Y1-1].num_pieces < abs(X1-X2) || board[X1-1][Y1-1].num_pieces < abs(Y1-Y2)){
            //checks if movement is less than stack size
            printf("Invalid move. Displacement of a piece should be less than/equal to the number of pieces in the stack.\n");
        }else if(board[X2-1][Y2-1].stack==NULL || board[X2-1][Y2-1].stack->p_color != Player.player_color){
            //checks if square is empty or has different colour
            sameColour2=false;
        }else if(board[X2-1][Y2-1].stack->p_color == Player.player_color){  //checks if piece has same colour
            printf("You can't capture a piece that matches your colour.\nPlease try again.\n");
        }
    }
}

piece* place_reserve(player Player,square board[BOARD_SIZE][BOARD_SIZE])
{
    bool sameColour2=true;
    piece *newPiece;

    newPiece = malloc(sizeof(piece));   //allots memory to newPiece

    if(newPiece == NULL){
        printf("Memory not allocated.\n");
        exit(1);
    }else if(Player.player_color == RED){   //assigns color to newPiece as same as players colour
        newPiece->p_color = RED;
    }else{
        newPiece->p_color = GREEN;
    }

    //keeps looping until chosen stack doesnt have same colour as player and rules are followed
    while(sameColour2){
        printf("\nEnter the coordinates of the square to be captured:\nX2:");   //enter coordinates to capture
        scanf("%d",&X2);
        printf("Y2:");
        scanf("%d",&Y2);

        if(X2<1 || X2>8 || Y2<1 || Y2>8){       //checks if coordinates are out of bounds
            printf("Invalid coordinates. Please try again.\n");
            printf("Valid coordinates for x: 1-8\nValid coordinates for y: 1-8\n");
        }else if(board[X2-1][Y2-1].type == INVALID){    //checks if square is invalid
            printf("Invalid square. Please choose a valid square.\n");
        }else if(board[X2-1][Y2-1].stack==NULL || board[X2-1][Y2-1].stack->p_color != Player.player_color){
            //checks if square is empty or has different colour as player
            sameColour2=false;
        }else if(board[X2-1][Y2-1].stack->p_color == Player.player_color){  //checks if piece has same colour as player
            printf("You can't capture a piece that matches your colour.\nPlease try again.\n");
        }
    }

    return newPiece;
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

            if(i==p1_num_pieces-1 && previousPtr != NULL){  //connects copied list to top
                previousPtr->next = newNode;
                newNode->next = top;
            }else if(i==p1_num_pieces-1){   //connects copied node to top
                newNode->next = top;
            }else if ( previousPtr == NULL ) { //this is for inserting a new node at the start of the list
                newNode->next = sPtr;
                sPtr = newNode;
            }else{ //this is for inserting a node at the end of the list
                previousPtr->next = newNode;
                newNode->next = currentPtr;
            }
        }

        p1 = p1->next;  //moves to next node of the list to be copied
        if(i==0){   //stores first node of the list
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

    //moves through first five node in the list
    while ( i<5 ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
        i++;
    }

    //cuts the list after five nodes (last node points to NULL)
    if(previousPtr!=NULL){
        previousPtr->next = NULL;
    }

    //moves through the remaining nodes and free up memory
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

    //goes through first five nodes
    while ( i<5 ) {
        currentPtr = currentPtr->next;
        i++;
    }

    while(currentPtr !=NULL){
        if(currentPtr->p_color == Player.player_color){ //if same colour as player, increase reserve
            Player.reserve++;
        }else{
            Player.captured++;  //if different colour as player, increase captured
        }

        currentPtr = currentPtr->next;  //moves to next node
    }

    return Player;
}