#include "game.h"

#include <utility>
#include <algorithm>

const  int di[] = { -1, -2, -3, -4, -5, -6, -7, -8, -9 };
const int di_[] = { -1, 1 };

game::game() : select_cell_i(-1), select_cell_j(-1),
white_player_move(true), white_eat_count(0),
black_eat_count(0), is_after_jump(false),
is_winner(false), white_queen_eat_count(0), black_queen_eat_count(0)
{
	for (unsigned i = 0; i < board_size; ++i)
		for (unsigned j = 0; j < board_size; ++j)
			check_board[i][j] = EMPTY;

	for (unsigned j = 0; j < board_size / 2 - 1; ++j)
		for (unsigned i = (j + 1) % 2; i < board_size; i += 2)
			check_board[i][j] = BLACK;

	for (unsigned j = board_size / 2 + 1; j < board_size; ++j)
		for (unsigned i = (j + 1) % 2; i < board_size; i += 2)
			check_board[i][j] = WHITE;

}

void game::single_white_jump(int i, int j, std::vector<position>& vector){
	if (check_board[i][j] == WHITE){
		for (int dir = 0; dir < 2; ++dir)
			for (int dir_ = 0; dir_ < 2; ++dir_){
				int _i = i + di_[dir];
				int _j = j + di_[dir_];

				int i_ = _i + di_[dir];
				int j_ = _j + di_[dir_];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;
				if ((check_board[_i][_j] == BLACK || check_board[_i][_j] == BLACK_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
	}
}

void game::single_black_jump(int i, int j, std::vector<position>& vector){
	if (check_board[i][j] == BLACK){
		for (int dir = 0; dir < 2; ++dir)
			for (int dir_ = 0; dir_ < 2; ++dir_){
				int _i = i + di_[dir];
				int _j = j + di_[dir_];

				int i_ = _i + di_[dir];
				int j_ = _j + di_[dir_];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;
				if ((check_board[_i][_j] == WHITE || check_board[_i][_j] == WHITE_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
	}
}

void game::single_white_queen_jump(int i, int j, std::vector<position>& vector){

	if (check_board[i][j] == WHITE_QUEEN){

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i + di[dir1];
			int _j = j + di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i + di[dir2];
				int j_ = _j + di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if (check_board[_i][_j] != EMPTY && check_board[i_][j_] != EMPTY)
					break;

				if ((check_board[_i][_j] == BLACK || check_board[_i][_j] == BLACK_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i - di[dir1];
			int _j = j + di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i - di[dir2];
				int j_ = _j + di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if (check_board[_i][_j] != EMPTY && check_board[i_][j_] != EMPTY)
					break;

				if ((check_board[_i][_j] == BLACK || check_board[_i][_j] == BLACK_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i + di[dir1];
			int _j = j - di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i + di[dir2];
				int j_ = _j - di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if (check_board[_i][_j] != EMPTY && check_board[i_][j_] != EMPTY)
					break;

				if ((check_board[_i][_j] == BLACK || check_board[_i][_j] == BLACK_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i - di[dir1];
			int _j = j - di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i - di[dir2];
				int j_ = _j - di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if (check_board[_i][_j] != EMPTY && check_board[i_][j_] != EMPTY)
					break;

				if ((check_board[_i][_j] == BLACK || check_board[_i][_j] == BLACK_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}
	}

}

void game::single_black_queen_jump(int i, int j, std::vector<position>& vector){

	if (check_board[i][j] == BLACK_QUEEN){
		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i + di[dir1];
			int _j = j + di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i + di[dir2];
				int j_ = _j + di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;
				if ((check_board[_i][_j] == WHITE || check_board[_i][_j] == WHITE_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i - di[dir1];
			int _j = j + di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i - di[dir2];
				int j_ = _j + di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if ((check_board[_i][_j] == WHITE || check_board[_i][_j] == WHITE_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i + di[dir1];
			int _j = j - di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i + di[dir2];
				int j_ = _j - di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if ((check_board[_i][_j] == WHITE || check_board[_i][_j] == WHITE_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}

		for (int dir1 = 0; dir1 < 8; ++dir1){
			int _i = i - di[dir1];
			int _j = j - di[dir1];

			for (int dir2 = 0; dir2 < 8; ++dir2){
				int i_ = _i - di[dir2];
				int j_ = _j - di[dir2];

				if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
					continue;
				if (i_ < 0 || i_ >= board_size || j_ < 0 || j_ >= board_size)
					continue;

				if ((check_board[_i][_j] == WHITE || check_board[_i][_j] == WHITE_QUEEN) && check_board[i_][j_] == EMPTY)
					vector.push_back(position(i_, j_));
			}
		}
	}

}

void game::single_white_move(int i, int j, std::vector<position>& vector){
	if (check_board[i][j] == WHITE){
		int j_ = select_cell_j - 1;
		for (int dir = 0; dir < 2; ++dir){
			int i_ = select_cell_i + di_[dir];
			if (i_ < 0)
				continue;
			if (i_ >= board_size)
				continue;
			if (check_board[i_][j_] == EMPTY)
				possible_steps.push_back(position(i_, j_));
		}
	}
}

void game::single_white_queen_move(int i, int j, std::vector<position>& vector){
	if (check_board[i][j] == WHITE_QUEEN){

		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i + di[dir1];
			int _j = j + di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i + di[dir1];
			int _j = j - di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i - di[dir1];
			int _j = j + di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i - di[dir1];
			int _j = j - di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
	}
}

void game::single_black_move(int i, int j, std::vector<position>& vector){
	if (check_board[i][j] == BLACK){
		int j_ = select_cell_j + 1;
		for (int dir = 0; dir < 2; ++dir){
			int i_ = i + di_[dir];
			if (i_ < 0)
				continue;
			if (i_ >= board_size)
				continue;
			if (check_board[i_][j_] == EMPTY)
				possible_steps.push_back(position(i_, j_));
		}
	}
}

void game::single_black_queen_move(int i, int j, std::vector<position>& vector){
	if (check_board[i][j] == BLACK_QUEEN){
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i + di[dir1];
			int _j = j + di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i + di[dir1];
			int _j = j - di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i - di[dir1];
			int _j = j + di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
		for (int dir1 = 0; dir1 < 9; ++dir1){
			int _i = i - di[dir1];
			int _j = j - di[dir1];
			if (_i < 0 || _i >= board_size || _j < 0 || _j >= board_size)
				continue;
			if (check_board[_i][_j] == EMPTY)
				possible_steps.push_back(position(_i, _j));
			if (check_board[_i][_j] != EMPTY)
				break;
		}
	}

}

bool game::is_must_white_eat(){

	std::vector<position> mandatory_moves;
	for (int i = 0; i < board_size; ++i)
		for (int j = 0; j < board_size; ++j)
			single_white_jump(i, j, mandatory_moves);

	if (mandatory_moves.empty())
		return true;
	else
		return false;
}

bool game::is_must_black_eat(){

	std::vector<position> mandatory_moves;
	for (int i = 0; i < board_size; ++i)
		for (int j = 0; j < board_size; ++j)
			single_black_jump(i, j, mandatory_moves);

	if (mandatory_moves.empty())
		return true;
	else
		return false;
}

bool game::is_must_white_queen_eat(){

	std::vector<position> mandatory_moves;
	for (int i = 0; i < board_size; ++i)
		for (int j = 0; j < board_size; ++j)
			single_white_queen_jump(i, j, mandatory_moves);

	if (mandatory_moves.empty())
		return true;
	else
		return false;
}

bool game::is_must_black_queen_eat(){

	std::vector<position> mandatory_moves;
	for (int i = 0; i < board_size; ++i)
		for (int j = 0; j < board_size; ++j)
			single_black_queen_jump(i, j, mandatory_moves);

	if (mandatory_moves.empty())
		return true;
	else
		return false;
}

void game::check_the_end_of_the_game(){
	int white_numb = 0;
	int black_numb = 0;

	for (int i = 0; i < board_size; ++i)
		for (int j = 0; j < board_size; ++j){
			if (check_board[i][j] == WHITE || check_board[i][j] == WHITE_QUEEN)
				++white_numb;
			if (check_board[i][j] == BLACK || check_board[i][j] == BLACK_QUEEN)
				++black_numb;
		}

	if (black_numb == 0){
		winner = BLACK_SIDE;
		is_winner = true;
		display();
		*this = game();
		return;
	}
	if (white_numb == 0){
		winner = WHITE_SIDE;
		is_winner = true;
		display();
		*this = game();
		return;
	}
}

bool game::could_eat_onse_again(int i, int j){
	possible_steps.empty();

	if (check_board[i][j] == WHITE){
		single_white_jump(i, j, possible_steps);
		if (possible_steps.empty())
			return false;
		else
			return true;
	}

	if (check_board[i][j] == WHITE_QUEEN){
		single_white_queen_jump(i, j, possible_steps);
		if (possible_steps.empty())
			return false;
		else
			return true;
	}

}

bool game::could_eat_onse_again_black(int i, int j){
	possible_steps.empty();

	if (check_board[i][j] == BLACK){
		single_black_jump(i, j, possible_steps);
		if (possible_steps.empty())
			return false;
		else
			return true;
	}

	if (check_board[i][j] == BLACK_QUEEN){
		single_black_queen_jump(i, j, possible_steps);
		if (possible_steps.empty())
			return false;
		else
			return true;
	}
}

void game::possible_step_to_white(int i, int j){

	if (!is_must_white_eat() || !is_must_white_queen_eat()){ // true - ходим куда хотим, false - должны бить
		single_white_jump(i, j, possible_steps);
		single_white_queen_jump(i, j, possible_steps);
	}


	if (is_must_white_eat() && is_must_white_queen_eat() && possible_steps.empty()){
		single_white_move(i, j, possible_steps);
		single_white_queen_move(i, j, possible_steps);
	}
	/*	сделать подсветку для возможных шагов
	for (std::vector<position>::iterator iter = possible_steps.begin(); iter != possible_steps.end(); ++iter){
		check_board[iter->first][iter->second] = SELECTED;
	}
	*/
}

void game::posssible_step_to_black(int i, int j){

	if (!is_must_black_eat() || !is_must_black_queen_eat()){
		single_black_jump(i, j, possible_steps);
		single_black_queen_jump(i, j, possible_steps);
	}

	if (is_must_black_eat() && is_must_black_queen_eat() && possible_steps.empty()){
		single_black_move(i, j, possible_steps);
		single_black_queen_move(i, j, possible_steps);
	}
}

void game::set_select_cell(int i, int j){
	if (i >= 0 && i < board_size && j >= 0 && j < board_size &&  check_board[i][j] != EMPTY){	// если выбранная позиция лежит на доске и не  пустая
		if (white_player_move && get_cell(i, j) == game::WHITE){	// если сейчас ход белого игрока и если выбранная шашка белая
			select_cell_i = i;
			select_cell_j = j;
			possible_step_to_white(i, j);
		}
		if (!white_player_move && get_cell(i, j) == game::BLACK){
			select_cell_i = i;
			select_cell_j = j;
			posssible_step_to_black(i, j);
		}
		if (white_player_move && get_cell(i, j) == game::WHITE_QUEEN){
			select_cell_i = i;
			select_cell_j = j;
			possible_step_to_white(i, j);
		}
		if (!white_player_move && get_cell(i, j) == game::BLACK_QUEEN){
			select_cell_i = i;
			select_cell_j = j;
			posssible_step_to_black(i, j);
		}
	}
	else{	// если выбранная позиция вне доски или выбрана пустая клетка
		select_cell_i = -1;
		select_cell_j = -1;
	}
}

void game::move(int i, int j){
	if (select_cell_i == i && select_cell_j == j && !is_after_jump){	// отмена хода кроме тех случае когда обязателно бить
		possible_steps.clear();
		select_cell_i = -1;
		select_cell_j = -1;
		is_after_jump = false;
	}
	if (check_board[i][j] == EMPTY){	// если позиция в которую совершается ход пустая
		bool is_real_step = !white_player_move;		// проверка: действительно и мы сходили (сходили в допустимые значения)
		if (white_player_move){
			std::vector<position>::iterator iter;

			for (iter = possible_steps.begin(); iter < possible_steps.end(); ++iter){
				if (iter->first == i && iter->second == j){

					if (check_board[select_cell_i][select_cell_j] == WHITE){
						check_board[select_cell_i][select_cell_j] = EMPTY;
						check_board[i][j] = WHITE;
						if (abs(select_cell_i - i) > 1){
							check_board[(select_cell_i + i) / 2][(select_cell_j + j) / 2] = EMPTY;
							++white_eat_count;
							is_after_jump = true;
						}
					}
					if (check_board[select_cell_i][select_cell_j] == WHITE_QUEEN){
						check_board[select_cell_i][select_cell_j] = EMPTY;
						check_board[i][j] = WHITE_QUEEN;


						int i_dell = 0, j_dell = 0;

						if (select_cell_i > i && select_cell_j < j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == BLACK || check_board[i][j] == BLACK_QUEEN){
									++white_queen_eat_count;
								}
								--i_dell;
								++j_dell;
							}
						}

						if (select_cell_i < i && select_cell_j > j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == BLACK || check_board[i][j] == BLACK_QUEEN){
									++white_queen_eat_count;
								}
								++i_dell;
								--j_dell;
							}
						}

						if (select_cell_i < i && select_cell_j < j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == BLACK || check_board[i][j] == BLACK_QUEEN){
									++white_queen_eat_count;
								}
								++i_dell;
								++j_dell;
							}
						}

						if (select_cell_i > i && select_cell_j > j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == BLACK || check_board[i][j] == BLACK_QUEEN){
									++white_queen_eat_count;
								}
								--i_dell;
								--j_dell;
							}
						}

						if (white_queen_eat_count > 0){
							int i_dell = 0, j_dell = 0;
							if (select_cell_i > i && select_cell_j < j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									--i_dell;
									++j_dell;
								}
							}

							if (select_cell_i < i && select_cell_j > j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									++i_dell;
									--j_dell;
								}
							}

							if (select_cell_i < i && select_cell_j < j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									++i_dell;
									++j_dell;
								}
							}

							if (select_cell_i > i && select_cell_j > j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									--i_dell;
									--j_dell;
								}
							}
							is_after_jump = true;
						}
					}
					is_real_step = white_player_move;
				}
			}
			possible_steps.clear();
			if (could_eat_onse_again(i, j) && (white_eat_count > 0 || white_queen_eat_count > 0)){		// повторный прыжок через шашку которую можем побить
				select_cell_i = i;
				select_cell_j = j;
				is_real_step = !white_player_move;
			}
			else { // после хода шашка становится не останется выбраной
				select_cell_i = -1;
				select_cell_j = -1;
				white_eat_count = 0;
				white_queen_eat_count = 0;
			}

			if (j == 0){
				std::vector<position> eat_after_end_;
				single_white_jump(i, j, eat_after_end_);
				if (eat_after_end_.empty())
					check_board[i][j] = WHITE_QUEEN;	// проверка на дамку после окончания всех возможных прыжков
			}
		}
		if (!white_player_move){
			std::vector<position>::iterator iter;
			for (iter = possible_steps.begin(); iter < possible_steps.end(); ++iter){
				if (iter->first == i && iter->second == j){
					if (check_board[select_cell_i][select_cell_j] == BLACK){
						check_board[select_cell_i][select_cell_j] = EMPTY;
						check_board[i][j] = BLACK;
						if (abs(select_cell_i - i) > 1){
							check_board[(select_cell_i + i) / 2][(select_cell_j + j) / 2] = EMPTY;
							++black_eat_count;
							is_after_jump = true;
						}
					}
					if (check_board[select_cell_i][select_cell_j] == BLACK_QUEEN){
						check_board[select_cell_i][select_cell_j] = EMPTY;
						check_board[i][j] = BLACK_QUEEN;

						int i_dell = 0, j_dell = 0;
						if (select_cell_i > i && select_cell_j < j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i][j] == WHITE || check_board[i][j] == WHITE_QUEEN)
									++black_queen_eat_count;
								--i_dell;
								++j_dell;
							}
						}

						if (select_cell_i < i && select_cell_j > j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == WHITE || check_board[i_dell][j_dell] == WHITE_QUEEN)
									++black_queen_eat_count;
								++i_dell;
								--j_dell;
							}
						}

						if (select_cell_i < i && select_cell_j < j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == WHITE || check_board[i_dell][j_dell] == WHITE_QUEEN)
									++black_queen_eat_count;
								++i_dell;
								++j_dell;
							}
						}

						if (select_cell_i > i && select_cell_j > j){
							i_dell = select_cell_i; j_dell = select_cell_j;
							while (i_dell != i && j_dell != j){
								if (check_board[i_dell][j_dell] == WHITE || check_board[i_dell][j_dell] == WHITE_QUEEN)
									++black_queen_eat_count;
								--i_dell;
								--j_dell;
							}
						}


						if (black_queen_eat_count > 0){
							int i_dell = 0, j_dell = 0;

							if (select_cell_i > i && select_cell_j < j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									--i_dell;
									++j_dell;
								}
							}

							if (select_cell_i < i && select_cell_j > j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									++i_dell;
									--j_dell;
								}
							}

							if (select_cell_i < i && select_cell_j < j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									++i_dell;
									++j_dell;
								}
							}

							if (select_cell_i > i && select_cell_j > j){
								i_dell = select_cell_i; j_dell = select_cell_j;
								while (i_dell != i && j_dell != j){
									check_board[i_dell][j_dell] = EMPTY;
									--i_dell;
									--j_dell;
								}
							}
						}
						is_after_jump = true;
					}

					is_real_step = white_player_move;
				}
			}
			possible_steps.clear();
			if (could_eat_onse_again_black(i, j) && (black_eat_count > 0 || black_queen_eat_count > 0)){
				select_cell_i = i;
				select_cell_j = j;
				is_real_step = !white_player_move;
			}
			else {
				select_cell_i = -1;
				select_cell_j = -1;
				black_eat_count = 0;
				black_queen_eat_count = 0;
			}
			if (j == board_size - 1 && is_after_jump ){
				std::vector<position> eat_after_end;
				single_black_jump(i, j, eat_after_end);
				if (eat_after_end.empty())
					check_board[i][j] = BLACK_QUEEN;
			}
		}
		white_player_move = !is_real_step;
	}

	check_the_end_of_the_game();
}