#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

int** loadBoard(void);
int solve(int**);
void saveBoard(int**);
int isNumInRow(int**, int, int);
int isNumInCol(int**, int, int);
int isNumInBox(int**, int, int, int);
int isPlaceValid(int**, int, int, int);

int main(void){
    int** board = loadBoard();
    double timespent = 0.0;
    if(solve(board)){
        printf("Solve successfully\n");
        saveBoard(board);
    }else{
        printf("Board cannot be solved\n");
    }
    return 0;
}

int** loadBoard(void){
    int* tile = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int** board = (int**)malloc(sizeof(int*)*SIZE);
    // point start of each row to board
    for(int i=0;i<SIZE;i++){
        board[i] = &tile[i*SIZE];
    }
    // input file existence check
    FILE *p = fopen("input.txt","r");
    if(!p){
        printf("Input file doesn't exist\n");
        exit(1);
    }
    // if fscanf != 1, the input file is not 81 interger separate by space.
    for(int i=0;i<SIZE*SIZE;i++){
        if(fscanf(p,"%d",&tile[i]) != 1){
            printf("Input file is not valid\n");
            exit(1);
        }
        if(tile[i]>9 || tile[i]<0){
            printf("Input file is not valid\n");
            exit(1);
        }
    }
    fclose(p);
    return board;
}

int solve(int** board){
    for(int i=0;i<SIZE;i++){    // transverse all tile
        for(int j=0;j<SIZE;j++){
            if(!board[i][j]){   // if the tile is empty
                for(int k=1; k<=SIZE; k++){ // try 1-9
                    if(isPlaceValid(board, i, j, k)){   // if valid
                        board[i][j] = k;                // place it
                        if(solve(board)){               // if can be recursive solve
                            return 1;                   // return true
                        }else{                          // else
                            board[i][j] = 0;            // reset the tile placed;
                        }
                    }
                }
                return 0;     // after try 1-9, all of them is not valid, return false.
            }
        }
    }
    return 1;                 // whole board is filled, return true.
}

void saveBoard(int** board){
    FILE *p = fopen("output.txt","w");

    if(!p){
        printf("Error!\n");
        exit(1);
    }

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++)
            fprintf(p,"%d ",board[i][j]);
        fprintf(p,"\n");
    }
    fclose(p);
}

int isNumInRow(int** board, int r, int k){
    for(int i=0;i<SIZE;i++){
        if(board[r][i]==k) return 1;
    }
    return 0;
}

int isNumInCol(int** board, int c, int k){
    for(int i=0;i<SIZE;i++){
        if(board[i][c]==k) return 1;
    }
    return 0;
}

int isNumInBox(int** board, int r, int c, int k){
    r -= (r % 3);
    c -= (c % 3);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            if(board[r+i][c+j]==k) return 1;
    }
    return 0;
}

int isPlaceValid(int** board, int r, int c, int k){
    return !isNumInRow(board,r,k) && !isNumInCol(board,c,k) && !isNumInBox(board,r,c,k);
}
