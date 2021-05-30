#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "maze.h"
#include "const.h"

void bfs(int y, int x, Grid *g);
int  random_range(int left, int right);

int random(int right) {
    srand((unsigned)time(0) + rand());
    return rand() % right;
}

int random_range(int left, int right) {
    srand((unsigned)time(0) + rand());
    return rand() % (right-left+1) + left;
}

void crave_passage(Grid *g) {
    bfs(g->exit_y, g->exit_x, g);
    return ;
}

void bfs(int y, int x, Grid *g) {
    // set the grid visited
    g->G[y][x] |= VISIT;

    const unsigned char *opt = maze_option[random(24)];
    int nx, ny;
    for (int i = 0; i < 4; i++) {
        ny = y + maze_position[opt[i]][0], nx = x + maze_position[opt[i]][1];

        if (nx>= 0 && nx<g->len && ny>=0 && ny<g->wid && !(g->G[ny][nx]&VISIT)) {
            // crave the passage between two cell
            g->G[y][x] |= opt[i];
            g->G[ny][nx] |= maze_opposite[opt[i]];
            // go ahead
            bfs(ny, nx, g);
        }
    }
}

void straight_line(int y_lo, int y_hi, int x_lo, int x_hi, Grid *g) {
    // check whether can be seperated in two ways?
    unsigned char horizon = y_hi >= (y_lo+2) ? 1 : 0;
    unsigned char vertical = x_hi >= (x_lo+2) ? 1 : 0;

    // decide which way to seperate it.
    unsigned char way = 0;
    if (vertical && horizon) {
        way = random(2);
    } else {
        way = vertical ? 1 : 0;
    }

    // define the seperating line.
    unsigned char line = 0;
    line = way ? random_range(x_lo+1,x_hi-1) : random_range(y_lo+1,y_hi-1);
    // "dig a hole" in the seperating line to connect the two parts.
    unsigned char pos = 0;
    pos = way ? random_range(y_lo,y_hi-1) : random_range(x_lo,x_hi-1);

    if (way) {  // vertical
        g->G[pos][line-1] |= E;
        g->G[pos][line] |= W;

        // seperate two parts and go ahead.
        if (line >= x_lo+2 || y_hi >= y_lo+2)
            straight_line(y_lo,y_hi,x_lo,line,g);
        if (x_hi >= line+2 || y_hi >= y_lo+2)
            straight_line(y_lo,y_hi,line,x_hi,g);
    }
    else {  // horizontal
        g->G[line-1][pos] |= S;
        g->G[line][pos] |= N;

        // do the same before.
        if (line >= y_lo+2 || x_hi >= x_lo+2)
            straight_line(y_lo,line,x_lo,x_hi,g);
        if (y_hi >= line+2 || x_hi >= x_lo+2)
            straight_line(line,y_hi,x_lo,x_hi,g);
    }
}