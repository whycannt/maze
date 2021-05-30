#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "grid.h"

Grid* init_grid(int wid, int len) {
    Grid *g = malloc(sizeof(Grid));
    g->wid = wid; g->len = len;
    // Default startpoint and exit.
    g->start_y = 0; g->start_x = 0;
    g->exit_y = wid - 1; g->exit_x = len - 1;

    g->G = malloc(sizeof(_GRID_TYPE*) * wid);
    for (int i = 0; i < wid; i++) {
        g->G[i] = malloc(sizeof(_GRID_TYPE) * len);
        memset(g->G[i], 0, len);
    }
    return g;
}

void set_exit(int y, int x, Grid *g) {
    g->exit_y = y;
    g->exit_x = x;
}

void set_start(int y, int x, Grid *g) {
    g->start_y = y;
    g->start_x = x;
}

void destory_grid(Grid *g) {
    for (int i = 0; i < g->wid; i++) {
        free(g->G[i]);
    }
    free(g->G); free(g);
    return ;
}

void print_grid(const Grid *g) {
    for (int i = 0; i < g->wid; i++) {
        for (int j = 0; j < g->len; j++) {
            printf("%d ", g->G[i][j]);
        }
        printf("\n");
    }
}