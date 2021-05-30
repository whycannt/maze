#ifndef MAZE_CONST_H
#define MAZE_CONST_H
#include <getopt.h>
#define ARG_OPT_WIDTH           0
#define ARG_OPT_LENGTH          1
#define ARG_OPT_HELP            2
#define ARG_OPT_VERSION         3
#define ARG_OPT_DIFFICULTY      4
#define ARG_OPT_PREVIEW         5
#define ARG_OPT_OUTPUT          6
#define ARG_OPT_INPUT           7
#define ARG_OPT_SAVE            8
#define ARG_OPT_KEY             9

#define ARG_OPT_OUTPUT_FILE     0
#define ARG_OPT_INPUT_FILE      1
#define ARG_OPT_SAVE_FILE       2

#define VERSION_INFO "1.0-beta"
#define HELP_INFO \
    printf("Version:  %s\n",VERSION_INFO);\
    printf("Options:\n");\
    printf("You can use the short option with its initial.\n");\
    printf("%-20sDisplay this information.\n","--help");\
    printf("%-20sDisplay the tool version information.\n","--version");\
    printf("%-20sSpecify the width of maze.\n","--width");\
    printf("%-20sSpecify the length of maze.\n","--length");\
    printf("%-20sChoose the difficulty.\n","--difficulty");\
    printf("%-20sOutput the maze into a image file.\n","--output");\
    printf("%-20sSave the maze into a .mz file.\n","--save");\
    printf("%-20sInput a .mz file to generate.\n","--input");\
    printf("%-20sShow the path.\n","--key");\
    printf("For bug or issues reporting, please visit\n  <https://www.github.com/whycannt/maze>\n")

#define NO_EXIST -1
/* Indicator */
#define HI_B   0xf0
#define LOW_B  0x0f
#define VISIT  0x80
#define PATH   0x40

/* Path indicator */
#define PATH_INFO 0x30
#define PATH_E 0x00
#define PATH_S 0x10
#define PATH_W 0x20
#define PATH_N 0x30

/* Wall info */
#define E 0x01
#define S 0x02
#define W 0x04
#define N 0x08


/* preview */
#define HORIZON "__"
#define VERTICAL "|"
#define OPEN "  "

extern const unsigned char maze_option[24][4];
extern const char maze_position[][2];
extern const char maze_opposite[];
extern const char maze_path[];
extern const char maze_arrow[];
extern struct option long_options[];
extern const char *optstring;
extern unsigned char arg_opt[];
extern char arg_opt_file[][50];
#endif