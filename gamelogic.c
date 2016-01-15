#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "gamelogic.h"

void init_game(){
    score = 0;
    changed = 1;

    struct timeval t;
    gettimeofday(&t,NULL);
    srand(t.tv_usec);

    spawn_tile();
}

void spawn_tile(){
    if(changed){
        int r,c;

        int full = 1;
        for(r = 0; r < BOARD_HEIGHT; r++){
            for(int c = 0; c < BOARD_WIDTH; c++){
                full &= game_board[r][c];   
            }
        }

        if(!full){
            do{
                r = random()%BOARD_HEIGHT;
                c = random()%BOARD_WIDTH;
            }while(game_board[r][c] != 0);

            game_board[r][c] = 1<<(random()%2+1);
        }
        changed = 0;
    }
}

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

int game_score(){
    return score;
}

unsigned short get_tile(int r, int c){
    bound_check(r,c);
    return game_board[r][c];
}

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


static int try_merge(int r0, int c0, int r1, int c1){
    bound_check(r0,c0);
    bound_check(r1,c1);

    int v0 = game_board[r0][c0];
    int v1 = game_board[r1][c1];

    if(v0 == 0 || v1 == 0 || v0 == v1){
        if(v0!=0){
            changed = 1;
        }

        game_board[r1][c1] = v0 + v1;
        game_board[r0][c0] = 0;
        if(v0 == v1){
            score += (v0 + v1);
            return 1;
        }
        return 0;
    } else {
        return 1;
    }
}

static void bound_check(int r, int c){
    if(r < 0 || c < 0 || r >=  BOARD_HEIGHT || c >= BOARD_WIDTH){
        fprintf(stderr, "Index out of bounds at row %d and collumn %d\n",r,c);
    }
}
