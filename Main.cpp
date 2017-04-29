// Lab4G.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdexcept>
#include <iostream>
#include "GameBase.h"
#include "Enumeration.h"

using namespace std;

int usageMessag(char* progName) {
	cout << progName << "'s usage: lab4.exe NineAlmonds/MagicBoard" << endl;
	return wrong_num_argv;
}

int main(int argc, char* argv[])
{
	try {
		GameBase::fun(argc, argv);
		shared_ptr<GameBase> game = GameBase::instance();
		int result = game->play();
		return result;
	}
	catch (const flowCheck &e) {
		if (e == wrong_num_argv || e == wrong_game_name) { usageMessag(argv[program_name]); }
		else if (e == null_ptr) { cerr << "Null point exception" << endl; }
		else if (e == file_open_fail) { cerr << "File can't be opened to read or write" << endl; }
		else {}
		return e;
	}
	catch (const bad_alloc &e) { cerr << e.what() << endl; }
}



