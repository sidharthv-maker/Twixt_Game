#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int main() {
    status game;
    init_game(&game);
    while (1) {
        print_board(&game);
        printf("Current turn: ");
        if (game.current == redturn) {
            printf("Red(R)\n");
        } else {
            printf("Black(B)\n");
        }
        printf("Enter row col (or -1 -1 to quit): ");
        int r, c;
        if (scanf("%d %d", &r, &c) != 2) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        if (r == -1 && c == -1) {
            printf("Game exited. Thank you for playing!\n");
            break;
        }
        if (r < 0 || r >= MAX || c < 0 || c >= MAX) {
            printf("Out of bounds! Try again.\n");
            continue;
        }
        if ((r == 0 || r == MAX - 1) && (c == 0 || c == MAX - 1)) {
            printf("You cannot place on the corners.Try again\n");
            continue;
        }
        if (game.current == blackturn && (r == 0 || r == MAX - 1)) {
            printf("Black cannot place in the first or last row.Try again\n");
            continue;
        }
        if (game.current == redturn && (c == 0 || c == MAX - 1)) {
            printf("Red cannot place in the first or last column.Try again.");
            continue;
        }
        if (game.board[r][c] != empty) {
            printf("Cell occupied!Try again\n");
            continue;
        }
        game.board[r][c] = cell_for_player(game.current);
        game.total++;
        print_link(&game, r, c);
        if (win_con(&game, game.current)) {
            print_board(&game);
            if (game.current == redturn) {
                printf("Red");
            } else {
                printf("Black");
            }
            printf(" wins!\n");
            break;
        }
        switch_player(&game);
    }
    return 0;
}