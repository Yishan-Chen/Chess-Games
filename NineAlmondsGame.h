#pragma once
#ifndef NineAlmondsGame_H
#define NIneAlmondsGame_H

#include "gamebase.h"

using namespace std;

class NineAlmondsGame :public GameBase {
public:
	NineAlmondsGame();
	void initialize();
	virtual void print();
	virtual bool done();
	virtual bool statement();
	virtual void prompt(unsigned int &x, unsigned int &y);
	virtual int turn();
	void emptySquare(unsigned int index);
	void checkValidMove(unsigned int x, unsigned int y, unsigned int x2, unsigned int y2, bool &validMove);

	friend ostream & operator<<(ostream &o, const NineAlmondsGame &game);
};

ostream & operator<<(ostream &o, const NineAlmondsGame &game);

#endif