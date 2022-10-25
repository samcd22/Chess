#pragma once
#ifndef PIECE_H
#define PIECE_H

//Defining the base piece class
class piece {
protected:
	std::vector<std::vector<int>> possible_positions;
	int i{ 1 };
	int j{ 1 };
	bool white{ true };
	bool has_moved{ false };
	std::string name{ "" };
	bool _king{ false };
	bool _rook{ false };
	bool _pawn{ false };
	bool piece_taken{ false };
public:
	//Initialises the virtual functions
	piece() {}
	virtual ~piece() {}
	virtual void calc_possible_positions(piece* piece_list[], int num_pieces, bool white_turn) = 0;
	virtual bool is_checking(int king_location_i, int king_location_j) = 0;
	virtual piece* clone() = 0;

	//Get variables
	std::string get_name() { return name; }
	int get_i() { return i; }
	int get_j() { return j; }
	bool is_white() { return white; }
	std::vector<std::vector<int>> get_possible_positions() { return possible_positions; }
	bool is_king() { return _king; }
	bool is_rook() { return _rook; }
	bool is_pawn() { return _pawn; }

	bool check_if_moved() { return has_moved; }

	//Change the position of the piece
	void change_position(int new_position[2]) {
		i = new_position[0];
		j = new_position[1];
		has_moved = true;
	}

	//Take piece
	void take_piece() { piece_taken = true; }

	//Get piece status
	bool get_piece_taken() { return piece_taken; }


	//Copy constructor
	piece(piece& new_piece) {
		i = new_piece.i;
		j = new_piece.j;
		name = new_piece.name;
		white = new_piece.white;
		has_moved = new_piece.has_moved;
		possible_positions = new_piece.possible_positions;
		_king = new_piece._king;
		_rook = new_piece._rook;
		_pawn = new_piece._pawn;
		piece_taken = new_piece.piece_taken;
	}
};
#endif