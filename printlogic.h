#ifndef PRINTLOGIC_H
#define PRINTLOGIC_H

    
static struct termios oldt, newt;

void init_print();
void destroy_print();
void print_game();
void setColorFor(int tile);

#endif
