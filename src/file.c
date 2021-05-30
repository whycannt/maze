#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "const.h"
#include "grid.h"

void save_file(const char *file,const Grid *g){
    FILE *out = fopen(file, "wb");
    // Write the width and length.
    fwrite(&g->wid,1,1,out);
    fwrite(&g->len,1,1,out);

    unsigned char byte;
    unsigned char count = 0;
    for (int i = 0; i < g->wid; i++) {
        for (int j = 0; j < g->len; j++) {
            byte |= count ? g->G[i][j]&LOW_B : g->G[i][j]<<4;
            count++;
            if (count == 2) {
                fwrite(&byte,1,1,out);
                byte = 0;
                count = 0;
            }
        }
    }
    if (count) {
        fwrite(&byte, 1, 1, out);
    }
    fclose(out);
}

Grid* load_file(const char* file) {
    FILE *in = fopen(file, "rb");
    if (in == NULL) {
        printf("Fail to open file!\n");
        exit(-1);
    }

    // Read the head data.
    unsigned char len, wid;
    fread(&wid,1,1,in);
    fread(&len,1,1,in);

    Grid *g = init_grid(wid,len);
    unsigned char byte;
    int count = 0;
    for (int i = 0; i < g->wid; i++) {
        for (int j = 0; j < g->len; j++) {
            // if there is no data in 'byte' variable,then read from file stream.
            if (!count) {
                fread(&byte,1,1,in);
                count = 2;
            }
            g->G[i][j] |= count==2 ? (byte&HI_B)>>4 : (byte&LOW_B);
            count--;
        }
    }

    fclose(in);
    return g;
}

void out_svg(const char *file, const Grid *g){
    FILE *out = fopen(file, "wb");
    if (out == NULL) {
        printf("open svg file error!\n");
        exit(-1);
    }
    fwrite(SVG_PREFIX(LINE_COLOR, LINE_WIDTH),
           sizeof(SVG_PREFIX(LINE_COLOR, LINE_WIDTH))-1, 1, out);

    int x = LINE_LENGTH, y = 0;
    char svg_path[BUFFER_SIZE];
    int  svg_len = 0;
    char command;
    // First row.
    for (int c = 0; c < g->len; c++, x += LINE_LENGTH) {
        command = (g->G[0][c]&N) ? 'M' : 'L';
        fwrite(&command, 1, 1, out);
        svg_len = sprintf(svg_path, "%d", x);
        fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
        svg_len = sprintf(svg_path, "%d", y);
        fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
    }
    y += LINE_LENGTH;
    for (int r = 0; r < g->wid; r++, y += LINE_LENGTH) {
        x = LINE_LENGTH;
        // Move to the start.
        fwrite("M0 ", 3, 1, out);
        svg_len = sprintf(svg_path, "%d", y);
        fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
        for (int c = 0; c < g->len; c++, x += LINE_LENGTH) {
            command = (g->G[r][c]&S) ? 'M' : 'L';
            fwrite(&command, 1, 1, out);
            svg_len = sprintf(svg_path, "%d", x);
            fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
            svg_len = sprintf(svg_path, "%d", y);
            fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
        }
    }

    fwrite("M0 0 ", 5, 1, out);
    x = 0, y = LINE_LENGTH;
    for (int r = 0; r < g->wid; r++, y += LINE_LENGTH) {
        command = (g->G[r][0]&W) ? 'M' : 'L';
        fwrite(&command, 1, 1, out);
        svg_len = sprintf(svg_path, "%d", x);
        fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
        svg_len = sprintf(svg_path, "%d", y);
        fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
    }
    x += LINE_LENGTH;
    for (int c = 0; c < g->len; c++, x += LINE_LENGTH) {
        y = LINE_LENGTH;
        // Move to the start.
        fwrite("M", 1, 1, out);
        svg_len = sprintf(svg_path, "%d", x);
        fwrite(svg_path, svg_len, 1, out); fwrite(" 0 ", 3, 1, out);

        for (int r = 0; r < g->wid; r++, y += LINE_LENGTH) {
            command = (g->G[r][c]&E) ? 'M' : 'L';
            fwrite(&command, 1, 1, out);
            svg_len = sprintf(svg_path, "%d", x);
            fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
            svg_len = sprintf(svg_path, "%d", y);
            fwrite(svg_path, svg_len, 1, out); fwrite(" ", 1, 1, out);
        }
    }

    fwrite(svg_path, svg_len, 1, out);
    fwrite(SVG_SUFFIX, sizeof(SVG_SUFFIX)-1, 1, out);
    fclose(out);
};