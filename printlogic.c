#include "gamelogic.h"
#include "printlogic.h"
#include <stdio.h>
#include <termios.h> 
#include <unistd.h>



void init_print(){
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void destroy_print(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}



void print_game(){
    int r,c,n;

    printf("\x1B[2J\x1B[H");

    printf(" ____   ___  _  _    ___  \n\
|___ \\ / _ \\| || |  ( _ ) \n\
  __) | | | | || |_ / _ \\ \n\
 / __/| |_| |__   _| (_) |\n\
|_____|\\___/   |_|  \\___/ \n");

    printf("┌────");
    for(n = 1; n < BOARD_WIDTH; n++){
        printf("┬────");
    }
    printf("┐\n");

    for(r = 0; r < BOARD_HEIGHT; r++){

        printf("│");
        for(c = 0; c < BOARD_WIDTH; c++){
            if(get_tile(r,c)){
                setColorFor(get_tile(r,c));
                printf("%4d",get_tile(r,c));
            } else {
                printf("%4s","");
            }
            printf("\x1b[39;49m│");
        }

        if(r != BOARD_HEIGHT - 1){
            printf("\n├────");
            for(n = 1; n < BOARD_WIDTH; n++){
                printf("┼────");
            }
            printf("┤");
        }
        printf("\n");
    }

    printf("\x1B[37m");
    printf("└────");
    for(c = 1; c < BOARD_WIDTH; c++){
        printf("┴────");
    }
    printf("┘\n");

    printf("Score: %d\n",game_score());
}

void setColorFor(int tile){
    if(tile <= 8){
        printf("\x1b[37m");
    } else if (tile <= 64) {
        printf("\x1b[36m");
    } else if (tile <= 512) {
        printf("\x1b[33m");
    } else {
        printf("\x1b[31m");
    }
}