#ifndef BOARD_HPP
#define BOARD_HPP

#include "piece.hpp"
#include <vector>
#include <memory>

struct LastMove {
    int startLine;
    int startColumn;
    int destLine;
    int destColumn;
    Piece* movedPiece;
};


class Board {
private:
    Piece* board[8][8]; // 8*8 cases
    vector<Piece*> pieces;
    LastMove lastMove;


public:
    Board();
    ~Board();

    void initialize(); // Initialize the board with pieces
    void display() const;

    bool movePiece(int startLine, int startColumn, int destLine, int destCol);

    Piece* getPiece(int line, int col) const;

    string getPieceName(Piece* piece) const;

    string canonicalPosition() const;

    bool checkKingIsInCheck(bool player) const;

    bool wouldCauseCheck(int startLine, int startColumn, int destLine, int destColumn, bool player);

    void removePiece(int line, int column);

    const LastMove& getLastMove() const { return lastMove; }

    bool shortCastling(bool playerIsWhite);

    bool longCastling(bool playerIsWhite);

    bool promotion(Piece* p);

    bool checkmate(bool playerIsWhite);
    
    bool stalemate(bool playerIsWhite);

};

#endif // BOARD_HPP
