#pragma once
#ifndef REVERSIGAME_H
#define REVERSIGAME_h

#include "GameBase.h"

using namespace std;

class ReversiGame : public GameBase {
	string playerone;
	string playertwo;
	string currentPlayer;
public:
	ReversiGame(string &playerone, string &playertwo);
	void initialize();
	virtual void print();
	virtual bool statement();
	virtual bool done();
	virtual int turn();
	bool checkForSingleValidMove(int x, int y, piece_color color);
	bool checkForAllValidMove(piece_color color);
	bool move(int x, int y, piece_color color, string displayway);
	void replaceforpieces(int xsub, int ysub, piece_color original, string displayway);
	virtual void prompt(unsigned int &x, unsigned int &y);
	friend ostream & operator<<(ostream &o, const ReversiGame &game);

};

ostream & operator<<(ostream &o, const ReversiGame &game);

#endif
