#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "gamefield.h"

const int HEIGHT=800;
const int WIDTH=800;

typedef struct {
	SDL_Rect rect;
	SDL_Color color;
} Cell;

typedef struct {
	Cell *cells;
	int size;
} CellList;

gameField *generate_gameField(int x, int y) {
	gameField *gf = make_gameField(x, y);
	set_random_cells(gf, 100);
	set_cell(gf, 10, 10, 1);
	set_cell(gf, 11, 10, 1);
	set_cell(gf, 12, 10, 1);
	set_cell(gf, 13, 10, 1);
	set_cell(gf, 13, 11, 1);
	set_cell(gf, 10, 11, 1);
	return gf;
}

CellList *gamefield_to_cells( gameField *gf ) {
	CellList *list = malloc(sizeof(CellList));
	int elems = (gf->width)*(gf->height);	
	list->cells = malloc(elems*sizeof(Cell));
	int rect_width = 0;
	if ( WIDTH <= HEIGHT ) {
		rect_width = WIDTH/gf->width;
		//rect_height = WIDTH/gf->height;
	} else {
		rect_width = HEIGHT/gf->height;
	}
	//int rect_width = WIDTH/gf->width;
	//int rect_height = HEIGHT/gf->height;
	list->size=elems;

	int cell_count = 0;
	int posX = 0;
	int posY = 0;

	for (int z=0; z<gf->width; z++) {
		for (int s=0; s<gf->height; s++) {
			list->cells[cell_count].rect.x = posX;
			list->cells[cell_count].rect.y = posY;
			list->cells[cell_count].rect.w = rect_width;
			list->cells[cell_count].rect.h = rect_width;
			if (gf->field[z][s] >= 1) {
				list->cells[cell_count].color.r = 255;
				list->cells[cell_count].color.g = 255;
				list->cells[cell_count].color.b = 255;
			} else {
				list->cells[cell_count].color.r = 0;
				list->cells[cell_count].color.g = 50;
				list->cells[cell_count].color.b = 0;
			}

			posX += rect_width;
			cell_count++;
		}
		posY += rect_width;
		posX = 0;
	}

	return list;
}

void draw_field( SDL_Renderer *rend, CellList *list) {
	for ( int i=0; i<list->size; i++) {
		SDL_SetRenderDrawColor( rend, list->cells[i].color.r, list->cells[i].color.g, list->cells[i].color.b, list->cells[i].color.a );
		SDL_RenderFillRect( rend, &list->cells[i].rect );
	}
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

	window = SDL_CreateWindow("Came of Life - by lgrt", 50, 50, HEIGHT, WIDTH, SDL_WINDOW_SHOWN);
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

	gameField *gf = generate_gameField(50, 50);

	while(quit == 0) {
		SDL_SetRenderDrawColor(rend, 10, 0, 0, 0);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
		}
		SDL_RenderClear(rend);

		CellList *cells = gamefield_to_cells(gf);
		draw_field( rend, cells);
		SDL_RenderPresent(rend);	
		SDL_Delay(500);
		gf = calc_new_state(gf);	
	}

	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
