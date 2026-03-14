#ifndef TWIXT_H
#define TWIXT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 24 
#define MAX_LINKS 5000
extern int link_count;
extern int cache[MAX][MAX];
extern int kdist[8][2];
typedef enum {
    empty,
    cred,
    cblack
} Cell;
typedef enum {
    redturn,
    blackturn
} turn;
typedef struct {
    int r1, c1;
    int r2, c2;
    turn player;
} Link;
extern Link links[MAX_LINKS];
typedef struct {
    Cell board[MAX][MAX];
    turn current;
    int total;
} status;
void init_game(status *g);
Cell cell_for_player(turn p);
void switch_player(status *g);
void print_board(status *g);
int check_link(status *g, int r1, int c1, int r2, int c2, turn p);
void print_link(status *g, int r, int c);
void dfs(status *g, int r, int c, turn p);
int rwin_check(status *g);
int bwin_check(status *g);
int win_con(status *g, turn p);
#endif
