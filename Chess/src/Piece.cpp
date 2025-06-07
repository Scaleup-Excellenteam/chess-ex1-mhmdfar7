#include "Piece.h"
#include "Board.h"
#include <algorithm>

Piece::Piece(bool isWhite, int row, int col) : isWhite(isWhite), row(row), col(col) {}

bool Piece::getIsWhite() const { return isWhite; }
int Piece::getRow() const { return row; }
int Piece::getCol() const { return col; }
void Piece::setPosition(int newRow, int newCol) { row = newRow; col = newCol; }

bool Piece::isPathClear(int destRow, int destCol, const Board& board) const {
    int rowStep = (destRow > row) ? 1 : (destRow < row) ? -1 : 0;
    int colStep = (destCol > col) ? 1 : (destCol < col) ? -1 : 0;

    int steps = std::max(abs(destRow - row), abs(destCol - col));

    int currentRow = row + rowStep;
    int currentCol = col + colStep;

    for (int i = 0; i < steps - 1; ++i) {
        if (board.getPiece(currentRow, currentCol) != nullptr) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }

    return true;
}