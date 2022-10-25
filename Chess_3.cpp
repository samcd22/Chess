#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>

//Include header files
#include "Piece.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
#include "Board.h"

//Output operator overloaded to print board
void operator<<(std::ostream& os, board& a_board) {
	std::string black_check_string{""};
	std::string white_check_string{""};
	std::string black_turn_string{""};
	std::string white_turn_string{""};
	
	//Changes check and check mate output
	if (a_board.black_in_check && !a_board.black_in_check_mate) {
		black_check_string = "Check!";
	}
	else if (a_board.black_in_check_mate) {
		black_check_string = "Check Mate!";
	}
	if (a_board.white_in_check && !a_board.white_in_check_mate) {
		white_check_string = "Check!";
	}
	else if (a_board.white_in_check_mate) {
		white_check_string = "Check Mate!";
	}

	//Changes the turn output
	if (a_board.white_turn) {
		white_turn_string = "White turn";
	}
	else {
		black_turn_string = "Black turn";
	}

	//Prints whites taken pieces
	a_board.print_taken_pieces(true);

	//Draws the board
	std::cout << "         A         B         C         D         E         F         G         H                                " + black_turn_string << std::endl;
	std::cout << "   ==================================================================================    " << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||   " << std::endl;
	std::cout << " 8 ||##" + a_board(8, 1) + "##|  " + a_board(8, 2) + "  |##" + a_board(8, 3) + "##|  " + a_board(8, 4) + "  |##" + a_board(8, 5) + "##|  " + a_board(8, 6) + "  |##" + a_board(8, 7) + "##|  " + a_board(8, 8) + "  || 8                         " + black_check_string << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||   " << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||   " << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||   " << std::endl;
	std::cout << " 7 ||  " + a_board(7, 1) + "  |##" + a_board(7, 2) + "##|  " + a_board(7, 3) + "  |##" + a_board(7, 4) + "##|  " + a_board(7, 5) + "  |##" + a_board(7, 6) + "##|  " + a_board(7, 7) + "  |##" + a_board(7, 8) + "##|| 7" << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||              ________________________________" << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||             |              Key               |" << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||             |================================|" << std::endl;
	std::cout << " 6 ||##" + a_board(6, 1) + "##|  " + a_board(6, 2) + "  |##" + a_board(6, 3) + "##|  " + a_board(6, 4) + "  |##" + a_board(6, 5) + "##|  " + a_board(6, 6) + "  |##" + a_board(6, 7) + "##|  " + a_board(6, 8) + "  || 6           |                                |" << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||             |  B -> Black        W -> White  |" << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||             |________________________________|"<< std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||             |                                |" << std::endl;
	std::cout << " 5 ||  " + a_board(5, 1) + "  |##" + a_board(5, 2) + "##|  " + a_board(5, 3) + "  |##" + a_board(5, 4) + "##|  " + a_board(5, 5) + "  |##" + a_board(5, 6) + "##|  " + a_board(5, 7) + "  |##" + a_board(5, 8) + "##|| 5           |  Ki -> King                    |" << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||             |                                |" << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||             |  Qu -> Queen                   |" << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||             |                                |" << std::endl;
	std::cout << " 4 ||##" + a_board(4, 1) + "##|  " + a_board(4, 2) + "  |##" + a_board(4, 3) + "##|  " + a_board(4, 4) + "  |##" + a_board(4, 5) + "##|  " + a_board(4, 6) + "  |##" + a_board(4, 7) + "##|  " + a_board(4, 8) + "  || 4           |  Bi -> Bishop                  |"<< std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||             |                                |" << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||             |  Kn -> Knight                  |" << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||             |                                |" << std::endl;
	std::cout << " 3 ||  " + a_board(3, 1) + "  |##" + a_board(3, 2) + "##|  " + a_board(3, 3) + "  |##" + a_board(3, 4) + "##|  " + a_board(3, 5) + "  |##" + a_board(3, 6) + "##|  " + a_board(3, 7) + "  |##" + a_board(3, 8) + "##|| 3           |  Ro -> Rook                    |" << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||             |                                |" << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||             |  Pa -> Pawn                    |" << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||             |________________________________|" << std::endl;
	std::cout << " 2 ||##" + a_board(2, 1) + "##|  " + a_board(2, 2) + "  |##" + a_board(2, 3) + "##|  " + a_board(2, 4) + "  |##" + a_board(2, 5) + "##|  " + a_board(2, 6) + "  |##" + a_board(2, 7) + "##|  " + a_board(2, 8) + "  || 2 " << std::endl;
	std::cout << "   ||#########|         |#########|         |#########|         |#########|         ||   " << std::endl;
	std::cout << "   ||-------------------------------------------------------------------------------||   " << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||   " << std::endl;
	std::cout << " 1 ||  " + a_board(1, 1) + "  |##" + a_board(1, 2) + "##|  " + a_board(1, 3) + "  |##" + a_board(1, 4) + "##|  " + a_board(1, 5) + "  |##" + a_board(1, 6) + "##|  " + a_board(1, 7) + "  |##" + a_board(1, 8) + "##|| 1                         " + white_check_string << std::endl;
	std::cout << "   ||         |#########|         |#########|         |#########|         |#########||   " << std::endl;
	std::cout << "   ===================================================================================                          " + white_turn_string << std::endl;
	std::cout << "         A         B         C         D         E         F         G         H         " << std::endl;

	//Prints whites taken pieces
	a_board.print_taken_pieces(false);
};

//Input operator overload
std::vector<int> input() {

	char letters[8] = { 'A','B','C','D','E','F','G','H' };
	int numbers[8] = { 1,2,3,4,5,6,7,8 };
	std::map<char, int> input_key;
	for (int i{}; i < 8; i++) {
		input_key[letters[i]] = numbers[i];
	}
	std::cout << "Enter coordinates of the piece you want to move followed by where you want to move it to, (e.g A1 A2): ";
	std::cin;
	char letter_1, letter_2;
	int number_1, number_2;
	std::cin >> letter_1;
	std::cin >> number_1;
	std::cin >> letter_2;
	std::cin >> number_2;
	std::cin.clear();
	return { number_1 , input_key[letter_1] ,  number_2 ,input_key[letter_2] };
}

//Driving main function
int main()
{
	//Define initial list of pieces
	piece** piece_list = new piece * [32];
	piece_list[0] = new rook{ 1,1,true }; piece_list[1] = new knight{ 1,2,true }; piece_list[2] = new bishop{ 1,3,true }; piece_list[3] = new queen{ 1,4,true };
	piece_list[4] = new king{ 1,5,true }; piece_list[5] = new bishop{ 1,6,true }; piece_list[6] = new knight{ 1,7,true }; piece_list[7] = new rook{ 1,8,true };
	piece_list[8] = new pawn{ 2,1,true }; piece_list[9] = new pawn{ 2,2,true }; piece_list[10] = new pawn{ 2,3,true }; piece_list[11] = new pawn{ 2,4,true };
	piece_list[12] = new pawn{ 2,5,true }; piece_list[13] = new pawn{ 2,6,true }; piece_list[14] = new pawn{ 2,7,true }; piece_list[15] = new pawn{ 2,8,true };
	piece_list[16] = new pawn{ 7,1,false }; piece_list[17] = new pawn{ 7,2,false }; piece_list[18] = new pawn{ 7,3,false }; piece_list[19] = new pawn{ 7,4,false };
	piece_list[20] = new pawn{ 7,5,false }; piece_list[21] = new pawn{ 7,6,false }; piece_list[22] = new pawn{ 7,7,false }; piece_list[23] = new pawn{ 7,8,false };
	piece_list[24] = new rook{ 8,1,false }; piece_list[25] = new knight{ 8,2,false }; piece_list[26] = new bishop{ 8,3,false }; piece_list[27] = new queen{ 8,4,false };
	piece_list[28] = new king{ 8,5,false };	piece_list[29] = new bishop{ 8,6,false };	piece_list[30] = new knight{ 8,7,false }; piece_list[31] = new rook{ 8,8,false };

	//Initialises the board
	board a{ piece_list,32 };

	//Initially prints the board
	std::cout << a;

	//Loops through until someone is in checkmate
	while (a.check_mate() == 0) {
		std::vector<int> input_coordinates{ input() };
		int original_position[2]{ input_coordinates[0],input_coordinates[1] };
		int final_position[2]{ input_coordinates[2],input_coordinates[3] };
		board b = a.move_piece(original_position, final_position);
		Sleep(2000);
		b.pawn_promotion();
		b.check_for_check();
		b.check_for_check_mate();
		system("CLS");
		a = b;
		std::cout << a;
	}

	//Prints the final results
	if (a.check_mate() == 1) {
		std::cout << "=============================  Black, you win!!!  =======================================" << std::endl;
	}
	else {
		std::cout << "=============================  White, you win!!!  =======================================" << std::endl;
	}
}
