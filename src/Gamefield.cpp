#include "Gamefield.hpp"
#include <iostream>

using namespace std;

Gamefield::Gamefield(int w, int h) :
		width(w),
		height(h)
	{
	field = (int**)calloc(height, sizeof(int*));
	for (int z=0; z<height; z++) {
		field[z] = (int*)calloc(width, sizeof(int));
	}
}

void Gamefield::print() {
	for (int z=0; z<height; z++) {
		for (int s=0; s<width; s++) {
			cout << field[z][s] << " ";
		}
		cout << endl;
	}
}

void Gamefield::set_cell(int z, int s, int v) {
	cout << "Setting cell " << z << " " << s << endl;
	field[z][s] = v;
}

void Gamefield::fill_with_zeros() {
	for (int z=0; z<height; z++) {
		for (int s=0; s<width; s++) {
			set_cell(z, s, 0);
		}
	}
}

int Gamefield::count_neighbours(int z, int s) {
	int count = 0;
	int bZ=0;
	if( z>0 )
		bZ=z-1;
	for (; bZ<=z+1 && bZ < height; bZ++) {
		int bS=0;
		if( s>0 )
			bS=s-1;
		for ( ; bS<=s+1 && bS < width; bS++) {
			if (field[bZ][bS] == 1)
				count++;
		}
	}
	if( count < 0 ) {
		return 0;
	} else if( field[z][s] == 1 ) {
		return count-1;
	} else {
		return count;
	}
	
}

void Gamefield::generate_next_gen() {
	Gamefield *oldState(this);
	// Count neighbours of a cell
	for (int z=0; z<height; z++) {
		for (int s=0; s<width; s++) {
			int n = oldState->count_neighbours(z, s);
			if( n == 3 ) {
				set_cell(z, s, 1);	
			} else if( n == 2 && field[z][s] == 1) {
				set_cell(z, s, 1);
			}
		}
	}
}
