#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

class King : public Piece {
public:
    King(int line, int column, bool color, int nMove) : Piece(line, column, color, nMove) {}

    string getName() const override { return "King"; }

    string getSymbole() const override { return getColor() ? "♔" : "♚";}

    bool isValidMovement(int destLine, int destColumn, const Board& board) const override {
        int dL = abs(destLine - getLine());
        int dC = abs(destColumn - getColumn());
    
        if (dL > 1 || dC > 1) return false; // Le roi ne bouge que d'une case max
    
        Piece* target = board.getPiece(destLine, destColumn);
        return target == nullptr || target->getColor() != getColor(); // case vide ou pièce adverse
    }
    
};

#endif // KING_HPP