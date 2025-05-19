#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece {
public:
    Knight(int line, int column, bool color, int nMove) : Piece(line, column, color, nMove) {}

    string getName() const override { return "Knight"; }

    string getSymbole() const override { return getColor() ? "♘" : "♞"; }

    bool isValidMovement(int destLine, int destColumn, const Board& /*board*/) const override {
    int dL = abs(destLine - getLine());
    int dC = abs(destColumn - getColumn());
    return (dL == 2 && dC == 1) || (dL == 1 && dC == 2);
}
};

#endif // KNIGHT_HPP
