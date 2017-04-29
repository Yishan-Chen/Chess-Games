#include "stdafx.h"
#include "MagicSquare.h"
#include "GameBase.h"
#include "ReversiGame.h"
#include "Enumeration.h"
#include <iostream>
#include <sstream>
#include <algorithm>
GameBase::GameBase() {
	longestPiecesLength = 1;
};

shared_ptr<GameBase> GameBase::sp = nullptr;

shared_ptr<GameBase> GameBase::instance() {
	if (GameBase::sp == nullptr) { throw null_ptr; }
	return GameBase::sp;
}

int GameBase::play() {
	this->print();
	while (true) {
		if (this->turn() == user_quit) {
			return user_quit;
		}
		if (this->done()) {
			cout << endl << turnCount << " turns it took to complete the game successfully " << endl;
			return success;
		}
		if (this->statement()) {
			cout << turnCount << " turns were played and no valid moves remain";
			return no_valid_move;
		}
	}
};

void GameBase::fun(int argc, char* argv[]) {
	if (argc >= num_of_argv && argc <= 5) {
		if (GameBase::sp != nullptr) { throw null_ptr; }
		if (strcmp(argv[1], "NineAlmonds") == 0) {
			shared_ptr<NineAlmondsGame> game = make_shared<NineAlmondsGame>();
			GameBase::sp = game;
		}
		else if (strcmp(argv[1], "MagicSquare") == 0) {

			int initial = 1;
			int range = 3;

			if (argv[2] != NULL) {
				istringstream iss(argv[2]);
				int w;
				iss >> w;
				range = w;
				if (argv[3] != NULL) {
					istringstream is(argv[3]);
					int i;
					is >> i;
					initial = i;
					

				}
			}
			shared_ptr<MagicSquare> game = make_shared<MagicSquare>(range, initial);
			GameBase::sp = game;
			
		}
		else if (strcmp(argv[1], "Reversi") == 0) {
			if (argv[2] != NULL && argv[3] != NULL) {
				string playerone(argv[2]);
				string playertwo(argv[3]);
				shared_ptr<ReversiGame> game = make_shared<ReversiGame>(playerone, playertwo);
				GameBase::sp = game;
			}
			else { throw wrong_num_argv; }
		}
		else {
			throw wrong_game_name;
		}
	}
	else {
		throw wrong_num_argv;
	}
};

void GameBase::prompt(unsigned int &x, unsigned int &y) {
	string input;
	bool run = true;
	while (run) {
		cout << endl << "prompt: \n" << "1.Input a valid coordinate of a square on the board, such as (x,x) \n"
			<< "2. Quit the game(Input 'quit')" << endl;
		cin >> input;

		if (input == "quit") { throw user_quit; }
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
};