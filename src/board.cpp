#include "board.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "piece.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

Board::Board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8 ; j++)
            board[i][j] = nullptr;

    initialize();
}

Board::~Board() {
    for (auto p : pieces)
        delete p;
}

void Board::initialize() {
    // ♜ Rooks
    board[0][0] = new Rook(0, 0, false, 0);
    board[0][7] = new Rook(0, 7, false, 0);
    board[7][0] = new Rook(7, 0, true, 0);
    board[7][7] = new Rook(7, 7, true, 0);

    // ♞ Knights
    board[0][1] = new Knight(0, 1, false, 0);
    board[0][6] = new Knight(0, 6, false, 0);
    board[7][1] = new Knight(7, 1, true, 0);
    board[7][6] = new Knight(7, 6, true, 0);

    // ♝ Bishops
    board[0][2] = new Bishop(0, 2, false, 0);
    board[0][5] = new Bishop(0, 5, false, 0);
    board[7][2] = new Bishop(7, 2, true, 0);
    board[7][5] = new Bishop(7, 5, true, 0);

    // ♛ Queens
    board[0][3] = new Queen(0, 3, false, 0);
    board[0][4] = new King(0, 4, false, 0);
    board[7][3] = new Queen(7, 3, true, 0);
    board[7][4] = new King(7, 4, true, 0);

    // ♟ Pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn(1, i, false, 0);
        board[6][i] = new Pawn(6, i, true, 0);
    }

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (board[i][j]) pieces.push_back(board[i][j]); 
}

void Board::display() const {
    cout << endl;
    cout << " ";
    for (char column = 'a'; column <= 'h'; column++)
        cout << "   " << column;
    cout << endl;
    
    cout << "  +";
    for (int i = 0; i < 8; i++)
        cout << "---+";
    cout << endl;

    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++) {
            if (board[i][j])
                cout << " " << board[i][j]->getSymbole() << " |";
            else
                cout << "   |";
        }
        cout << endl;

        cout << "  +";
        for (int j = 0; j < 8; j++)
            cout << "---+";
        cout << endl;
    }
}


Piece* Board::getPiece(int line, int column) const {
    if (line < 0 || line >= 8 || column < 0 || column >= 8)
        return nullptr;
    return board[line][column];
}

void Board::removePiece(int line, int column) {
    Piece* piece = getPiece(line, column);
    if (piece) {
        auto it = find(pieces.begin(), pieces.end(), piece);
        if (it != pieces.end()) {
            delete *it;
            pieces.erase(it);
        }
    }
    board[line][column] = nullptr;
}

bool Board::movePiece(int startLine, int startColumn, int destLine, int destcolumn) {
    Piece* p = getPiece(startLine, startColumn);
    if (!p) return false;

    if (!p->isValidMovement(destLine, destcolumn, *this))
        return false;

    Piece* dest = getPiece(destLine, destcolumn);
    if (dest && dest->getColor() == p->getColor())
        return false;

    if (dest) {
        for (auto item = pieces.begin(); item != pieces.end(); item++) {
            if (*item == dest) {
                delete *item;
                pieces.erase(item);
                break;
            }
        }
    }

    board[destLine][destcolumn] = p;
    board[startLine][startColumn] = nullptr;
    p->setPosition(destLine, destcolumn);
    lastMove = {startLine, startColumn, destLine, destcolumn, p};

    return true;
}

string Board::getPieceName(Piece* piece) const {
    if (!piece) return "";

    string result;

    result += (piece->getColor() == true) ? "w" : "b";

    if (dynamic_cast<Queen*>(piece)) result += "Q";
    else if (dynamic_cast<King*>(piece)) result += "K";
    else if (dynamic_cast<Bishop*>(piece)) result += "B";
    else if (dynamic_cast<Knight*>(piece)) result += "N";
    else if (dynamic_cast<Rook*>(piece)) result += "R";
    else if (dynamic_cast<Pawn*>(piece)) result += "P";
    else result += "?";

    return result;
}


string Board::canonicalPosition() const {
    string output;

    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = board[row][col];
            if (piece != nullptr) {
                output += getPieceName(piece);
            }
            output += ",";
        }
    }

    return output;
}

bool Board::checkKingIsInCheck(bool playerColor) const {
    Piece* king = nullptr;
    for (Piece* p : pieces) {
        if (p && dynamic_cast<King*>(p) && p->getColor() == playerColor) {
            king = p;
            break;
        }
    }

    if (!king) return false;

    int kingLine = king->getLine();
    int kingCol = king->getColumn();

    for (Piece* p : pieces) {
        if (p && p->getColor() != playerColor && p->isValidMovement(kingLine, kingCol, *this)) {
            return true;
        }
    }

    return false;
}

bool Board::wouldCauseCheck(int startLine, int startColumn, int destLine, int destColumn, bool playerColor) {
    Piece* moving = getPiece(startLine, startColumn);
    if (!moving || moving->getColor() != playerColor) return false;

    Piece* target = getPiece(destLine, destColumn);

    board[destLine][destColumn] = moving;
    board[startLine][startColumn] = nullptr;
    moving->setPosition(destLine, destColumn);

    auto it = find(pieces.begin(), pieces.end(), target);
    if (target && it != pieces.end()) pieces.erase(it);

    bool result = checkKingIsInCheck(playerColor);

    board[startLine][startColumn] = moving;
    board[destLine][destColumn] = target;
    moving->setPosition(startLine, startColumn);
    if (target && it != pieces.end()) pieces.insert(it, target);

    return result;
}

bool Board::shortCastling(bool playerIsWhite) {
    int row = playerIsWhite ? 7 : 0;

    if (board[row][4] && board[row][4]->getName() == "King" && board[row][4]->getMoveCount() == 0 &&
        board[row][7] && board[row][7]->getName() == "Rook" && board[row][7]->getMoveCount() == 0) {

        if (!board[row][5] && !board[row][6]) {

            if (!checkKingIsInCheck(playerIsWhite) &&
                !wouldCauseCheck(row, 4, row, 5, playerIsWhite) &&
                !wouldCauseCheck(row, 4, row, 6, playerIsWhite)) {

                // king's move
                board[row][6] = board[row][4];
                board[row][4] = nullptr;
                board[row][6]->setPosition(row, 6);
                board[row][6]->incrementMoveCount();

                // rook's move
                board[row][5] = board[row][7];
                board[row][7] = nullptr;
                board[row][5]->setPosition(row, 5);
                board[row][5]->incrementMoveCount();

                // update pieces vector
                lastMove = {row, 4, row, 6, board[row][6]};

                return true;
            }
        }
    }
    return false;
}


bool Board::longCastling(bool playerIsWhite) {
    int row = playerIsWhite ? 7 : 0;

    if (board[row][4] && board[row][4]->getName() == "King" && board[row][4]->getMoveCount() == 0 &&
        board[row][0] && board[row][0]->getName() == "Rook" && board[row][0]->getMoveCount() == 0) {

        if (!board[row][1] && !board[row][2] && !board[row][3]) {

            if (!checkKingIsInCheck(playerIsWhite) &&
                !wouldCauseCheck(row, 4, row, 3, playerIsWhite) &&
                !wouldCauseCheck(row, 4, row, 2, playerIsWhite)) {
                
                // king's move
                board[row][2] = board[row][4];
                board[row][4] = nullptr;
                board[row][2]->setPosition(row, 2);
                board[row][2]->incrementMoveCount();

                // rook's move
                board[row][3] = board[row][0];
                board[row][0] = nullptr;
                board[row][3]->setPosition(row, 3);
                board[row][3]->incrementMoveCount();

                // update pieces vector
                lastMove = {row, 4, row, 2, board[row][2]};
                
                return true;
            }
        }
    }
    return false;
}

bool Board::promotion(Piece* p) {
    if (p->getName() == "Pawn") {
        if ((p->getColor() && p->getLine() == 0) || (!p->getColor() && p->getLine() == 7)) {
            char choice = ' ';
            cout << "Promotion! Choose a piece (Q, R, B, N): ";
            cin >> choice;
            while (choice != 'Q' && choice != 'R' && choice != 'B' && choice != 'N') {
                cout << "Invalid choice. Choose a piece (Q, R, B, N): ";
                cin >> choice;
            }

            int line = p->getLine();
            int column = p->getColumn();
            bool color = p->getColor();

            removePiece(line, column);
            for (auto item = pieces.begin(); item != pieces.end(); item++) {
                if (*item == p) {
                    delete *item;
                    pieces.erase(item);
                    break;
                }
            }
            Piece* newPiece = nullptr;

            switch (choice) {
                case 'Q':
                    newPiece = new Queen(line, column, color, 0);
                    break;
                case 'R':
                    newPiece = new Rook(line, column, color, 0);
                    break;
                case 'B':
                    newPiece = new Bishop(line, column, color, 0);
                    break;
                case 'N':
                    newPiece = new Knight(line, column, color, 0);
                    break;
                default:
                    cout << "Invalid choice. No promotion." << endl;
                    return false;
            }

            board[line][column] = newPiece;
            pieces.push_back(newPiece);
            lastMove = {line, column, line, column, newPiece};
            return true;
        }
    }
    return false;
}

bool Board::checkmate(bool playerColor) {
    if (!checkKingIsInCheck(playerColor)) return false;

    for (Piece* p : pieces) {
        if (!p || p->getColor() != playerColor) continue;

        int fromL = p->getLine();
        int fromC = p->getColumn();

        for (int toL = 0; toL < 8; ++toL) {
            for (int toC = 0; toC < 8; ++toC) {
                if (p->isValidMovement(toL, toC, *this) &&
                    !wouldCauseCheck(fromL, fromC, toL, toC, playerColor)) {
                    cout << "can move " << p->getName() << " from " << fromL << "," << fromC << " to " << toL << "," << toC << endl;
                    return false;
                }
            }
        }
    }

    return true;
}


bool Board::stalemate(bool playerColor) {
    if (checkKingIsInCheck(playerColor)) return false;

    for (Piece* p : pieces) {
        if (!p || p->getColor() != playerColor) continue;

        int fromL = p->getLine();
        int fromC = p->getColumn();

        for (int toL = 0; toL < 8; ++toL) {
            for (int toC = 0; toC < 8; ++toC) {
                if (p->isValidMovement(toL, toC, *this) &&
                    !wouldCauseCheck(fromL, fromC, toL, toC, playerColor)) {
                    return false;
                }
            }
        }
    }

    return true;
}
