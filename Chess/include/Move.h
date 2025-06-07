#pragma once

struct Move {
    int srcRow, srcCol;
    int dstRow, dstCol;

    std::string toString() const {
        char f1 = 'h' - srcRow;
        char r1 = '1' + srcCol;
        char f2 = 'h' - dstRow;
        char r2 = '1' + dstCol;
        return std::string() + f1 + r1 + f2 + r2;
    }
};
