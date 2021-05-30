#ifndef MAZE_H
#define MAZE_H
#include "grid.h"
#include "file.h"
#include "preview.h"
#include "path.h"
#include "const.h"
int random(int right);
void  crave_passage(Grid *g);
void  straight_line(int wlow, int whight, int llow, int lhight, Grid *g);
#endif