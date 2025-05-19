#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
#include "board.hpp"

class Bishop : public Piece {
public:
    Bishop(int line, int column, bool color, int nMove) : Piece(line, column, color, nMove) {}

    string getName() const override { return "Bishop"; }

    string getSymbole() const override { return getColor() ? "♗" : "♝"; }

    bool isValidMovement(int destLine, int destColumn, const Board& board) const override {
        int stepLine, stepColumn;
        int dL = abs(destLine - getLine());
        int dC = abs(destColumn - getColumn());

        bool isBishopMove = (dL == dC);
        if (!isBishopMove) return false;

        bool nobodyInTheWay = true;
        for (int i = 1; i < dL; i++) {
            stepLine = getLine() + (destLine > getLine() ? i : -i);
            stepColumn = getColumn() + (destColumn > getColumn() ? i : -i);
            if (board.getPiece(stepLine, stepColumn) != nullptr) { 
                nobodyInTheWay = false;
                break;
            }
        }
        
        return nobodyInTheWay;
    }
    
};
#endif // BISHOP_HPP
