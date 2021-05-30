#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int main(int argc, char *argv[]) {
    Grid *g = NULL;
    int opt, option_index = 0;
    while ((opt = getopt_long(argc, argv, optstring,
                              long_options, &option_index)) != -1){
        switch (opt){
            case 'w': arg_opt[ARG_OPT_WIDTH]      = atoi(optarg); break;
            case 'l': arg_opt[ARG_OPT_LENGTH]     = atoi(optarg); break;
            case 'd': arg_opt[ARG_OPT_DIFFICULTY] = atoi(optarg); break;
            case 'h': HELP_INFO;exit(0); break;
            case 'k': arg_opt[ARG_OPT_KEY] = 1; break;
            case 'o': arg_opt[ARG_OPT_OUTPUT] = 1; strcpy(arg_opt_file[ARG_OPT_OUTPUT_FILE],optarg); break;
            case 'i': arg_opt[ARG_OPT_INPUT]  = 1; strcpy(arg_opt_file[ARG_OPT_INPUT_FILE],optarg); break;
            case 's': arg_opt[ARG_OPT_SAVE]   = 1; strcpy(arg_opt_file[ARG_OPT_SAVE_FILE],optarg); break;
            case ':': printf("option needs a value\n");exit(-1);break;
            case '?':
                printf("Error : unknown option -%c\n", optopt);
                printf("use -h option to see more.\n");
                exit(-2);
                break;
        }
    }
    /* input file or not? */
    if (arg_opt[ARG_OPT_INPUT] == 1) {
        g = load_file(arg_opt_file[ARG_OPT_INPUT_FILE]);
    } else {
        g = init_grid(arg_opt[ARG_OPT_WIDTH], arg_opt[ARG_OPT_LENGTH]);
        switch (arg_opt[ARG_OPT_DIFFICULTY]) {
            case 0:  straight_line(0,arg_opt[ARG_OPT_WIDTH],0,arg_opt[ARG_OPT_LENGTH],g); break;
            case 1:  crave_passage(g); break;
            default: crave_passage(g); break;
        }
    }

    if (!arg_opt[ARG_OPT_OUTPUT]) {
        preview(g);
    }
    if (arg_opt[ARG_OPT_KEY]) {
        find_path(0, 0, g);
        print_path(0, 0, g);
    }
    /* output file. */
    if (arg_opt[ARG_OPT_OUTPUT]) {
        out_svg(arg_opt_file[ARG_OPT_OUTPUT_FILE], g);
    } else if (arg_opt[ARG_OPT_SAVE]) {
        save_file(arg_opt_file[ARG_OPT_SAVE_FILE], g);
    }

    destory_grid(g);

    return 0;
}