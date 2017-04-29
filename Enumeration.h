#pragma once
#ifndef ENUMERATION
#define ENUMERATION
#include <string>
#include <vector>
#include <iostream>
#include "NineAlmondsGame.h"
using namespace std;


enum  array_indice { programName, input_file_name, numOfCommdLineArg };
enum  flowCheck {
	success,
	wrong_num_argv,
	file_open_fail,
	file_getline_fail,
	extract_Xdimen_fail,
	extract_Ydimen_fail,
	no_game_piece,
	exceed_gameboard_dimen,
	user_quit,
	invalid_input,
	no_valid_move,
	no_object_constructed,
	sum_not_equal,
	null_ptr,
	wrong_game_name,
	invalid_move,
	no_such_player
};


enum  argument { program_name = 0, file_name = 1, num_of_argv = 2 };
int usageMessg(char* progName);
int parse_input_file(vector<string>& result, char *fileName);
ostream& insertOpera(ostream &o, const NineAlmondsGame &game);

#endif
