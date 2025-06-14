#include "Rook.h"
#include "Board.h"

Rook::Rook(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}

bool Rook::isValidMove(int destRow, int destCol, const Board& board) const {
    if (row != destRow && col != destCol) return false;
    if (!isPathClear(destRow, destCol, board)) return false;
    Piece* destPiece = board.getPiece(destRow, destCol);
    return !(destPiece && destPiece->getIsWhite() == isWhite);
}

char Rook::getSymbol() const { return isWhite ? 'R' : 'r'; }

Piece* Rook::clone() const {
    return new Rook(*this);
}

