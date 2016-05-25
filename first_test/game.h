#ifndef GAME_H
#define GAME_H

#include <utility>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdlib>

const int board_size = 10;
typedef std::pair<int, int> position;
typedef std::pair<position, position> step;


class game
{
	int select_cell_i;
	int select_cell_j;
public:
	enum side {BLACK_SIDE, WHITE_SIDE};
	enum cell { BLACK, WHITE, EMPTY, BLACK_QUEEN, WHITE_QUEEN, SELECTED };
	bool is_winner;
	game();

	cell get_cell(int i, int j) { return check_board[i][j]; }
	void set_cell(int i, int j, cell Cell) { check_board[i][j] = Cell; }

	void single_white_jump(int, int, std::vector<position>&);
	void single_black_jump(int, int, std::vector<position>&);
	void single_white_queen_jump(int, int, std::vector<position>&);
	void single_black_queen_jump(int, int, std::vector<position>&);

	void single_white_move(int, int, std::vector<position>&);
	void single_white_queen_move(int, int, std::vector<position>&);
	void single_black_move(int, int, std::vector<position>&);
	void single_black_queen_move(int, int, std::vector<position>&);

	bool is_must_white_eat();
	bool is_must_black_eat();
	bool is_must_white_queen_eat();
	bool is_must_black_queen_eat();

	bool could_eat_onse_again(int, int);
	bool could_eat_onse_again_black(int, int);

	void possible_step_to_white(int, int);
	void posssible_step_to_black(int, int);
	void check_the_end_of_the_game();

	void set_select_cell(int i, int j);
	position is_select_cell()const { return std::make_pair(select_cell_i, select_cell_j); }
	void unselect_sell() { select_cell_i = -1; select_cell_j = -1; }

	void move(int, int);
	side get_winner(){ return winner; }
	friend void display();
private:
	typedef cell board[board_size][board_size];
	board check_board;
	std::vector<position> possible_steps;
	bool white_player_move;
	bool is_after_jump;
	int white_eat_count;
	int black_eat_count;

	int white_queen_eat_count;
	int black_queen_eat_count;

	side winner;
};
#endif /* GAME_H */