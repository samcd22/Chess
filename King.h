#pragma once
#ifndef KING_H
#define KING_H

//Defining the derived class king
class king : public piece {
public:
	//Parameterised constructor
	king(int i_in, int j_in, bool is_white) {
		i = i_in;
		j = j_in;
		white = is_white;
		if (white) {
			name = " WKi ";
		}
		else {
			name = " BKi ";
		}
		_king = true;
	}

	//Clone function overide
	piece* clone() {
		return new king{ *this };
	}

	//Copy constructor
	king(king& new_king) :
		piece(new_king) {}

	//Calculating the possible positions
	void calc_possible_positions(piece* piece_list[], int num_pieces, bool white_turn) {
		possible_positions.clear();
		bool piece_in_position[9]{ false,false,false,false,false,false,false,false,false };
		bool piece_in_castle_positions[2]{ false,false };
		bool rook_in_position{ false };

		//Looping through each piece in the piece list
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int piece_position_i{ piece_list[x]->get_i() };
				int piece_position_j{ piece_list[x]->get_j() };
				bool piece_white{ piece_list[x]->is_white() };
				int piece_in_position_index{ 0 };

				//Checks for pieces in all 8 places a king can move
				for (int plus_i{ -1 }; plus_i <= 1; plus_i++) {
					for (int plus_j{ -1 }; plus_j <= 1; plus_j++) {
						if (piece_position_i == i + plus_i && piece_position_j == j + plus_j && piece_white == white) {
							piece_in_position[piece_in_position_index] = true;
						}
						piece_in_position_index++;
					}
				}
				//Checks if right rook has moved
				if (white && piece_list[x]->is_rook() && piece_position_i == 1 && piece_position_j == 8 && !piece_list[x]->check_if_moved()) {
					rook_in_position = true;
				}
				if (!white && piece_list[x]->is_rook() && piece_position_i == 8 && piece_position_j == 8 && !piece_list[x]->check_if_moved()) {
					rook_in_position = true;
				}
				//Checking there are pieces between the rook and king 
				if (white && piece_position_i == 1 && piece_position_j == 6) {
					piece_in_castle_positions[0] = true;
				}
				else if (!white && piece_position_i == 8 && piece_position_j == 6) {
					piece_in_castle_positions[0] = true;
				}
				//Checking whether there are pieces between the king and the king side rook
				if (white && piece_position_i == 1 && piece_position_j == 7) {
					piece_in_castle_positions[1] = true;
				}
				else if (!white && piece_position_i == 8 && piece_position_j == 7) {
					piece_in_castle_positions[1] = true;
				}
			}
		}

		//Constrains the motion of the king
		int count{ 0 };
		for (int x{ -1 }; x <= 1; x++) {
			for (int y{ -1 }; y <= 1; y++) {
				if (!(x == 0 && y == 0)) {
					if (!piece_in_position[count]) {
						int new_i = i + x;
						int new_j = j + y;
						if (new_i > 0 && new_i <= 8 && new_j > 0 && new_j <= 8) {
							possible_positions.push_back({ new_i,new_j });
						}
					}
				}
				count++;
			}
		}

		//Add castling option
		if (!piece_in_castle_positions[0] && !piece_in_castle_positions[1] && rook_in_position) {
			possible_positions.push_back({ i,j + 2 });
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