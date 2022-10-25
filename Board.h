#pragma once
#ifndef BOARD_H
#define BOARD_H

//Defining the class board
class board {
private:
	//Private variables
	std::string* board_data{ new std::string[64] };
	piece** piece_list{ nullptr };
	int num_pieces{ 32 };
	std::string white_space = "#####";
	std::string black_space = "     ";
	bool white_turn{ true };
	bool white_in_check{ false };
	bool black_in_check{ false };
	bool white_in_check_mate{ false };
	bool black_in_check_mate{ false };
	std::vector<int> white_king_location{ 1,1 };
	std::vector<int> black_king_location{ 8,8 };
public:
	//Initialising friend functions
	friend void operator<<(std::ostream& os, board& a_board);

	//Default constructor
	board() {}

	//Parameterised constrictor
	board(piece* piece_list_in[], int num_pieces) {
		for (int i{ 1 }; i <= 8; i++) {
			for (int j{ 1 }; j <= 8; j++) {
				if (i % 2 ^ j % 2) {
					board_data[index(i, j)] = white_space;
				}
				else {
					board_data[index(i, j)] = black_space;
				}
			}
		}
		piece_list = new piece * [num_pieces];
		for (int x{}; x < num_pieces; x++) {
			piece_list[x] = piece_list_in[x]->clone();
			if (!piece_list_in[x]->get_piece_taken()) {
				int i{ piece_list_in[x]->get_i() };
				int j{ piece_list_in[x]->get_j() };
				board_data[index(i, j)] = piece_list_in[x]->get_name();
				if (piece_list[x]->is_king() && piece_list_in[x]->is_white()) {
					white_king_location[0] = piece_list_in[x]->get_i();
					white_king_location[1] = piece_list_in[x]->get_j();
				}
				if (piece_list[x]->is_king() && !piece_list_in[x]->is_white()) {
					black_king_location[0] = piece_list_in[x]->get_i();
					black_king_location[1] = piece_list_in[x]->get_j();
				}
			}
		}
	}

	//Copy constructor
	board(const board& a_board) {
		delete[] board_data; delete[] piece_list;
		board_data = nullptr; piece_list = nullptr;
		white_in_check = a_board.white_in_check;
		black_in_check = a_board.black_in_check;
		white_in_check_mate = a_board.white_in_check_mate;
		black_in_check_mate = a_board.black_in_check_mate;
		white_turn = a_board.white_turn;
		white_king_location = a_board.white_king_location;
		black_king_location = a_board.black_king_location;
		piece_list = new piece * [num_pieces];
		board_data = new std::string[64];
		for (int i{ 1 }; i <= 8; i++) {
			for (int j{ 1 }; j <= 8; j++) {
				if (i % 2 ^ j % 2) {
					board_data[index(i, j)] = white_space;
				}
				else {
					board_data[index(i, j)] = black_space;
				}
			}
		}
		for (int x{}; x < num_pieces; x++) {
			piece_list[x] = a_board.piece_list[x]->clone();
		}
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int i{ a_board.piece_list[x]->get_i() };
				int j{ a_board.piece_list[x]->get_j() };
				board_data[index(i, j)] = a_board.piece_list[x]->get_name();
				if (piece_list[x]->is_king() && piece_list[x]->is_white()) {
					white_king_location[0] = a_board.piece_list[x]->get_i();
					white_king_location[1] = a_board.piece_list[x]->get_j();
				}
				if (piece_list[x]->is_king() && !piece_list[x]->is_white()) {
					black_king_location[0] = a_board.piece_list[x]->get_i();
					black_king_location[1] = a_board.piece_list[x]->get_j();
				}
			}
		}
	}

	//Copy assignment
	board operator=(const board& a_board) {
		if (&a_board == this) { return *this; }
		delete[] board_data; delete[] piece_list;
		board_data = nullptr; piece_list = nullptr;
		white_in_check = a_board.white_in_check;
		black_in_check = a_board.black_in_check;
		white_in_check_mate = a_board.white_in_check_mate;
		black_in_check_mate = a_board.black_in_check_mate;
		white_turn = a_board.white_turn;
		white_king_location = a_board.white_king_location;
		black_king_location = a_board.black_king_location;
		piece_list = new piece * [num_pieces];
		board_data = new std::string[64];
		for (int i{ 1 }; i <= 8; i++) {
			for (int j{ 1 }; j <= 8; j++) {
				if (i % 2 ^ j % 2) {
					board_data[index(i, j)] = white_space;
				}
				else {
					board_data[index(i, j)] = black_space;
				}
			}
		}
		for (int x{}; x < num_pieces; x++) {
			piece_list[x] = a_board.piece_list[x]->clone();
		}
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				int i{ a_board.piece_list[x]->get_i() };
				int j{ a_board.piece_list[x]->get_j() };
				board_data[index(i, j)] = a_board.piece_list[x]->get_name();
				if (piece_list[x]->is_king() && piece_list[x]->is_white()) {
					white_king_location[0] = a_board.piece_list[x]->get_i();
					white_king_location[1] = a_board.piece_list[x]->get_j();
				}
				if (piece_list[x]->is_king() && !piece_list[x]->is_white()) {
					black_king_location[0] = a_board.piece_list[x]->get_i();
					black_king_location[1] = a_board.piece_list[x]->get_j();
				}
			}
		}
		return *this;
	}

	//Destructor
	~board() {}

	//Checks if either player in check
	void check_for_check() {
		//Initially reset the check statuses to false
		white_in_check = false;
		black_in_check = false;
		//Loop through all of the pieces in the piece list to check their possible positions and check for check
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				//Calculate the possible positions of the white pieces
				piece_list[x]->calc_possible_positions(piece_list, num_pieces, white_turn);

				//Calculate the possible positions of the black pieces
				piece_list[x]->calc_possible_positions(piece_list, num_pieces, !white_turn);

				//Checking if each piece is putting the other player in check
				if (piece_list[x]->is_checking(white_king_location[0], white_king_location[1]) && !piece_list[x]->is_white()) {
					white_in_check = true;
				}
				if (piece_list[x]->is_checking(black_king_location[0], black_king_location[1]) && piece_list[x]->is_white()) {
					black_in_check = true;
				}
			}
		}
	}

	//Move piece function definition
	board move_piece(int original_position[2], int final_position[2]) {

		//Initialises variables
		bool original_is_piece{ false };
		int original_piece_list_index;
		bool final_is_opposite_piece{ false };
		int final_piece_list_index;
		bool free_move{ false };
		int castling{ 0 };
		int white_rook_index;
		int black_rook_index;

		//First loop through all of the pieces in the piece list to find positions
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()) {
				bool piece_in_original_place{ piece_list[x]->get_i() == original_position[0] && piece_list[x]->get_j() == original_position[1] };
				bool piece_in_final_place{ piece_list[x]->get_i() == final_position[0] && piece_list[x]->get_j() == final_position[1] };
				bool piece_is_same_colour{ piece_list[x]->is_white() == white_turn };

				//Check if the original position has a valid piece
				if (piece_in_original_place && piece_is_same_colour) {
					original_is_piece = true;
					original_piece_list_index = x;
				}

				//Check if the final position has a opposite piece
				if (piece_in_final_place && !piece_is_same_colour) {
					final_is_opposite_piece = true;
					final_piece_list_index = x;
				}

				//Find location o the white king
				if (piece_list[x]->is_king() && piece_list[x]->is_white()) {
					white_king_location[0] = piece_list[x]->get_i();
					white_king_location[1] = piece_list[x]->get_j();
				}

				//Find location o the black king
				if (piece_list[x]->is_king() && !piece_list[x]->is_white()) {
					black_king_location[0] = piece_list[x]->get_i();
					black_king_location[1] = piece_list[x]->get_j();
				}

				//Finding the index of both rooks in the piece list
				if (piece_list[x]->is_rook() && piece_list[x]->is_white() && piece_list[x]->get_i() == 1 && piece_list[x]->get_j() == 8) {
					white_rook_index = x;
				}
				if (piece_list[x]->is_rook() && !piece_list[x]->is_white() && piece_list[x]->get_i() == 8 && piece_list[x]->get_j() == 8) {
					black_rook_index = x;
				}
			}
		}

		//Checks if there is a piece of the correct colour in the original location
		if (original_is_piece) {
			piece_list[original_piece_list_index]->calc_possible_positions(piece_list, num_pieces, white_turn);
			//Loops through every position the piece can go
			std::vector<std::vector<int>> possible_positions{ piece_list[original_piece_list_index]->get_possible_positions() };
			for (int i{}; i != possible_positions.size(); i++) {

				//If the imputted final position is an impossible position we set the possible move to false
				if (final_position[0] == possible_positions[i][0] && final_position[1] == possible_positions[i][1]) {
					free_move = true;
				}

				//Checks if the inputted move is a castling move
				if (piece_list[original_piece_list_index]->is_king() && possible_positions[i][1] == piece_list[original_piece_list_index]->get_j() + 2 && piece_list[original_piece_list_index]->is_white()) {
					castling = 1;
				}
				else if (piece_list[original_piece_list_index]->is_king() && possible_positions[i][1] == piece_list[original_piece_list_index]->get_j() + 2 && !piece_list[original_piece_list_index]->is_white()) {
					castling = 2;
				}
			}

			//Created a copy of the board to manipulate
			board new_board{ *this };

			//Changes the position of the required rook if the move requires castling
			if (castling == 1) {
				int new_rook_position[2]{ 1,6 };
				new_board.piece_list[white_rook_index]->change_position(new_rook_position);
			}
			if (castling == 2) {
				int new_rook_position[2]{ 8,6 };
				new_board.piece_list[black_rook_index]->change_position(new_rook_position);
			}

			//Changes the position of the relevant piece if the move is allowed
			if (free_move) {
				new_board.piece_list[original_piece_list_index]->change_position(final_position);
				if (final_is_opposite_piece) {
					new_board.piece_list[final_piece_list_index]->take_piece();
				}

				//Change turn
				new_board.change_turn();

				//Copies the board and checks is either player is in check
				board new_new_board{ new_board };
				new_new_board.check_for_check();

				//If the move is possible, then we return the new version of the board
				if ((white_turn && !new_new_board.white_in_check) || (!white_turn && !new_new_board.black_in_check)) {
					std::cout << "Moving piece" << std::endl;
					return new_new_board;
				}
				//If the move is not possible due to check, then we return the old version of the board
				else { std::cout << "Invalid move, you're in check, or you're putting yourself in check" << std::endl; 
					return *this;
				}
			}

			//If the move is not possible due to the restriction of the piece's movement, then we return the old version of the board
			else {
				std::cout << "Invalid move, the piece can't move that way" << std::endl;
				return *this;
			}

		}

		//If the inputted starting location does not contain a piece of the relevant colour, then we return the old version of the board
		else {
			std::cout << "Invalid, starting tile does not contain a piece of the relevant colour" << std::endl;
			return *this;
		}
	}
	
	//Adds the functionality of promoting a pawn when it reaches the other end of the board
	void pawn_promotion() {
		//Loops through each piece and checks if any pawns have reached the opposite end
		for (int x{}; x < num_pieces; x++) {
			if (!piece_list[x]->get_piece_taken()){
				if (piece_list[x]->is_pawn() && ((piece_list[x]->is_white() && piece_list[x]->get_i() == 8) || (!piece_list[x]->is_white() && piece_list[x]->get_i() == 1))) {
					int pawn_index{ x };
					int pawn_i{ piece_list[x]->get_i() };
					int pawn_j{ piece_list[x]->get_j() };
					bool pawn_white{ piece_list[x]->is_white() };
					bool input_correct{ false };
					std::string input_string;
					//Checks for valid input
					while (!input_correct) {
						system("CLS");
						std::cout << *this;
						std::cout << "What piece would you like to exchange? (e.g. Queen): ";
						std::cin.clear();
						std::cin >> input_string;
						if (input_string == "Queen" || input_string == "Rook" || input_string == "Bishop" || input_string == "Knight") {
							input_correct = true;
						}
						else {
							input_correct = false;
							std::cout << "Invalid input, try again!";

						}
						Sleep(2000);
					}
					//Changes the piece in the piece list to the input piece
					delete piece_list[pawn_index];
					if (input_string == "Queen") {
						piece_list[pawn_index] = new queen{ pawn_i,pawn_j,pawn_white };
					}
					else if (input_string == "Bishop") {
						piece_list[pawn_index] = new bishop{ pawn_i,pawn_j,pawn_white };
					}
					else if (input_string == "Knight") {
						piece_list[pawn_index] = new knight{ pawn_i,pawn_j,pawn_white };
					}
					else {
						piece_list[pawn_index] = new rook{ pawn_i,pawn_j,pawn_white };
					}
				}
			}
		}
	}

	//Access function
	int index(int m, int n) const {
		if (m > 0 && m <= 8 && n > 0 && n <= 8) {
			return (n - 1) + (m - 1) * 8;
		}
		else {
			std::cout << "Error: out of range" << std::endl;
			exit(1);
		}
	}

	//Overloading the round bracket operator
	std::string operator()(int m, int n) const { return board_data[index(m, n)]; }

	//Change turn function definition
	void change_turn() {
		if (white_turn) {
			white_turn = false;
		}
		else {
			white_turn = true;
		}
	}

	//Prints the taken pieces for a specific player
	void print_taken_pieces(bool white_taken_pieces) {
		int count{ 0 };
		//Loops through each piece and check if it has been taken ans if it is the cotrrect colour
		for (int x{}; x < num_pieces; x++) {
			if (piece_list[x]->get_piece_taken() && piece_list[x]->is_white() == white_taken_pieces) {
				std::cout << piece_list[x]->get_name() << "  ";
				count++;
			}
		}
		if (count == 0) {
			std::cout << "No taken pieces" << std::endl << std::endl;
		}
		else {
			std::cout<< std::endl << std::endl;
		}
	}

	//Function that checks anyone has won
	void check_for_check_mate() {
		if (white_in_check && white_turn) {
			white_in_check_mate = true;
			int x{ 0 };
			//Loops through each white piece and checks whether any move it can make will take white out of check
			while(white_in_check_mate){
				if (piece_list[x]->is_white() && !piece_list[x]->get_piece_taken()) {
					piece_list[x]->calc_possible_positions(piece_list, num_pieces, white_turn);
					//Loops through every position the piece can go
					std::vector<std::vector<int>> possible_positions{ piece_list[x]->get_possible_positions() };
					for (int y{}; y != possible_positions.size(); y++) {
						board new_board{ *this };
						int changed_position[2]{ possible_positions[y][0],possible_positions[y][1] };
						new_board.piece_list[x]->change_position(changed_position);
						board new_new_board{ new_board };
						new_new_board.check_for_check();
						if (!new_new_board.white_in_check) {
							white_in_check_mate = false;
						}
					}
				}
				x++;
				if (x == num_pieces) {
					break;
				}
			}
		}
		else if (black_in_check && !white_turn) {
			black_in_check_mate = true;
			int x{ 0 };
			while(black_in_check_mate){
				//Loops through each black piece and checks whether any move it can make will take white out of check
				if (!piece_list[x]->is_white() && !piece_list[x]->get_piece_taken()) {
					piece_list[x]->calc_possible_positions(piece_list, num_pieces, white_turn);
					//Loops through every position the piece can go
					std::vector<std::vector<int>> possible_positions{ piece_list[x]->get_possible_positions() };
					for (int y{}; y != possible_positions.size(); y++) {
						board new_board{ *this };
						int changed_position[2]{ possible_positions[y][0],possible_positions[y][1] };
						new_board.piece_list[x]->change_position(changed_position);
						board new_new_board{ new_board };
						new_new_board.check_for_check();
						if (!new_new_board.black_in_check) {
							std::cout << piece_list[x]->get_name() << piece_list[x]->get_i() << piece_list[x]->get_j();
							black_in_check_mate = false;
						}
					}
				}
				x++;
				if (x == num_pieces) {
					break;
				}
			}
		}

	}

	//Function that changes the check mate status of the board
	int check_mate() {
		if (white_in_check_mate) {
			return 1;
		}
		else if (black_in_check_mate) {
			return 2;
		}
		else {
			return 0;
		}
	}

	//End of Class
};
#endif