#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H

//Defining the derived class knight
class knight : public piece {
public:
	//Parameterised constructor
	knight(int i_in, int j_in, bool is_white) {
		i = i_in;
		j = j_in;
		white = is_white;
		if (white) {
			name = " WKn ";
		}
		else {
			name = " BKn ";
		}
	}

	//Clone function overide
	piece* clone() {
		return new knight{ *this };
	}

	//Copy constructor
	knight(knight& new_knight) :
		piece(new_knight) {}

	//Calulating the possible positions
	void calc_possible_positions(piece* piece_list[], int num_pieces, bool white_turn) {
		possible_positions.clear();
		bool piece_in_position_1{ false };
		bool piece_in_position_2{ false };
		bool piece_in_position_3{ false };
		bool piece_in_position_4{ false };
		bool piece_in_position_5{ false };
		bool piece_in_position_6{ false };
		bool piece_in_position_7{ false };
		bool piece_in_position_8{ false };

		//Looping through each piece in the piece list
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int piece_position_i{ piece_list[x]->get_i() };
				int piece_position_j{ piece_list[x]->get_j() };
				bool piece_white{ piece_list[x]->is_white() };

				//Checking for pieces in position 1
				if (piece_position_i == i + 2 && piece_position_j == j + 1 && piece_white == white_turn) {
					piece_in_position_1 = true;
				}

				//Checking for pieces in position 2
				if (piece_position_i == i + 1 && piece_position_j == j + 2 && piece_white == white_turn) {
					piece_in_position_2 = true;
				}

				//Checking for pieces in position 3
				if (piece_position_i == i - 1 && piece_position_j == j + 2 && piece_white == white_turn) {
					piece_in_position_3 = true;
				}

				//Checking for pieces in position 4
				if (piece_position_i == i - 2 && piece_position_j == j + 1 && piece_white == white_turn) {
					piece_in_position_4 = true;
				}

				//Checking for pieces in position 5
				if (piece_position_i == i - 2 && piece_position_j == j - 1 && piece_white == white_turn) {
					piece_in_position_5 = true;
				}

				//Checking for pieces in position 6
				if (piece_position_i == i - 1 && piece_position_j == j - 2 && piece_white == white_turn) {
					piece_in_position_6 = true;
				}

				//Checking for pieces in position 7
				if (piece_position_i == i + 1 && piece_position_j == j - 2 && piece_white == white_turn) {
					piece_in_position_7 = true;
				}

				//Checking for pieces in position 8
				if (piece_position_i == i + 2 && piece_position_j == j - 1 && piece_white == white_turn) {
					piece_in_position_8 = true;
				}
			}
		}

		//Constrains the motion of the knights
		if (!piece_in_position_1 && i + 2 <= 8 && j + 1 <= 8) {
			possible_positions.push_back({ i + 2,j + 1 });
		}
		if (!piece_in_position_2 && i + 1 <= 8 && j + 2 <= 8) {
			possible_positions.push_back({ i + 1,j + 2 });
		}
		if (!piece_in_position_3 && i - 1 > 0 && j + 2 <= 8) {
			possible_positions.push_back({ i - 1,j + 2 });
		}
		if (!piece_in_position_4 && i - 2 > 0 && j + 1 <= 8) {
			possible_positions.push_back({ i - 2,j + 1 });
		}
		if (!piece_in_position_5 && i - 2 > 0 && j - 1 > 0) {
			possible_positions.push_back({ i - 2,j - 1 });
		}
		if (!piece_in_position_6 && i - 1 > 0 && j - 2 > 0) {
			possible_positions.push_back({ i - 1,j - 2 });
		}
		if (!piece_in_position_7 && i + 1 <= 8 && j - 2 > 0) {
			possible_positions.push_back({ i + 1,j - 2 });
		}
		if (!piece_in_position_8 && i + 2 <= 8 && j - 1 > 0) {
			possible_positions.push_back({ i + 2,j - 1 });
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