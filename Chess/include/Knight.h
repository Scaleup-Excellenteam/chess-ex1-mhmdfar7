#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite, int row, int col);
    virtual bool isValidMove(int destRow, int destCol, const Board& board) const override;
    virtual char getSymbol() const override;
};