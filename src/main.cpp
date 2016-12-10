#include <iostream>
#include "Gamefield.cpp"

using namespace std;

int main() {
	Gamefield gamefield(10, 10);
	gamefield.set_cell(5,6,1);
	gamefield.set_cell(5,4,1);
	gamefield.print();
	cout << gamefield.count_neighbours(5, 5);
	return 0;
}
