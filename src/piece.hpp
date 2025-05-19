#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include  "board.hpp"
using namespace std;

class Board; // Forward declaration
class Piece {
private:
    int line, column;
    bool isWhite;
    int nMove;

public:
    Piece(int line, int column, bool color, int nMove) : line(line), column(column), isWhite(color), nMove(nMove) {}

    int getLine() const { return line; }
    int getColumn() const { return column; }
    bool getColor() const { return isWhite; }
    int getMoveCount() const { return nMove; }
    void incrementMoveCount() { nMove++; }

    void setPosition(int l, int c) {
        line = l;
        column = c;
    }

    virtual string getName() const = 0;

    virtual bool isValidMovement(int destLine, int destColumn, const Board& board) const = 0;

    
    virtual string getSymbole() const = 0;

    virtual bool passantCapture(int, int, const Board&) const {
        return false;
    }

    virtual ~Piece() = default;
};

#endif // PIECE_HPP
