#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece {
public:
    Pawn(int line, int column, bool color, int nMove) : Piece(line, column, color, nMove) {}

    string getName() const override { return "Pawn"; }

    string getSymbole() const override { return getColor() ? "♙" : "♟"; }

    bool isValidMovement(int destLine, int destColumn, const Board& board) const override {
        int dir = getColor() ? -1 : 1;
        int startLine = getLine();
        int startColumn = getColumn();
        int dL = destLine - startLine;
        int dC = destColumn - startColumn;
    
        Piece* target = board.getPiece(destLine, destColumn);
    
        // Simple move
        if (dL == dir && dC == 0 && target == nullptr)
            return true;
    
        // Double move
        if (dL == 2 * dir && dC == 0 && target == nullptr &&
            ((getColor() && startLine == 6) || (!getColor() && startLine == 1)) &&
            board.getPiece(startLine + dir, startColumn) == nullptr)
            return true;
    
        // Diagonal capture
        if (dL == dir && abs(dC) == 1) {
            if (target != nullptr && target->getColor() != getColor())
                return true;
    
            if (target == nullptr && passantCapture(destLine, destColumn, board))
                return true;
        }
    
        return false;
    }
    

    bool passantCapture(int destLine, int destColumn, const Board& board) const override {
        const LastMove& lastMove = board.getLastMove();
        Piece* target = lastMove.movedPiece;
        
        if (board.getPiece(destLine, destColumn) != nullptr) return false;
        if (!target || !dynamic_cast<Pawn*>(target)) return false;
        if (target->getColor() == this->getColor()) return false;
    
        if (abs(lastMove.destLine - lastMove.startLine) != 2) return false;
    
        if (abs(lastMove.destColumn - this->getColumn()) != 1) return false;
    
        int expectedLine = getLine() + (getColor() ? -1 : 1);
        if (destLine != expectedLine || destColumn != lastMove.destColumn) return false;
    
        return true;
    }
    
};

#endif // PAWN_HPP