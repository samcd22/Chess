#pragma once
#ifndef BISHOP_H
#define BISHOP_H

//Defining the derived class bishop
class bishop : public piece {
public:
	//Parameterised constructor
	bishop(int i_in, int j_in, bool is_white) {
		i = i_in;
		j = j_in;
		white = is_white;
		if (white) {
			name = " WBi ";
		}
		else {
			name = " BBi ";
		}
	}

	//Clone function overide
	piece* clone() {
		return new bishop{ *this };
	}

	//Copy constructor
	bishop(bishop& new_bishop) :
		piece(new_bishop) {}

	//Calulating the possible positions
	void calc_possible_positions(piece* piece_list[], int num_pieces, bool white_turn) {
		possible_positions.clear();
		int pieces_forward_diagonal[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //0 - No piece, 1 - Same coloured piece, 2 - Different coloured piece
		int pieces_backward_diagonal[16]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //0 - No piece, 1 - Same coloured piece, 2 - Different coloured piece

		//Looping through each piece in the piece list
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int piece_position_i{ piece_list[x]->get_i() };
				int piece_position_j{ piece_list[x]->get_j() };
				bool piece_white{ piece_list[x]->is_white() };

				//Checking for pieces on the forward and backward diagonal
				for (int diag{ -7 }; diag <= 8; diag++) {
					if (piece_position_i == i + diag && piece_position_j == j + diag && piece_white == white) {
						pieces_forward_diagonal[diag + 7] = 1;
					}
					else if (piece_position_i == i + diag && piece_position_j == j + diag && piece_white != white) {
						pieces_forward_diagonal[diag + 7] = 2;
					}
					if (piece_position_i == i - diag && piece_position_j == j + diag && piece_white == white) {
						pieces_backward_diagonal[diag + 7] = 1;
					}
					else if (piece_position_i == i - diag && piece_position_j == j + diag && piece_white != white) {
						pieces_backward_diagonal[diag + 7] = 2;
					}
				}
			}
		}

		//Checks how far up and right the bishop can move
		int up_right_x{ i + 1 };
		int up_right_y{ j + 1 };
		bool stop_up_right_loop{ false };
		int up_right_diag_index{ 8 };
		while (!stop_up_right_loop) {
			if (up_right_x <= 8 && up_right_y <= 8) {
				if (pieces_forward_diagonal[up_right_diag_index] == 0) {
					possible_positions.push_back({ up_right_x,up_right_y });
					stop_up_right_loop = false;
				}
				else if (pieces_forward_diagonal[up_right_diag_index] == 1) {
					stop_up_right_loop = true;
				}
				else {
					possible_positions.push_back({ up_right_x,up_right_y });
					stop_up_right_loop = true;
				}
				up_right_x++; up_right_y++; up_right_diag_index++;
			}
			else {
				stop_up_right_loop = true;
			}
		}

		//Checks how far down and left the bishop can move
		int down_left_x{ i - 1 };
		int down_left_y{ j - 1 };
		bool stop_down_left_loop{ false };
		int down_left_diag_index{ 6 };
		while (!stop_down_left_loop) {
			if (down_left_x > 0 && down_left_y > 0) {
				if (pieces_forward_diagonal[down_left_diag_index] == 0) {
					possible_positions.push_back({ down_left_x,down_left_y });
					stop_down_left_loop = false;
				}
				else if (pieces_forward_diagonal[down_left_diag_index] == 1) {
					stop_down_left_loop = true;
				}
				else {
					possible_positions.push_back({ down_left_x,down_left_y });
					stop_down_left_loop = true;
				}
				down_left_x--; down_left_y--; down_left_diag_index--;
			}
			else {
				stop_down_left_loop = true;
			}
		}

		//Checks how far down and right the bishop can move
		int down_right_x{ i - 1 };
		int down_right_y{ j + 1 };
		bool stop_down_right_loop{ false };
		int down_right_diag_index{ 8 };
		while (!stop_down_right_loop) {
			if (down_right_x > 0 && down_right_y <= 8) {
				if (pieces_backward_diagonal[down_right_diag_index] == 0) {
					possible_positions.push_back({ down_right_x,down_right_y });
					stop_down_right_loop = false;
				}
				else if (pieces_backward_diagonal[down_right_diag_index] == 1) {
					stop_down_right_loop = true;
				}
				else {
					possible_positions.push_back({ down_right_x,down_right_y });
					stop_down_right_loop = true;
				}
				down_right_x--; down_right_y++; down_right_diag_index++;
			}
			else {
				stop_down_right_loop = true;
			}
		}

		//Checks how far up and left the bishop can move
		int up_left_x{ i + 1 };
		int up_left_y{ j - 1 };
		bool stop_up_left_loop{ false };
		int up_left_diag_index{ 6 };
		while (!stop_up_left_loop) {
			if (up_left_x <= 8 && up_left_y > 0) {
				if (pieces_backward_diagonal[up_left_diag_index] == 0) {
					possible_positions.push_back({ up_left_x,up_left_y });
					stop_up_left_loop = false;
				}
				else if (pieces_backward_diagonal[up_left_diag_index] == 1) {
					stop_up_left_loop = true;
				}
				else {
					possible_positions.push_back({ up_left_x,up_left_y });
					stop_up_left_loop = true;
				}
				up_left_x++; up_left_y--; up_left_diag_index--;
			}
			else {
				stop_up_left_loop = true;
			}
		}
	}

	//Check if piece is putting other player in check
	bool is_checking(int king_location_i, int king_location_j) {
		bool check_on_other_player{ false };
		for (int x{}; x != possible_positions.size(); x++) {
			if (king_location_i == possible_positions[x][0] && king_location_j == possible_positions[x][1]) {
				check_on_other_player = true;
			}
		}
		return check_on_other_player;
	}
};
#endif