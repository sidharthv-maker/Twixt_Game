#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int cache[MAX][MAX];
Link links[MAX_LINKS];
int link_count = 0;
int kdist[8][2] = {{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
int coords(int ax, int ay, int bx, int by, int cx, int cy) {
    long long v = (long long)(bx - ax) * (cy - ay) - (long long)(by - ay) * (cx - ax);
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}
int func(int ax, int ay, int bx, int by, int cx, int cy) {
    int minx, maxx, miny, maxy;
    if (ax < bx) {
        minx = ax;
        maxx = bx;
    } else {
     minx = bx;
        maxx = ax;
    }
    if (ay < by) {
        miny = ay;
        maxy = by;
    } else {
        miny = by;
        maxy = ay;
    }
    if (cx < minx || cx > maxx) return 0;
    if (cy < miny || cy > maxy) return 0;
    return 1;
}
int intersection(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) {
    int o1 = coords(ax, ay, bx, by, cx, cy);
    int o2 = coords(ax, ay, bx, by, dx, dy);
    int o3 = coords(cx, cy, dx, dy, ax, ay);
    int o4 = coords(cx, cy, dx, dy, bx, by);
    if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 &&
        ((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
        ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0))) {
        return 1;
    }
    if (o1 == 0 && func(ax, ay, bx, by, cx, cy)) return 1;
    if (o2 == 0 && func(ax, ay, bx, by, dx, dy)) return 1;
    if (o3 == 0 && func(cx, cy, dx, dy, ax, ay)) return 1;
    if (o4 == 0 && func(cx, cy, dx, dy, bx, by)) return 1;
    return 0;
}
int crosses_existing(int r1, int c1, int r2, int c2) {
    for (int i = 0; i < link_count; i++) {
        int a1 = links[i].r1;
        int b1 = links[i].c1;
        int a2 = links[i].r2;
        int b2 = links[i].c2;
        if ((a1 == r1 && b1 == c1) || (a1 == r2 && b1 == c2) ||
            (a2 == r1 && b2 == c1) || (a2 == r2 && b2 == c2)) {
            continue;
        }
        if (intersection(r1, c1, r2, c2, a1, b1, a2, b2)) {
            return 1;
        }
    }
    return 0;
}
void init_game(status *g) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            g->board[i][j] = empty;
    g->current = redturn;
    g->total = 0;
    link_count = 0;
}
Cell cell_for_player(turn p) {
    if (p == redturn) {
        return cred;
    } else {
        return cblack;
    }
}
void switch_player(status *g) {
    if (g->current == redturn) {
        g->current = blackturn;
    } else {
        g->current = redturn;
    }
}
void print_board(status *g) {
    printf("   ");
    for (int j = 0; j < MAX; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    for (int i = 0; i < MAX; i++) {
        printf("%2d ", i);
        for (int j = 0; j < MAX; j++) {
            char ch;
            if (g->board[i][j] == cred) {
                ch = 'R';
            } else if (g->board[i][j] == cblack) {
                ch = 'B';
            } else {
                int on_top_or_bottom = (i == 0 || i == MAX - 1);
                int on_left_or_right = (j == 0 || j == MAX - 1);
                int is_corner = on_top_or_bottom && on_left_or_right;

                if (is_corner) {
                    ch = ' ';
                } else if (on_top_or_bottom) {
                    ch = '-';
                } else if (on_left_or_right) {
                    ch = '|';
                } else {
                    ch = '.';
                }
            }

            printf(" %c ", ch);
        }
        printf("\n");
    }
}
int check_link(status *g, int r1, int c1, int r2, int c2, turn p) {
    for (int i = 0; i < link_count; i++) {
        if (links[i].player != p) continue;
        if ((links[i].r1 == r1 && links[i].c1 == c1 &&
             links[i].r2 == r2 && links[i].c2 == c2) ||
            (links[i].r1 == r2 && links[i].c1 == c2 &&
             links[i].r2 == r1 && links[i].c2 == c1)) {
            return 1;
        }
    }
    return 0;
}
int link_check(status *g, int r1, int c1, int r2, int c2, turn p) {
    if (r1 < 0 || r1 >= MAX || c1 < 0 || c1 >= MAX) return 0;
    if (r2 < 0 || r2 >= MAX || c2 < 0 || c2 >= MAX) return 0;
    Cell pc = cell_for_player(p);
    if (g->board[r1][c1] != pc || g->board[r2][c2] != pc) return 0;
    int dr = r2 - r1;
    int dc = c2 - c1;
    int adr;
    if (dr < 0) adr = -dr;
    else adr = dr;
    int adc;
    if (dc < 0) adc = -dc;
    else adc = dc;
    if (!((adr == 1 && adc == 2) || (adr == 2 && adc == 1))) return 0;
    if (check_link(g, r1, c1, r2, c2, p)) return 0;
    if (crosses_existing(r1, c1, r2, c2)) return 0;
    return 1;
}
void print_link(status *g, int r, int c) {
    turn p = g->current;
    char *pname;
    if (p == redturn) {
        pname = "Red";
    } else {
        pname = "Black";
    }
    for (int k = 0; k < 8; k++) {
        int nr = r + kdist[k][0];
        int nc = c + kdist[k][1];
        if (link_check(g, r, c, nr, nc, p)) {
            if (link_count < MAX_LINKS) {
                links[link_count].r1 = r;
                links[link_count].c1 = c;
                links[link_count].r2 = nr;
                links[link_count].c2 = nc;
                links[link_count].player = p;
                link_count++;
            }
            printf("Link formed for %s between (%d, %d) and (%d, %d)\n",
                   pname, r, c, nr, nc);
        }
    }
}
void recursion(status *g, int r, int c, turn p) {
    cache[r][c] = 1;
    for (int k = 0; k < 8; k++) {
        int nr = r + kdist[k][0];
        int nc = c + kdist[k][1];
        if (nr < 0 || nr >= MAX || nc < 0 || nc >= MAX) continue;
        if (cache[nr][nc]) continue;
        if (check_link(g, r, c, nr, nc, p)) {
            recursion(g, nr, nc, p);
        }
    }
}
int rwin_check(status *g) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            cache[i][j] = 0;
    for (int j = 0; j < MAX; j++) {
        if (g->board[0][j] == cred) {
            recursion(g, 0, j, redturn);
        }
    }
    for (int j = 0; j < MAX; j++) {
        if (g->board[MAX-1][j] == cred && cache[MAX-1][j]) {
            return 1;
        }
    }
    return 0;
}
int bwin_check(status *g) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            cache[i][j] = 0;
    for (int i = 0; i < MAX; i++) {
        if (g->board[i][0] == cblack) {
            recursion(g, i, 0, blackturn);
        }
    }
    for (int i = 0; i < MAX; i++) {
        if (g->board[i][MAX-1] == cblack && cache[i][MAX-1]) {
            return 1;
        }
    }
    return 0;
}
int win_con(status *g, turn p) {
    if (p == redturn) {
        return rwin_check(g);
    } else {
        return bwin_check(g);
    }
}