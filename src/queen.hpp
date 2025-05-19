#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"
#include <iostream>

class Queen : public Piece {
public:
    Queen(int line, int column, bool color,int nMove) : Piece(line, column, color, nMove) {}

    string getName() const override { return "Queen"; }

    string getSymbole() const override { return getColor() ? "♕" : "♛"; }

    bool isValidMovement(int destLine, int destColumn, const Board& board) const override {
        int dL = abs(destLine - getLine());
        int dC = abs(destColumn - getColumn());
    
        bool isDiagonal = (dL == dC);
        bool isStraight = (getLine() == destLine || getColumn() == destColumn);
    
        if (!isDiagonal && !isStraight) return false;
    
        int stepLine = (destLine == getLine()) ? 0 : (destLine > getLine() ? 1 : -1);
        int stepColumn = (destColumn == getColumn()) ? 0 : (destColumn > getColumn() ? 1 : -1);
    
        int l = getLine() + stepLine;
        int c = getColumn() + stepColumn;
    

        while (l != destLine || c != destColumn) {
            if (board.getPiece(l, c) != nullptr) {
                return false;
            }
            l += stepLine;
            c += stepColumn;
        }
    
        Piece* destination = board.getPiece(destLine, destColumn);
        return destination == nullptr || destination->getColor() != getColor();
    }
    
    
};

#endif // QUEEN_HPP