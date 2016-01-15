#include "printlogic.h"
#include "gamelogic.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    init_game();
    init_print();
    atexit(destroy_print);

    print_game();
    char input;
    while((input = getchar())!=4){

        switch(input){
            case 'w':
                slide(NORTH);
                break;
            case 'd':
                slide(EAST);
                break;
            case 's':
                slide(SOUTH);
                break;
            case 'a':
                slide(WEST);
                break;
        }
        print_game();
    }
}