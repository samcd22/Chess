#pragma once
#ifndef PAWN_H
#define PAWN_H

//Defining the derived class pawn
class pawn : public piece {
public:
	//Parameterised Constructor
	pawn(int i_in, int j_in, bool is_white) {
		i = i_in;
		j = j_in;
		white = is_white;
		if (white) {
			name = " WPa ";
		}
		else {
			name = " BPa ";
		}
		_pawn = true;
	}

	//Clone function overide
	piece* clone() {
		return new pawn{ *this };
	}

	//Copy constructor
	pawn(pawn& new_pawn) :
		piece(new_pawn) {}

	//Calculating the possible positions
	void calc_possible_positions(piece* piece_list[], int num_pieces, bool white_turn) {
		possible_positions.clear();
		bool is_in_front{ false };
		bool is_in_front_plus_1{ false };
		bool is_diag_left{ false };
		bool is_diag_right{ false };

		//Looping through each piece in the piece list
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int piece_position_i{ piece_list[x]->get_i() };
				int piece_position_j{ piece_list[x]->get_j() };
				bool piece_white{ piece_list[x]->is_white() };

				//Checking for pieces in front of the pawn
				if (piece_position_i == i + 1 && piece_position_j == j && white) {
					is_in_front = true;
				}
				else if (piece_position_i == i - 1 && piece_position_j == j && !white) {
					is_in_front = true;
				}
				if (piece_position_i == i + 2 && piece_position_j == j && white) {
					is_in_front_plus_1 = true;
				}
				else if (piece_position_i == i - 2 && piece_position_j == j && !white) {
					is_in_front_plus_1 = true;
				}

				//Checking for opposite colour pieces diagonally in front of the pawns
				if (white && piece_white != white && piece_position_i == i + 1 && piece_position_j == j - 1) {
					is_diag_left = true;
				}
				else if (!white && piece_white != white && piece_position_i == i - 1 && piece_position_j == j - 1) {
					is_diag_left = true;
				}
				if (white && piece_white != white && piece_position_i == i + 1 && piece_position_j == j + 1) {
					is_diag_right = true;
				}
				else if (!white && piece_white != white && piece_position_i == i - 1 && piece_position_j == j + 1) {
					is_diag_right = true;
				}
			}
		}

		//Constrain the forward motion of a pawn
		//For white pieces
		if (white && !is_in_front && i + 1 <= 8) {
			possible_positions.push_back({ i + 1 ,j });
			//Only move forward 2 on first move of pawn
			if (!has_moved && i == 2 && !is_in_front_plus_1 && i + 2 <= 8) {
				possible_positions.push_back({ i + 2,j });
			}
		}
		//For black pieces
		else if (!white && !is_in_front && i - 1 > 0) {
			possible_positions.push_back({ i - 1 ,j });
			//Only move forward 2 on first move of pawn
			if (!has_moved && i == 7 && !is_in_front_plus_1 && i - 2 > 0) {
				possible_positions.push_back({ i - 2,j });
			}
		}

		//Making it possible to move diagonally forward onto spaces with opposing colourd pieces
		if (white && is_diag_left && i + 1 <= 8 && j - 1 > 0) {
			possible_positions.push_back({ i + 1,j - 1 });
		}
		else if (!white && is_diag_left && i - 1 > 0 && j - 1 > 0) {
			possible_positions.push_back({ i - 1,j - 1 });
		}
		if (white && is_diag_right && i + 1 <= 8 && j + 1 <= 8) {
			possible_positions.push_back({ i + 1,j + 1 });
		}		
		else if (!white && is_diag_right && i - 1 > 0 && j + 1 <= 8) {
			possible_positions.push_back({ i - 1,j + 1 });
		}
	}

	//Check if piece is putting other player in check
	bool is_checking(int king_location_i, int king_location_j) {
		bool check_on_other_player{ false };
		for (int x{}; x != possible_positions.size(); x++) {
			if (king_location_i == possible_positions[x][0] && king_location_j == possible_positions[x][1] && (possible_positions[x][1] == j + 1 || possible_positions[x][1] == j - 1)) {
				check_on_other_player = true;
			}
		}
		return check_on_other_player;
	}
};
#endif