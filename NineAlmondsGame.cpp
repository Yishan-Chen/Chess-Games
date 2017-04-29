#include "stdafx.h"
#include "NineAlmondsGame.h"
#include "Enumeration.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;


void NineAlmondsGame::print() {
	cout << *this;
}

void NineAlmondsGame::initialize()
{
	
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			int index = i*width + j;
			game_piece game_pieces;
			if ((index > 5 && index < 9) || (index > 10 && index < 14) || (index > 15 && index < 19)) {
				game_pieces.display_way = "A";
				if (game_pieces.display_way.length() > longestPiecesLength) {
					longestPiecesLength = game_pieces.display_way.length();
				}
				game_pieces.color = piece_color::brown;
				game_pieces.piece_name = "almond";
				game_board.push_back(game_pieces);
			}
			else {
				game_pieces.display_way = " ";
				game_board.push_back(game_pieces);
			}
		}
	}
}

// initial the game aboard when every instance of NineAlmondsGame is created
NineAlmondsGame::NineAlmondsGame() {
	GameBase::width = 5;
	GameBase::height = 5;
	ifstream ifs("NineAlmondsGame.txt");
	if (ifs.is_open()) {
		string state;
		getline(ifs, state);
		if (state == "NineAlmondsGame") {
			for (int i = 0; i < GameBase::width*GameBase::height; i++) {
				game_piece game_piece;
				string game_display_way;
				getline(ifs, game_display_way);
				game_piece.display_way = game_display_way;
				game_board.push_back(game_piece);
			}
		}
		else { NineAlmondsGame::initialize(); }
	}
	else { NineAlmondsGame::initialize(); }
}

// check whether the game is completed 
bool NineAlmondsGame::done() {
	bool check = false;
	if (game_board[12].display_way == "A") {
		check = true;
	}
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			int index = i*width + j;
			if (game_board[index].display_way == "A" && index != 12) {
				check = false;
			}
		}
	}
	if (check) {
		ofstream ofs("NineAlmondsGame.txt");
		if (ofs.is_open()) {
			ofs << "Game Completed";
			ofs.close();
		}
		else { throw file_open_fail;}
	}
	return check;
}

//check whether there are still any remaining valid moves
bool NineAlmondsGame::statement() {
	bool check = true;
	if (done()) {
		check = false;
	}
	for (int startIndex = 0; startIndex < width * height; startIndex++) {
		for (int endIndex = 0; endIndex < width * height; endIndex++) {
			int distance = abs(endIndex - startIndex);
			int middleIndex = (startIndex + endIndex) / 2;
			if (game_board[startIndex].display_way == "A" && game_board[endIndex].display_way == " " &&
				game_board[middleIndex].display_way == "A" && (distance == 2 || distance == 8 || distance == 10 || distance == 12)) {
				check = false;
			}
		}
	}
	if (check) {
		ofstream ofs("NineAlmondsGame.txt");
		if (ofs.is_open()) {
			ofs << "Game completed";
			ofs.close();
		}
		else { throw file_open_fail; }
	}
	return check;
}

// give user the prompt to input
void NineAlmondsGame::prompt(unsigned int &x, unsigned int &y) {
	string input;
	bool run = true;
	while (run) {
		cout << endl << "prompt: \n" << "1.Input a valid coordinate of a square on the board, such as (x,x) \n"
			<< "2. Quit the game(Input 'quit')" << endl;
		cin >> input;

		if (input == "quit") {
			string choice;
			cout << "Do you want to save the game(y/n)" << endl;
			cin >> choice;
			if (choice == "y") {
				ofstream ofs("NineAlmondsGame.txt");
				if (ofs.is_open()) {
					string s = "NineAlmondsGame\n";
					ofs << s;
					for (int i = 0;i < GameBase::height * GameBase::width; i++) {
						ofs << game_board[i].display_way << "\n";
					}
					ofs.close();
				}
				else { throw file_open_fail; }
			}
			else {
				ofstream ofs("NineAlmondsGame.txt");
				if (ofs.is_open()) { 
					ofs << "NO DATA"; 
					ofs.close();
				}
				else { throw file_open_fail; }
			}
			throw user_quit;
		}
		else {
			replace(input.begin(), input.end(), ',', ' ');
			replace(input.begin(), input.end(), '(', ' ');
			replace(input.begin(), input.end(), ')', ' ');
			istringstream iss(input);
			int horizontal;
			int vertical;
			iss >> horizontal;
			iss >> vertical;
			if ((horizontal < 5 && horizontal >= 0) && (vertical < 5 && vertical >= 0)) {
				x = horizontal;
				y = vertical;
				run = false;
			}
			else {
				cout << "invalid coordinate, please input again" << endl;
			}
		}
	}
}

void NineAlmondsGame::emptySquare(unsigned int index) {
	game_board[index].display_way = " ";
	game_board[index].piece_name = " ";
	game_board[index].color = piece_color::noColor;
}

// check whether the current move is valid
void NineAlmondsGame::checkValidMove(unsigned int x, unsigned int y, unsigned int x2, unsigned int y2, bool &validMove) {
	unsigned int startIndex = y*width + x;
	unsigned int endIndex = y2*width + x2;
	double distance = (x2 - x)*(x2 - x) + (y2 - y)*(y2 - y);
	unsigned int middleIndex = ((y2 + y) / 2)*width + (x2 + x) / 2;
	if (game_board[startIndex].display_way == "A" && game_board[endIndex].display_way == " " &&
		game_board[middleIndex].display_way == "A" && (distance == 4 || distance == 8)) {
		emptySquare(startIndex);
		emptySquare(middleIndex);
		game_board[endIndex].display_way = "A";
		game_board[endIndex].piece_name = "almond";
		game_board[endIndex].color = piece_color::brown;
		validMove = true;
	}

}

//this funtion is to move the game pieces
int NineAlmondsGame::turn() {
	try {
		bool validMove = false;
		bool continueMove = false;
		unsigned int x, y;
		unsigned int x2, y2;
		vector<string> coordinates;							// use this vector to hold all the coordinates in a turn	
		while (true) {										// Unless the user quit or there is already one valid move, user will be asked to input one or two coordinates based on the turn
			validMove = false;
			if (continueMove) {
				while (!validMove) {
					cout << endl << "*Tip: Please input one valid coordinate" << endl;
					prompt(x, y);
					checkValidMove(x2, y2, x, y, validMove);
				}
				string third = to_string(x) + "," + to_string(y);
				coordinates.push_back("to");
				coordinates.push_back(third);
				x2 = x;										// if the user choose to continue the move, make the second coorinate in last turn to be the first coordinate in this turn
				y2 = y;
			}
			else {

				while (!coordinates.empty()) {				// pop out all the coordinates in the vector when user choose to start a new turn
					coordinates.pop_back();
				}
				while (!validMove) {
					cout << endl << "Tip: Please input two valid coordinates" << endl;
					prompt(x, y);
					prompt(x2, y2);
					checkValidMove(x, y, x2, y2, validMove);
				};
				string First = to_string(x) + "," + to_string(y);
				string Second = to_string(x2) + "," + to_string(y2);
				coordinates.push_back(First);
				coordinates.push_back("to");
				coordinates.push_back(Second);
				turnCount++;
			}
			cout << *this << endl;								//print out the updated gameboard
			for (unsigned int i = 0; i < coordinates.size(); i++) {
				cout << coordinates[i] << " ";					// print out a single line showing the valid moves that have been made so far that turn
			}
			cout << endl;
			while (true) {
				cout << endl << "Continue this turn (YyNn)";
				string input;
				cin >> input;
				if (input == "y" || input == "Y") {
					continueMove = true;
					break;
				}
				else if (input == "n" || input == "N") {
					continueMove = false;
					if (validMove) {
						return success;
					}
				}
			}
		}
	}
	catch (flowCheck user_quit) {								// catch the user quit from the promt method
		cout << turnCount << " turns were played ";
		return user_quit;
	}
}


ostream & operator<<(ostream &o, const NineAlmondsGame &game) {
	o << endl;
	for (int i = game.height - 1; i >= 0; i--) {
		o << i;
		for (int j = 0; j < game.width; j++) {
			int index = i*game.width + j;
			o << setw(game.longestPiecesLength + 1) << game.game_board[index].display_way;
		}
		o << endl;
	}
	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			o << "X";
		}
		o << setw(game.longestPiecesLength + 1) << i;
	}
	return o;
}