#pragma once
#ifndef GameBase_H
#define GameBase_H


#include <vector>
#include <string>
#include <memory>


using namespace std;

enum piece_color { red, black, white, brown, noColor, invalid };

struct game_piece {
	int value;
	piece_color color;
	string piece_name;
	string display_way;
};

class GameBase {
protected:
	int height;
	int width;
	int initial;
	int turnCount = 0;
	static shared_ptr<GameBase> sp;
	size_t longestPiecesLength;
	vector<game_piece> game_board;
public:
	GameBase();
	virtual void print() = 0;
	virtual void initialize() = 0;
	virtual bool done() = 0;
	virtual bool statement() = 0;
	virtual void prompt(unsigned int &x, unsigned int &y);
	virtual int turn() = 0;
	int play();
	static void fun(int argc, char* argv[]);
	static shared_ptr<GameBase> instance();
};



#endif



