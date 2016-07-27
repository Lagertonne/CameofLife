#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int **field;
	int width;
	int height;
} gameField;


void fill_with_zeros( gameField *gF ) {
	for( int z=0; z<gF->height; z++) {
		for( int s=0; s<gF->width; s++ ) {
			gF->field[z][s] = 0;
		}
	}
}

gameField *make_gameField(int h, int w) {
	gameField *gF = malloc( sizeof(gameField) );
	gF->field = malloc( h*sizeof(int*) );
	gF->width = w;
	gF->height = h;
		
	for( int z=0; z<h; z++ ) {
		gF->field[z] = malloc( w*sizeof(int) );
	}
	fill_with_zeros( gF );
	return gF;
}

void set_cell(gameField *gf, int z, int s, int value) {
	if( z<gf->height && s<gf->width && z>=0 && s>=0 ) {
		gf->field[z][s] = value; 
	}
}

void destroy_gameField(gameField *gF ) {
	for( int z=0; z<gF->height; z++ ) {
		free(gF->field[z]);
	}
	free(gF->field);
	free(gF);
}

void print_gameField( gameField *gF ) {
	for( int i=0; i<gF->width+2; i++) {
		printf("-");
	}
	for( int z=0; z<gF->height; z++) {
		printf("\n|");
		for( int s=0; s<gF->width; s++) {
			(gF->field[z][s] == 0) ? printf(" ") : printf("#");
		}
		printf("|");
	}
	printf("\n");
	for( int i=0; i<gF->width+2; i++) {
		printf("-");
	}
}

int count_neighbours(gameField *gf, int z, int s) {
	int count = 0;
	int bZ=0;
	if( z>0 )
		bZ=z-1;
	for ( ; bZ<=z+1 && bZ<gf->height; bZ++) {
		int bS=0;
		if( s>0 )
			bS=s-1;
		for ( ; bS<=s+1 && bS<gf->width; bS++) {
			if (gf->field[bZ][bS] == 1)
				count++;
		}
	}
	if( count < 0 ) {
		return 0;
	} else if( gf->field[z][s] == 1 ) {
		return count-1;
	} else {
		return count;
	}
}

gameField *calc_new_state(gameField *gf) {
	gameField *newState = make_gameField(gf->height, gf->width);
	
	// Count neighbours of a cell
	for (int z=0; z<gf->height; z++) {
		for (int s=0; s<gf->width; s++) {
			int n = count_neighbours(gf, z, s);
			if( n == 3 ) {
				set_cell(newState, z, s, 1);	
			} else if( n == 2 && gf->field[z][s] == 1) {
				set_cell(newState, z, s, 1);
			}
		}
	}

	return newState;
}

void set_random_cells(gameField *gf, int n) {
	for( int i=0; i<n; i++ ) {
		set_cell(gf, rand()%gf->width, rand()%gf->height, 1);
	}
}

int main() {
	srand(time(NULL));
	gameField *field = make_gameField(10, 10);
	/*set_cell(field, 3, 3, 1);
	set_cell(field, 4, 3, 1);
	set_cell(field, 5, 3, 1);*/
	set_random_cells(field, 20);
	print_gameField(field);
	for( int i=0; i<5; i++ ) {
		printf("\n");
		field = calc_new_state(field);
		print_gameField(field);
	}
	destroy_gameField(field);
}
