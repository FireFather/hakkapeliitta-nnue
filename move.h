#ifndef MOVE_H
#define MOVE_H

#include "defs.h"

struct Move
{
	int moveInt; // the move condensed to an int
	int score; // the score of the for move-ordering

	void clear();
    void setFrom(int from);  
    void setTo(int to);  
    void setPiece(int piece);  
    void setCapture(int capture);  
    void setPromotion(int promotion); 
    int getFrom();  
    int getTo();  
    int getPiece();  
    int getCapture();
    int getPromotion();   
	bool isWhitemove();
	bool isBlackmove();
	bool isCapture();
	bool isKingcaptured();
	bool isRookmove();
	bool isRookcaptured();
	bool isKingmove();
	bool isPawnmove();
	bool isPawnDoublemove();
	bool isEnpassant();
	bool isPromotion();
	bool isCastle();
	bool isCastleOO();
	bool isCastleOOO();
};



#endif
