#pragma once

#include "Board.h"
#include "Move.h"

class MoveEvaluator {
public:
    explicit MoveEvaluator(int plyDepth)
        : depth(plyDepth) {
    }

    int score(const Move& m, const Board& b) const;

private:
    int depth;
    int materialCount(const Board& b) const;
};
