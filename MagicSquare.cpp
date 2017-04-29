#include "stdafx.h"
#include "MagicSquare.h"
#include "Enumeration.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

MagicSquare::MagicSquare(int &range, int &inital) {
	GameBase::initial = inital;
	GameBase::width = range;
	GameBase::height = range;
	ifstream ifs("MagicSquare.txt");
	if (ifs.is_open()) {
		//string line = "";
		string state = "";
		getline(ifs, state);
		if (state == "MagicSquare") {
			string display_line;
			getline(ifs, display_line);
			istringstream iss(display_line);
			while (true) {
				string display_way;
				iss >> display_way;
				if (!iss) { break; }
				game_piece game_piece;
				if (display_way == "e") { game_piece.display_way = " "; }
				else { game_piece.display_way = display_way; }
				game_board.push_back(game_piece);
				}
			string avaliable_line;
			getline(ifs, avaliable_line);
			istringstream is(avaliable_line);
			while (true) {
				string avaliable_value;
				is >> avaliable_value;
				if (!is) { break; }
				game_piece game;
				game.value = atoi(avaliable_value.c_str());
				avaliable_piece.push_back(game);
			}
		}
		else if (state == "NO DATA") {
			MagicSquare::initialize();
		}
	}
	else { MagicSquare::initialize(); }
}



void MagicSquare::initialize() {
	sumOfIntegers = (1 + width*height)*width / 2;
	for (int i = 1;i <= width*height;i++) {
		game_piece gp;
		gp.display_way = " ";          //put empty pieces into gameboard
		game_board.push_back(gp);
		gp.value = initial - 1 + i;    //put pieces with values into avaliable_piece
		avaliable_piece.push_back(gp); //gp.avaliable=true;
	}
}

void MagicSquare::print() {
	cout << *this;
}

bool MagicSquare::done() {
	bool check = true;
	for (unsigned int i = 0; i < game_board.size(); i++) {
		if (game_board[i].display_way == " ") { check = false; }
	}
	//sum of row equals 15
	for (int j = 0; j < height; j++) {
		int sum = 0;
		for (int k = 0; k < width; k++) {
			sum += game_board[j * width + k].value;
		}
		if (sum != sumOfIntegers) { 
			check = false;
			
		}
	}
	//sum of column equals 15
	for (int j = 0; j < width; j++) {
		int sum = 0;
		for (int k = 0; k < height; k++) {
			sum += game_board[j + k * height].value;
		}
		if (sum != sumOfIntegers) { check = false; return check; }
	}
	//sum of increasing diagonal equals 15
	int idsum = 0;
	for (int j = 0; j < width; j++) {
		idsum += game_board[j * width + j].value;
	}
	if (idsum != sumOfIntegers) { check = false; return check; }
	//sum of decreasing diagonal equals 15
	int ddsum = 0;
	for (int j = width - 1; j >= 0; --j) {
		ddsum += game_board[j * width + j].value;
	}
	if (ddsum != sumOfIntegers) { check = false; return check; }
	//all sum equals to 15
	cout << "done" << endl;
	if (check) {
		ofstream ofs("MagicSquare.txt");
		if (ofs.is_open()) {
			ofs << "Game Completed";
			ofs.close();
		}
		else { throw file_open_fail; }
	}
	return check;
}
bool MagicSquare::statement() {
	bool check = true;
	for (unsigned int i = 0; i < game_board.size(); i++) {
		if (game_board[i].display_way == " ") { check = false; }
	}

	for (int j = 0; j < height; j++) {
		int sum = 0;
		for (int k = 0; k < width; k++) {
			sum += game_board[j * width + k].value;
		}
		if (sum != sumOfIntegers) { check = false; }
	}

	for (int j = 0; j < width; j++) {
		int sum = 0;
		for (int k = 0; k < height; k++) {
			sum += game_board[j + k * height].value;
		}
		if (sum != sumOfIntegers) { check = false; }
	}
	//sum of increasing diagonal equals 15
	int idsum = 0;
	for (int j = 0; j < width; j++) {
		idsum += game_board[j * width + j].value;
	}
	if (idsum != sumOfIntegers) { check = false; }
	//sum of decreasing diagonal equals 15
	int ddsum = 0;
	for (int j = width - 1; j >= 0; --j) {
		ddsum += game_board[j * width + j].value;
	}
	if (ddsum != sumOfIntegers) { check = false; }
	if (check) {
		ofstream ofs("MagicSquare.txt");
		if (ofs.is_open()) {
			ofs << "Game Completed";
			ofs.close();
		}
		else { throw file_open_fail; }
	}
	return check;
}


void MagicSquare::prompt(unsigned int &x, unsigned int &y) {
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
				ofstream ofs("MagicSquare.txt");
				if (ofs.is_open()) {
					string s = "MagicSquare\n";
					ofs << s;
					string output;
					for (int i = 0;i < height * width; i++) {
						if (game_board[i].display_way == " ") {
							string empty = "e";
							output +=  empty + " ";
						}
						else { output += game_board[i].display_way + " ";}
					}
					ofs << output;
					string available_value;
					for (unsigned int j = 0;j < avaliable_piece.size(); j++) {
						available_value += " " + to_string(avaliable_piece[j].value);
					}
					ofs << endl;
					ofs << available_value;
					ofs.close();
				}
				else { throw file_open_fail; }
			}
			else {
				ofstream ofs("MagicSquare.txt");
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
			if ((horizontal < GameBase::width && horizontal >= 0) && (vertical < GameBase::height && vertical >= 0)) {
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

void MagicSquare::prompt(int &k) {
	cout << "Please enter quit or the value of the piece" << endl;
	string input;
	cin >> input;

	if (input == "quit") {
		string choice;
		cout << "Do you want to save the game(y/n)" << endl;
		cin >> choice;
		if (choice == "y") {
			ofstream ofs("MagicSquare.txt");
			if (ofs.is_open()) {
				string s = "MagicSquare\n";
				ofs << s;
				string output;
				for (int i = 0;i < height * width; i++) {
					if (game_board[i].display_way == " ") {
						string empty = "e";
						output += empty + " ";
					}
					else { output += game_board[i].display_way + " "; }
				}
				ofs << output;
				string available_value;
				for (unsigned int j = 0;j < avaliable_piece.size(); j++) {
					available_value += " " + to_string(avaliable_piece[j].value);
				}
				ofs << endl;
				ofs << available_value;
				ofs.close();
			}
			else { throw file_open_fail; }
		}
		else {
			ofstream ofs("MagicSquare.txt");
			if (ofs.is_open()) {
				ofs << "NO DATA";
				ofs.close();
			}
			else { throw file_open_fail; }
		}
		throw user_quit;
	}
	else {
		istringstream iss(input);
		int value;
		if (iss >> value) {
			//go through all the avaliablee_piece and find the corresponding piece
			bool find = false;
			for (unsigned int i = 0;i < avaliable_piece.size();i++) {
				//the value's corresponding piece is found
				if (avaliable_piece[i].value == value) {
					k = value;
					find = true;
					avaliable_piece.erase(avaliable_piece.begin() + i);
				}
			}
			if (find == false) {
				cout << "The value is not avaliable" << endl;
				//let the user input the value again
				prompt(k);
			}
		}
		else{ cout << "fail extract value" << endl;}
	}
}
int MagicSquare::turn() {

	try{
		unsigned int x, y;
		int k;
		prompt(x, y);
		//if the piece is empty
		if (game_board[x + y*width].display_way == " ") {
			prompt(k);
			game_board[x + y].value = k;
			game_board[x + y*width].display_way = to_string(k);
			turnCount += 1;
			print();
			return success;
		}
		else {
			cout << "The coordinate is not valid" << endl;
			return invalid_input;
		}
	}
	catch (flowCheck user_quit) {								// catch the user quit from the promt method
		cout << turnCount << " turns were played ";
		return user_quit;
	}
}
ostream & operator<<(ostream &o, const MagicSquare &game) {
	o << endl;
	for (int i = game.height - 1; i >= 0; i--) {
		o << i << " ";
		for (int j = 0; j < game.width; j++) {
			int index = i*game.width + j;
			o << setw(game.longestPiecesLength) << game.game_board[index].display_way << " ";
		}
		o << endl;
	}
	for (int i = 0; i < game.height; i++) {
		if (i == 0) {
			o << setw(game.longestPiecesLength) << "X ";
		}
		o << setw(game.longestPiecesLength) << i << " ";
	}
	o << endl;

	//print all avaliable pieces
	o << "Available pieces: ";
	for (unsigned int i = 0; i < game.avaliable_piece.size(); i++) {
		o << game.avaliable_piece[i].value << " ";
	}
	o << endl;
	return o;
}
