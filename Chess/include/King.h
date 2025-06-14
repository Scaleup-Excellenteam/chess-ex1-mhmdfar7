#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(bool isWhite, int row, int col);
    virtual bool isValidMove(int destRow, int destCol, const Board& board) const override;
    virtual char getSymbol() const override;
    Piece* clone() const override;

};