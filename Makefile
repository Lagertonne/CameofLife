all:
	mkdir -p bin
	gcc -o bin/cameoflife src/*.c `sdl2-config --cflags --libs`
debug:
	gcc -g -o bin/cameoflife src/*.c `sdl2-config --cflags --libs`
