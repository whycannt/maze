#ifndef MAZE_FILE_H
#define MAZE_FILE_H
#include "grid.h"

#define LINE_COLOR "black"
#define LINE_WIDTH "2"
#define LINE_LENGTH 30
#define DEFAULT_LEN 14

#define BUFFER_SIZE 81920
#define STRING(s) s
#define SVG_PREFIX(COLOR,WIDTH) "<?xml version=\"1.0\"?><svg width=\"500%\" height=\"500%\" xmlns=\"http://www.w3.org/2000/svg\" " \
"style=\"stroke:"STRING(COLOR)";stroke-width:"STRING(WIDTH)"\"><path d=\"M0 0 "
#define SVG_SUFFIX "\"/></svg>"

extern char svg_path[BUFFER_SIZE];
extern int  svg_len;

void save_file(const char *file, const Grid *g);
Grid* load_file(const char *file);
//void save_svg(const char *file, const Grid *g);
void out_svg(const char *file, const Grid *g);

#endif