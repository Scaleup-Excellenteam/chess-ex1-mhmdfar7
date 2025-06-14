#include "King.h"
#include "Board.h"

King::King(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}

bool King::isValidMove(int destRow, int destCol, const Board& board) const {
    int rowDiff = abs(destRow - row);
    int colDiff = abs(destCol - col);

    if (rowDiff <= 1 && colDiff <= 1) {
        Piece* destPiece = board.getPiece(destRow, destCol);
        return !(destPiece && destPiece->getIsWhite() == isWhite);
    }

    if (rowDiff == 0 && colDiff == 2) {
        return board.canCastle(isWhite, destCol > col);
    }

    return false;
}


char King::getSymbol() const { return isWhite ? 'K' : 'k'; }

Piece* King::clone() const {
    return new King(*this);
}
