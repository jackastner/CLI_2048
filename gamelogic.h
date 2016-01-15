#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Cardinal;

static unsigned short game_board[BOARD_WIDTH][BOARD_HEIGHT];
static int score;
static int changed;

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
