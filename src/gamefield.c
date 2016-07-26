#include <stdio.h>
#include <stdlib.h>

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
	for( int z=0; z<gF->height; z++) {
		for( int s=0; s<gF->width; s++) {
			printf( "%d ", gF->field[z][s] );
		}
		printf("\n");
	}
}

/*int count_neighbours(gameField *gf, int z, int s) {
	int count = 0;
	for ( z<=0 ? int bZ=0 : int bZ=z-1; z<gf->height ? bZ<z : bZ<=z+1; bZ++) {
		for (s<=0 ? int bS = 0 : int bS=s-1; z<gf->width ? bS<s : bS<=s+1; bS++) {
			if (gf->field[bZ][bS] == 1)
				count++;
		}
	}
	return count;
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
}*/

int main() {
	gameField *field = make_gameField(10, 10);
	set_cell(field, 3, 3, 1);
	set_cell(field, 4, 3, 1);
	set_cell(field, 5, 3, 1);
	set_cell(field, 5, 4, 1);
	print_gameField(field);
	//field = calc_new_state(field);
	print_gameField(field);
	destroy_gameField(field);
}
