#include "const.h"
const unsigned char maze_option[24][4] = {
        {N,W,S,E},{N,W,E,S},{N,S,W,E},{N,S,E,W},
        {N,E,W,S},{N,E,S,W},{W,N,S,E},{W,N,E,S},
        {W,S,N,E},{W,S,E,N},{W,E,N,S},{W,E,S,N},
        {S,N,W,E},{S,N,E,W},{S,W,N,E},{S,W,E,N},
        {S,E,N,W},{S,E,W,N},{E,N,W,S},{E,N,S,W},
        {E,W,N,S},{E,W,S,N},{E,S,N,W},{E,S,W,N},
};

const char maze_position[][2] = {
        {NO_EXIST, NO_EXIST},
        {0, 1},         // east
        {1, 0},         // south
        {NO_EXIST, NO_EXIST},
        {0,-1},         // west
        {NO_EXIST, NO_EXIST},
        {NO_EXIST, NO_EXIST},
        {NO_EXIST, NO_EXIST},
        {-1,0}          // north
};

const char maze_opposite[] = { NO_EXIST, W, N, NO_EXIST, E, NO_EXIST, NO_EXIST, NO_EXIST, S };
const char maze_path[] = { NO_EXIST, PATH_E, PATH_S, NO_EXIST, PATH_W, NO_EXIST, NO_EXIST, NO_EXIST, PATH_N };
const char maze_arrow[] = {'e','s','w','n'};

/* arg_opt */
struct option long_options[] = {
        {"width", required_argument, 0, 'w'},
        {"length", required_argument, 0, 'l'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"difficulty", required_argument, 0, 'd'},
        {"preview", no_argument, 0, 'p'},
        {"output", required_argument, 0, 'o'},
        {"input", required_argument, 0, 'i'},
        {"save", required_argument, 0, 's'},
        {"key", required_argument, 0, 'k'},
};
const char *optstring = "w:l:hvd:po:i:s:k";
unsigned char arg_opt[] = {
        10,     // default_width
        10,     // default_length
        0,      // default_no_help_info
        0,      // default_no_version_info
        1,      // default_difficulty
        1,      // default_preview
        0,      // default_no_output
        0,      // default_no_input
        0,      // default_no_save
        0       // default_no_key
};
char arg_opt_file[][50] = {
        "maze.svg",
        "maze.mz",
        "maze.mz"
};