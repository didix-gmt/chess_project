#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece {
public:
    Rook(int line, int column, bool color, int nMove) : Piece(line, column, color, nMove) {}

    string getName() const override { return "Rook"; }

    string getSymbole() const override { return getColor() ? "♖" : "♜"; }

    bool isValidMovement(int destLine, int destColumn, const Board& board) const override {
        int startLine = getLine();
        int startColumn = getColumn();
    
        if (startLine != destLine && startColumn != destColumn)
            return false; 
    
        int dL = destLine - startLine;
        int dC = destColumn - startColumn;
    
        int stepLine = (dL == 0) ? 0 : (dL > 0 ? 1 : -1);
        int stepColumn = (dC == 0) ? 0 : (dC > 0 ? 1 : -1);
    
        int l = startLine + stepLine;
        int c = startColumn + stepColumn;
    
        while (l != destLine || c != destColumn) {
            if (board.getPiece(l, c) != nullptr)
                return false;
            l += stepLine;
            c += stepColumn;
        }
    
        Piece* destPiece = board.getPiece(destLine, destColumn);
        if (destPiece != nullptr && destPiece->getColor() == getColor())
            return false;
    
        return true;
    }
    
    
};

#endif // ROOK_HPP