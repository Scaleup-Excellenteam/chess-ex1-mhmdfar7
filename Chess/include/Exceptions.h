#pragma once
#include <stdexcept>
#include <string>

class ChessException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidMoveException : public ChessException {
public:
    InvalidMoveException() : ChessException("Invalid move attempted!") {}
};

class PromotionException : public ChessException {
public:
    PromotionException(int row, int col)
        : ChessException("Promotion required at " + std::to_string(row) + "," + std::to_string(col)) {
    }
};