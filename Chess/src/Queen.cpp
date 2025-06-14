#include "Queen.h"
#include "Board.h"

Queen::Queen(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}

bool Queen::isValidMove(int destRow, int destCol, const Board& board) const {
    if ((row != destRow && col != destCol) && (abs(destRow - row) != abs(destCol - col))) return false;
    if (!isPathClear(destRow, destCol, board)) return false;
    Piece* destPiece = board.getPiece(destRow, destCol);
    return !(destPiece && destPiece->getIsWhite() == isWhite);
}

char Queen::getSymbol() const { return isWhite ? 'Q' : 'q'; }

Piece* Queen::clone() const {
    return new Queen(*this);
}
