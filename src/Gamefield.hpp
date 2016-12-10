#ifndef GAMEFIELD_HPP
#define GAMEFiELD_HPP

class Gamefield {
	private:
		int **field;
		int width;
		int height;
	
	public:
		Gamefield(int w, int h);
		void fill_with_zeros();
		void set_cell(int z, int s, int v);
		void print();

		void generate_next_gen();
		void set_random_cells();
		int count_neighbours(int z, int s);
};

#endif // GAMEFIELD_HPP
