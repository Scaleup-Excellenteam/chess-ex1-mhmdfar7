#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite, int row, int col);
    virtual bool isValidMove(int destRow, int destCol, const Board& board) const override;
    virtual char getSymbol() const override;
    Piece* clone() const override;

};