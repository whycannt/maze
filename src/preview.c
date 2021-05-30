#include <stdio.h>
#include "preview.h"
#include "const.h"

void preview (const Grid *g) {
    // Draw the first line
    for (int j = 0; j < g->len; j++) {
        (g->G[0][j]&W) ? printf("_") : printf(" ");
        (g->G[0][j]&N) ? printf("_") : printf("%s",HORIZON);
    }
    printf("\n");

    // the left 2*n lines
    for (int i = 0; i < g->wid; i++) {
        for (int j = 0; j < g->len; j++) {
            if (g->G[i][j]&W) {
                (j>=1 && (g->G[i][j-1]&S) || j<g->len-1 && (g->G[i][j]&S)) ? printf(" ") : printf("_");
            } else {
                printf("%s", VERTICAL);
            }
            (g->G[i][j]&S) ? printf("%s",OPEN) : printf("%s",HORIZON);
        }
        printf("%s\n",VERTICAL);
    }
}