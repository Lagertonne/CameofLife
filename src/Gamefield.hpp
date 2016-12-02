class Gamefield {
	private:
		int **field;
		int width;
		int height;
	
		int count_neighbours(z, s);

	public:
		void fill_with_zeros();
		void set_cell(int z, int s, int value);
		void print_gamefield();

		void generate_next_state();
		void set_random_cells();
		
}

