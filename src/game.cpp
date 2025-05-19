#include "game.hpp"
#include "pawn.hpp"
#include "utils.hpp"
#include <iostream>
using namespace std;

Game::Game() : playerIsWhite(true), gameResult("?-?") {}

void Game::display() const {
    board.display();
}

void Game::printInvalidMove(const string& reason) const {
    cout << "Invalid move: " << reason << endl << endl;
}

bool Game::move() {
    string from_to;
    cout << endl;
    cout << (playerIsWhite ? "White" : "Black") << " -> (eg. e2e4) ? /quit" << endl;
    cin >> from_to;

    if (from_to == "/quit" || from_to == "q") {
        gameResult = "?-?";
        return true;
    } else if (from_to == "/resign") {
        gameResult = playerIsWhite ? "0-1" : "1-0";
        return true;
    } else if (from_to == "/draw") {
        gameResult = "1/2-1/2";
        return true;
    }

    // Check if the input is valid
    if (!rightFormat(from_to) && !rightFormatCastling(from_to)) {
        printInvalidMove("use 'e2e4' or 'O-O' or 'O-O-O' format.");
        return false;
    }

    // Check if the input is a castling move
    if (rightFormatCastling(from_to)) {
        if ((from_to == "O-O" || from_to == "0-0" || from_to == "o-o") && board.shortCastling(playerIsWhite)) {
            cout << "Short castling!" << endl << endl;
            playerIsWhite = !playerIsWhite;
            return false;
        } else if ((from_to == "O-O-O" || from_to == "0-0-0" || from_to == "o-o-o") && board.longCastling(playerIsWhite)) {
            cout << "Long castling!" << endl << endl;
            playerIsWhite = !playerIsWhite;
            return false;
        } else {
            printInvalidMove("castling move.");
            return false;
        }
    }
    

    string from = from_to.substr(0, 2);
    string to = from_to.substr(2, 2);

    int startLine = 8 - (from[1] - '0');
    int startColumn = from[0] - 'a';
    int destLine = 8 - (to[1] - '0');
    int destColumn = to[0] - 'a';

    Piece* piece = board.getPiece(startLine, startColumn);
    if (!piece) {
        printInvalidMove("No piece at " + from);
        return false;
    }

    if (piece->getColor() != playerIsWhite) {
        printInvalidMove("it's not your turn!");
        return false;
    }
    if (board.wouldCauseCheck(startLine, startColumn, destLine, destColumn, playerIsWhite)) {
        printInvalidMove("this move would put your king in check!");
        return false;
    }

    if (piece->getName() == "Pawn") {
        Pawn* pawn = dynamic_cast<Pawn*>(piece);
        if (pawn->passantCapture(destLine, destColumn, board)) {
            cout << "En passant capture!" << endl;
            cout << endl;
            board.movePiece(startLine, startColumn, destLine, destColumn);
            int dir = playerIsWhite ? 1 : -1;
            board.removePiece(destLine + dir, destColumn);
            playerIsWhite = !playerIsWhite;
            return false;
        }
    }

    bool pieceCaptured = false;
    string capturePieceName = "";
    if (board.getPiece(destLine, destColumn) != nullptr) {
        capturePieceName = board.getPieceName(board.getPiece(destLine, destColumn));
        pieceCaptured = true;
    }
    if (!board.movePiece(startLine, startColumn, destLine, destColumn)) {
        printInvalidMove(piece->getName() + " from " + from + " to " + to);
        return false;
    }

    cout << "Move " << piece->getName() << " from " << from << " to " << to << endl;
    piece->incrementMoveCount();
    if (pieceCaptured) {
        cout << "Captured " << capturePieceName << endl;
    }
    
    if (board.promotion(piece)) {
        cout << endl;
    }

    if (board.checkKingIsInCheck(!playerIsWhite)) {
        cout << (playerIsWhite ? "Black" : "White") << " king is in check!" << endl;
        if (board.checkmate(!playerIsWhite)) {
            cout << "Checkmate!" << (playerIsWhite ? " Black wins!" : " White wins!") << endl;
            gameResult = playerIsWhite ? "1-0" : "0-1";
            return true;
        }
        cout << endl;
    }
    bool opponentStalemate = board.stalemate(!playerIsWhite);
    if (opponentStalemate) {
        cout << "Stalemate!" << endl;
        gameResult = "1/2-1/2";
        return true;
    }
        
        cout << endl;
    playerIsWhite = !playerIsWhite;
    return false;
}

string Game::getGameResult() const {
    return gameResult;
}

string Game::canonicalPosition() const {
    return board.canonicalPosition();
}