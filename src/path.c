#include <stdio.h>
#include "const.h"
#include "grid.h"
#include "maze.h"
int find_path(int y, int x, Grid *g) {
    // find the exit.
    if (y==g->exit_y && x==g->exit_x) {
        return 1;
    }
    // reserve the VISIT flag as a new VIIST flag.
    g->G[y][x] &= ~VISIT;

    // go randomly.
    unsigned char is_find = 0;
    const unsigned char *opt = maze_option[random(24)];
    int ny, nx;
    for (int i = 0; i < 4 && !is_find; i++) {
        ny = y + maze_position[opt[i]][0], nx = x + maze_position[opt[i]][1];
        // overflow.
        if (ny>=g->wid || nx>=g->len || ny<0 || nx<0) continue;

        if ((g->G[y][x]&opt[i]) && (g->G[ny][nx]&VISIT)) {
            // set path flag.
            g->G[y][x] |= PATH;
            g->G[y][x] |= maze_path[opt[i]];
            is_find = find_path(ny, nx, g);
        }
        if(!is_find) {
            // failed, clear path.
            g->G[y][x] &= ~PATH;
            g->G[y][x] &= ~PATH_INFO;
        }
    }
    return is_find;
}

void print_path(int y, int x, const Grid *g) {
    while (y!=g->exit_y || x!=g->exit_x){
        unsigned char direct = (g->G[y][x]&PATH_INFO)>>4;
        printf("%c",maze_arrow[direct]);
        y += maze_position[1<<direct][0]; x += maze_position[1<<direct][1];
    }
    printf("\n");
}