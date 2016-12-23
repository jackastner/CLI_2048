#ifndef GAMELOGIC_H
#define GAMELOGIC_H

//The standard 2048 board is 4x4. These macros can be modified for different
//board sizes
#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4

//Cardinal enumeration is used only when sliding the tiles in a direction.
//    NORTH
//WEST     EAST
//    SOUTH
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Cardinal;

//Each index of this array holds the value of one tile
static unsigned short game_board[BOARD_WIDTH][BOARD_HEIGHT];
static int score;   //used to track the points earned by the player
static int changed; //indicates if the board state has changed since last check

void init_game();
void slide(Cardinal dir);
int game_score();
unsigned short get_tile(int r, int c);

static void slide_north();
static void slide_east();
static void slide_south();
static void slide_west();

static void slide_tile_north();
static void slide_tile_east();
static void slide_tile_south();
static void slide_tile_west();

static int try_merge(int r0, int c0, int r1, int c1);
static void bound_check(int r, int c);
static void spawn_tile();

#endif
