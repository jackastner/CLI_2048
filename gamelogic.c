#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "gamelogic.h"

//Initialize global variables (deffined in "gamelogic.h" to needed values and
//seed the rng for use in the game
void init_game(){
    score = 0; //score starts at 0
    changed = 1; // In order for spawn_tile to do anything, changed must be 1

    //seed the rng
    struct timeval t;
    gettimeofday(&t,NULL);
    srand(t.tv_usec);

    //Spawn the first tile on the board
    spawn_tile();
}

//Place one tile on the board with value 2 or 4
//If the board state has not changed from the last call or, the board is full,
//nothing happens
void spawn_tile(){
    //check for change in state
    if(changed){
        int r,c;
 
        //check if the game board is full
        int full = 1;
        for(r = 0; r < BOARD_HEIGHT; r++){
            for(int c = 0; c < BOARD_WIDTH; c++){
                full &= game_board[r][c];   
            }
        }

        if(!full){
            //find an empty tile
            do{
                r = random()%BOARD_HEIGHT;
                c = random()%BOARD_WIDTH;
            }while(game_board[r][c] != 0);

            //place either 2 or 4 in this tile
            game_board[r][c] = 1<<(random()%2+1);
        }

        //record the change in game state
        changed = 0;
    }
}

//slide the tiles in the direction indicated by dir and spawn a new tile
void slide(Cardinal dir){
    if(dir == NORTH){
        slide_north();
    } else if (dir == EAST){
        slide_east();
    } else if (dir == SOUTH){
        slide_south();
    } else if (dir == WEST){
        slide_west();
    }
    spawn_tile();
}
 
//returns the value of the global variable score
int game_score(){
    return score;
}

//returns the value in a tile. Prints error message if out of bounds
unsigned short get_tile(int r, int c){
    bound_check(r,c);
    return game_board[r][c];
}
//The following set of functions are used to slide the board or a single tile
//in a cardinal direction. Order of itteration of the for loops is important in
//all cases so, it should  not be changed without some thought. To be honset I
//wrote this code a while ago and don't fully understand these functions.

static void slide_north(){
    int r,c;
    for(r = 0; r < BOARD_HEIGHT; r++){
        for(int c = 0; c < BOARD_WIDTH; c++){
            slide_tile_north(r,c);
        }
    }
}

static void slide_tile_north(int r, int c){
    int i;
    for(int i = r; i > 0; i--){
        if(try_merge(i,c,i-1,c)){
            break;
        }
    }
}

static void slide_east(){
    int r,c;
    for(int c = BOARD_WIDTH - 1; c >= 0; c--){
        for(r = 0; r < BOARD_HEIGHT; r++){
            slide_tile_east(r,c);
        }
    }
}

static void slide_tile_east(int r, int c){
    int i;
    for(int i = c; i < BOARD_WIDTH - 1; i++){
        if(try_merge(r,i,r,i+1)){
            break;
        }
    }
}

static void slide_south(){
    int r,c;
    for(r = BOARD_HEIGHT - 1; r >= 0; r--){
        for(int c = 0; c < BOARD_WIDTH; c++){
            slide_tile_south(r,c);
        }
    }
}

static void slide_tile_south(int r, int c){
    int i;
    for(int i = r; i < BOARD_HEIGHT - 1; i++){
        if(try_merge(i,c,i+1,c)){
            break;
        }
    }
}

static void slide_west(){
    int r,c;
    for(int c = 0; c < BOARD_WIDTH; c++){
        for(r = 0; r < BOARD_HEIGHT; r++){
            slide_tile_west(r,c);
        }
    }
}

static void slide_tile_west(int r, int c){
    int i;
    for(int i = c; i > 0; i--){
        if(try_merge(r,i,r,i-1)){
            break;
        }
    }
}


//Attempt to merge 2 tiles. A merge will suceed if one of the tiles is 0 or,
//the two tiles have the same value. 0 is returned on success; 1 on fail. 
//If the tile index is out of bounds an error is printed but computation
//continues
static int try_merge(int r0, int c0, int r1, int c1){
    //Check bounds. Only prints error does not exit
    bound_check(r0,c0);
    bound_check(r1,c1);

    //retrieve values of both tiles
    int v0 = game_board[r0][c0];
    int v1 = game_board[r1][c1];

    //if either is 0 or their values are equal, we can continue
    if(v0 == 0 || v1 == 0 || v0 == v1){
        //If the first tile is 0, the state after this opperation will not 
        //differ from the original state.
        if(v0!=0){
            changed = 1;
        }

        //The new value at r1 c1 is the sum, r0 c0 is 0.
        game_board[r1][c1] = v0 + v1;
        game_board[r0][c0] = 0;
        //the player gains score by combining non-0 tiles
        if(v0 == v1){
            score += (v0 + v1);
            return 1;
        }
        return 0;
    } else {
        return 1;
    }
}

//performs a bounds check based of the macros defined in gamelogic.h
//this function only prints an error message and does not exit
static void bound_check(int r, int c){
    if(r < 0 || c < 0 || r >=  BOARD_HEIGHT || c >= BOARD_WIDTH){
        fprintf(stderr, "Index out of bounds at row %d and collumn %d\n",r,c);
    }
}
