#include "MoveEvaluator.h"

static int pieceValue(char ch) {
    switch (tolower(ch)) {
    case 'p': return 100;
    case 'n': case 'b': return 300;
    case 'r': return 500;
    case 'q': return 900;
    case 'k': return 10000;
    default:  return 0;
    }
}

int MoveEvaluator::materialCount(const Board& b) const {
    int score = 0;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (auto p = b.getPiece(r, c)) {
                int val = pieceValue(p->getSymbol());
                score += p->getIsWhite() ? val : -val;
            }
        }
    }
    return score;
}

int MoveEvaluator::score(const Move& m, const Board& b) const {
    Board temp = b;
    temp.makeMove(m.srcRow, m.srcCol, m.dstRow, m.dstCol);
    return materialCount(temp);
}
