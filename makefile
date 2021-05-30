maze.exe :
	gcc main.c src/maze.c src/grid.c src/file.c src/preview.c src/path.c src/const.c -I inc -o maze
