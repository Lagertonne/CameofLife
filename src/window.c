#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "gamefield.h"

const int HEIGHT=800;
const int WIDTH=600;

typedef struct {
	SDL_Rect rect;
	SDL_Color color;
} Cell;

gameField *generate_gameField(int x, int y) {
	gameField *gf = make_gameField(10, 10);
	set_random_cells(gf, 20);
	return gf;
}

Cell *gamefield_to_cells( gameField *gf ) {
	int elems = (gf->width)*(gf->height);
	Cell *cells = malloc(elems*sizeof(Cell));
	int rect_width = WIDTH/gf->width;
	int rect_height = HEIGHT/gf->height;

	int cell_count = 0;
	int posX = 0;
	int posY = 0;
	for (int z=0; z<gf->width; z++) {
		for (int s=0; s<gf->height; s++) {
			cells[cell_count].rect.x = posX;
			cells[cell_count].rect.y = posY;
			cells[cell_count].rect.w = rect_width;
			cells[cell_count].rect.h = rect_height;
			if (gf->field[z][s] >= 1) {
				cells[cell_count].color.r = 255;
				cells[cell_count].color.g = 255;
				cells[cell_count].color.b = 255;
			} else {
				cells[cell_count].color.r = 0;
				cells[cell_count].color.g = 50;
				cells[cell_count].color.b = 0;
			}


			posX += rect_width;
			posY += rect_height;
			cell_count++;
		}
	}

	return cells;
}

int main() {
	SDL_Window *window = NULL; 
	SDL_Renderer *rend = NULL;
	SDL_Event e;
	int quit = 0;
	if  ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0 ) { 
		fprintf(stderr, "\nUnable to initialize SDL %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	window = SDL_CreateWindow("Came of Life - by lgrt", 100, 100, HEIGHT, WIDTH, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "\nCould not create window: %s\n", SDL_GetError());
		return 1;
	}

	rend = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	
	if (rend == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "\nCould not create rend: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	gameField *gf = generate_gameField(10, 10);

	while(quit == 0) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
		}
		Cell *cells = gamefield_to_cells(gf);
		
		SDL_Delay(500);
	}

	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
