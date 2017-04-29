#pragma once
#ifndef MagicSquare_H
#define MagicSquare_H


#include "GameBase.h"

using namespace std;

class MagicSquare :public GameBase {
private:
	vector<game_piece> avaliable_piece;
public:

	int sumOfIntegers;
	MagicSquare(int &range, int &inital);
	virtual void print();
	virtual bool done();
	virtual bool statement();
	void initialize();
	void prompt(int &k);
	void prompt(unsigned int &x, unsigned int &y);
	virtual int turn();
	

	friend ostream & operator<<(ostream &o, const MagicSquare &game);
};

ostream & operator<<(ostream &o, const MagicSquare &game);

#endif
