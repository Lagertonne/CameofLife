#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

typedef struct {
	int **field;
	int width;
	int height;
} gameField;

void fill_with_zeros( gameField *gF );

gameField *make_gameField(int h, int w);

void set_cell(gameField *gf, int z, int s, int value);

void destroy_gameField(gameField *gF );

void print_gameField( gameField *gF );

int count_neighbours(gameField *gf, int z, int s);

gameField *calc_new_state(gameField *gf);

void set_random_cells(gameField *gf, int n);

#endif // GAMEFIELD_H_
