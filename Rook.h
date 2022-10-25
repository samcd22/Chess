#pragma once
#ifndef ROOK_H
#define ROOK_H

//Defining the derived class rook
class rook : public piece {
public:
	//Parameterised constructor 
	rook(int i_in, int j_in, bool is_white) {
		i = i_in;
		j = j_in;
		white = is_white;
		if (white) {
			name = " WRo ";
		}
		else {
			name = " BRo ";
		}
		_rook = true;
	}

	//Clone function overide
	piece* clone() {
		return new rook{*this};
	}

	//Copy constructor
	rook(rook& new_rook) :
		piece(new_rook) {}

	//Calculating the possible positions
	void calc_possible_positions(piece* piece_list[], int num_pieces, bool white_turn) {
		possible_positions.clear();
		int pieces_vertical[8]{ 0,0,0,0,0,0,0,0 }; //0 - No piece, 1 - Same coloured piece, 2 - Different coloured piece
		int pieces_horizontal[8]{ 0,0,0,0,0,0,0,0 }; //0 - No piece, 1 - Same coloured piece, 2 - Different coloured piece

		//Looping through each piece in the piece list
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int piece_position_i{ piece_list[x]->get_i() };
				int piece_position_j{ piece_list[x]->get_j() };
				bool piece_white{ piece_list[x]->is_white() };

				//Checking for pieces vertical
				for (int i_vert{ 1 }; i_vert <= 8; i_vert++) {
					if (piece_position_i == i_vert && piece_position_j == j && piece_white == white) {
						pieces_vertical[i_vert - 1] = 1;
					}
					else if (piece_position_i == i_vert && piece_position_j == j && piece_white != white) {
						pieces_vertical[i_vert - 1] = 2;
					}
				}

				//Checking for pieces horizontal
				for (int j_vert{ 1 }; j_vert <= 8; j_vert++) {
					if (piece_position_i == i && piece_position_j == j_vert && piece_white == white) {
						pieces_horizontal[j_vert - 1] = 1;
					}
					else if (piece_position_i == i && piece_position_j == j_vert && piece_white != white) {
						pieces_horizontal[j_vert - 1] = 2;
					}
				}
			}
		}

		//Checks how far up the rook can move
		int up{ i };
		bool stop_up_loop{ false };
		while (!stop_up_loop) {
			if (up < 8) {
				if (pieces_vertical[up] == 0) {
					possible_positions.push_back({ up + 1,j });
					stop_up_loop = false;
				}
				else if (pieces_vertical[up] == 1) {
					stop_up_loop = true;
				}
				else {
					possible_positions.push_back({ up + 1,j });
					stop_up_loop = true;
				}
				up++;
			}
			else {
				stop_up_loop = true;
			}
		}

		//Checks how far down the rook can move
		int down{ i - 2 };
		bool stop_down_loop{ false };
		while (!stop_down_loop) {
			if (down >= 0) {
				if (pieces_vertical[down] == 0) {
					possible_positions.push_back({ down + 1,j });
					stop_down_loop = false;
				}
				else if (pieces_vertical[down] == 1) {
					stop_down_loop = true;
				}
				else {
					possible_positions.push_back({ down + 1,j });
					stop_down_loop = true;
				}
				down--;
			}
			else {
				stop_down_loop = true;
			}
		}

		//Checks how far right the rook can move
		int right{ j };
		bool stop_right_loop{ false };
		while (!stop_right_loop) {
			if (right < 8) {
				if (pieces_horizontal[right] == 0) {
					possible_positions.push_back({ i ,right + 1 });
					stop_right_loop = false;
				}
				else if (pieces_horizontal[right] == 1) {
					stop_right_loop = true;
				}
				else {
					possible_positions.push_back({ i,right + 1 });
					stop_right_loop = true;
				}
				right++;
			}
			else {
				stop_right_loop = true;
			}
		}

		//Checks how far left the rook can move
		int left{ j - 2 };
		bool stop_left_loop{ false };
		while (!stop_left_loop) {
			if (left >= 0) {
				if (pieces_horizontal[left] == 0) {
					possible_positions.push_back({ i,left + 1 });
					stop_left_loop = false;
				}
				else if (pieces_horizontal[left] == 1) {
					stop_left_loop = true;
				}
				else {
					possible_positions.push_back({ i,left + 1 });
					stop_left_loop = true;
				}
				left--;
			}
			else {
				stop_left_loop = true;
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