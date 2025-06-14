#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}

bool Bishop::isValidMove(int destRow, int destCol, const Board& board) const {
    if (abs(destRow - row) != abs(destCol - col)) return false;
    if (!isPathClear(destRow, destCol, board)) return false;
    Piece* destPiece = board.getPiece(destRow, destCol);
    return !(destPiece && destPiece->getIsWhite() == isWhite);
}

char Bishop::getSymbol() const { return isWhite ? 'B' : 'b'; }

Piece* Bishop::clone() const {
    return new Bishop(*this);
}
