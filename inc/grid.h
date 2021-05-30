#ifndef MAZE_GRID_H
#define MAZE_GRID_H

#define _GRID_SIZE int
#define _GRID_TYPE unsigned char
typedef struct _Grid {
    _GRID_SIZE wid;
    _GRID_SIZE len;
    _GRID_SIZE start_y;
    _GRID_SIZE start_x;
    _GRID_SIZE exit_y;
    _GRID_SIZE exit_x;
    _GRID_TYPE **G;
}Grid;

Grid* init_grid(int wid, int len);
void  set_start(int y, int x, Grid *g);
void  set_exit(int y, int x, Grid *g);
void  destory_grid(Grid *g);
void  print_grid(const Grid *g);

#endif