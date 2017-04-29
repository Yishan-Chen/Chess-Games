#include "stdafx.h"
#include "Enumeration.h"
#include "ReversiGame.h"
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

void ReversiGame::initialize() {

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			int index = i*width + j;
			game_piece gamepiece;
			if (index == 27 || index == 36) {
				gamepiece.display_way = "X";
				gamepiece.color = piece_color::black;
			}
			else if (index == 28 || index == 35) {
				gamepiece.display_way = "O";
				gamepiece.color = piece_color::white;
			}
			else {
				gamepiece.display_way = " ";
				gamepiece.color = piece_color::noColor;
			}
			if (gamepiece.display_way.length() > longestPiecesLength) { longestPiecesLength = gamepiece.display_way.length(); }
			game_board.push_back(gamepiece);

		}
	}
}


ReversiGame::ReversiGame(string &playerone, string &playertwo) : playerone(playerone), playertwo(playertwo) {
	GameBase::width = 8;
	GameBase::height = 8;
	ifstream ifs("Reversi.txt");
	if (ifs.is_open()) {
		string state;
		getline(ifs, state);
		if (state == "Reversi") {
			string player_line, p1, p2;
			getline(ifs, player_line);
			istringstream is(player_line);
			is >> p1 >> p2 >> currentPlayer >> turnCount;

			playerone = p1;
			playertwo = p2;
			
			string display_line;
			getline(ifs, display_line);
			istringstream iss(display_line);
			while (true) {
				string display_way;
				iss >> display_way;
				if (!iss) { break; }
				game_piece game_piece;
				if (display_way == "e") { game_piece.display_way = " "; game_piece.color = noColor; }
				else if (display_way == "X") { game_piece.display_way = display_way; game_piece.color = black; }
				else if (display_way == "O") { game_piece.display_way = display_way; game_piece.color = white; }
				game_board.push_back(game_piece);
			}
			
		}
		else if (state == "NO DATA") { ReversiGame::initialize(); }
	}
	else { ReversiGame::initialize(); }
}

bool validState(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) { return true; }
	else { return false; }
}

bool ReversiGame::checkForAllValidMove(piece_color color) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (checkForSingleValidMove(x, y, color)) { return true; }
		}
	}
	return false;
}
bool ReversiGame::move(int x, int y, piece_color original, string displayway) {
	piece_color  reversed;
	if (original == piece_color::white) { reversed = piece_color::black; }
	else if (original == piece_color::black) { reversed = piece_color::white; }
	if (!checkForSingleValidMove(x, y, original)) { return false; };
	int xIncre, yIncre;
	int index = y*width + x;
	for (yIncre = -1;yIncre < 2; yIncre++) {
		for (xIncre = -1; xIncre < 2; xIncre++) {
			if (yIncre == 0 && xIncre == 0) { continue; }
			int row = x + xIncre;
			int col = y + yIncre;
			if (!validState(row, col)) { continue; }
			int index2 = col*width + row;
			if (game_board[index2].color == reversed) {
				for (int newrow = x + 2 * xIncre, newcol = y + 2 * yIncre; validState(newrow, newcol); newrow += xIncre, newcol += yIncre) {
					int newIndex = newcol * width + newrow;
					if (game_board[newIndex].color == reversed) {
						continue;
					}
					else if (game_board[newIndex].color == original) {
                        if (row <= newrow) {
                            if (col <= newcol) {
                                for (int xsub = x + xIncre, ysub = y + yIncre; xsub <= newrow && ysub <= newcol; xsub += xIncre, ysub += yIncre) {
                                    replaceforpieces(xsub, ysub, original, displayway);
                                }
                            }
                            else {
                                for (int xsub = x + xIncre, ysub = y + yIncre; xsub <= newrow && ysub >= newcol; xsub += xIncre, ysub += yIncre) {
                                    replaceforpieces(xsub, ysub, original, displayway);
                                }
                            }
                        }
                        else {
                            if (col <= newcol) {
                                for (int xsub = x + xIncre, ysub = y + yIncre; xsub >= newrow && ysub <= newcol; xsub += xIncre, ysub += yIncre) {
                                    replaceforpieces(xsub, ysub, original, displayway);
                                }
                            }
                            else {
                                for (int xsub = x + xIncre, ysub = y + yIncre; xsub >= newrow && ysub >= newcol; xsub += xIncre, ysub += yIncre) {
                                    replaceforpieces(xsub, ysub, original, displayway);
                                }
                            }
                        }
						game_board[index].color = original;
						game_board[index].display_way = displayway;
						break;
					}
					else { break; }
				}
			}
		}
	}

	return true;
}

void ReversiGame::replaceforpieces(int xsub, int ysub, piece_color original, string displayway) {
	int subIndex = ysub*width + xsub;
	cout << subIndex << endl;
	game_board[subIndex].color = original;
	game_board[subIndex].display_way = displayway;
}

void ReversiGame::prompt(unsigned int &x, unsigned int &y)
{
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
				ofstream ofs("Reversi.txt");
				if (ofs.is_open()) {
					string s = "Reversi\n" + playerone + " " + playertwo + " " + currentPlayer + " " + to_string(turnCount) + "\n";
					ofs << s;
					string output;
					for (int i = 0;i < height * width; i++) {
						if (game_board[i].display_way == " ") {
							string empty = "e";
							output += empty + " ";
						}
						else {
							output += game_board[i].display_way + " ";
						}
					}
					ofs << output;
					ofs << endl;
					ofs.close();
				}
				else { throw file_open_fail; }
			}
			else {
				ofstream ofs("Reversi.txt");
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


bool ReversiGame::checkForSingleValidMove(int x, int y, piece_color original) {
	piece_color  reversed;
	if (original == piece_color::white) { reversed = piece_color::black; }
	else if (original == piece_color::black) { reversed = piece_color::white; }
	int xIncre, yIncre;
	int index = y*width + x;
	if (game_board[index].display_way != " ") {
		
		return false;
	}
	for (yIncre = -1; yIncre < 2; yIncre++) {
		for (xIncre = -1; xIncre < 2; xIncre++) {
			if (yIncre == 0 && xIncre == 0) {

				continue;
			}
			int row = x + xIncre;
			int col = y + yIncre;
			if (!validState(row, col)) { continue; }
			index = col*width + row;
			if (game_board[index].color == reversed) {
				
				for (int newrow = x + 2 * xIncre, newcol = y + 2 * yIncre; validState(newrow, newcol);newrow += xIncre, newcol += yIncre) {
					int newIndex = newcol * width + newrow;
					if (game_board[newIndex].color == reversed) { continue; }
					else if (game_board[newIndex].color == original) { return true; }
					else {break; }
				}
			}
		}
	}
	return false;
}

bool ReversiGame::done() {
	bool check = false;
	int white_piece_num = 0;
	int black_piece_num = 0;
	for (unsigned int i = 0; i < game_board.size(); i++) {
		if (game_board[i].color == piece_color::black) { white_piece_num++; }
		if (game_board[i].color == piece_color::white) { black_piece_num++; }
	}
	if (white_piece_num == 0 || black_piece_num == 0) { check = true; }
	if ((white_piece_num > black_piece_num && black_piece_num > 0) || (black_piece_num > white_piece_num && white_piece_num > 0)) {
		if (white_piece_num + black_piece_num == game_board.size()) {
			check = true;
		}
		if (!checkForAllValidMove(piece_color::black) && !checkForAllValidMove(piece_color::white)) { check = true; }
	}
	return check;
}

int ReversiGame::turn() {
	
	try {
		if (turnCount == 0 && currentPlayer != playertwo) { currentPlayer = playerone; }
		unsigned int x, y;
		if (currentPlayer == playerone) {
			cout << endl;
			cout << "It's " << currentPlayer << "'s" << " turn to play" << endl;
			if (checkForAllValidMove(piece_color::black)) {
				
				prompt(x, y);
				int moveX = x;
				int moveY = y;
				string display_way = "X";
				if (move(moveX, moveY, piece_color::black, display_way)) {
					print();
					currentPlayer = playertwo;
					turnCount++;
					return success;
				}
				else {
					cout << endl;
					cout << "illegal moves, please input again " << endl;
					print();
					return invalid_move;
				}
			}
			else {
				cout << "No black valid moves" << endl;
				currentPlayer = playertwo;
				return no_valid_move;
			}
		}
		else if (currentPlayer == playertwo) {
			cout << endl;
			cout << "It's " << currentPlayer << "'s" << " turn to play" << endl;
			if (checkForAllValidMove(piece_color::white)) {
				prompt(x, y);
				int moveX = x;
				int moveY = y;
				string display_way = "O";
				if (move(moveX, moveY, piece_color::white, display_way)) {
					print();
					currentPlayer = playerone;
					turnCount++;
					return success;
				}
				else {
					cout << "illegal moves, please input again " << endl;
					print();
					return invalid_move;
				}
			}
			else {
				cout << "No white valid moves" << endl;
				currentPlayer = playerone;
				return no_valid_move;
			}
		}
		else { return no_such_player; }
	}
	catch (flowCheck user_quit) { return user_quit; }
}

bool ReversiGame::statement() {
	bool check = false;
	int white_piece_num = 0;
	int black_piece_num = 0;
	for (unsigned int i = 0; i < game_board.size(); i++) {
		if (game_board[i].color == piece_color::black) { white_piece_num++; }
		if (game_board[i].color == piece_color::white) { black_piece_num++; }
	}
	if (white_piece_num == black_piece_num) {
		if (white_piece_num + black_piece_num == game_board.size()) { check = true; }
		if (!checkForAllValidMove(piece_color::black) && !checkForAllValidMove(piece_color::white)) { check = true; }
	}
	return check;
}

ostream & operator<<(ostream &o, const ReversiGame &game) {
	o << game.game_board.size() << endl;
	o << endl;
	for (int i = game.height - 1; i >= 0; i--) {
		o << i;
		for (int j = 0; j < game.width; j++) {
			int index = i*game.width + j;
			
			o << setw(game.longestPiecesLength + 1) << game.game_board[index].display_way;
		}
		o << endl << endl;
	}
	o << "X";
	for (int i = 0; i < game.width; i++) {
		o << setw(game.longestPiecesLength + 1) << i;
	}
	o << endl;
	return o;
}

void ReversiGame::print() { cout << *this; }
