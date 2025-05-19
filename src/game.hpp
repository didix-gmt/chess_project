#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include <string>

class Game {
private:
    Board board;
    bool playerIsWhite;
    string gameResult;

public:
    Game();

    ~Game() {}
    
    void display() const;

    bool move();

    string getGameResult() const;

    string canonicalPosition() const;

    void printInvalidMove(const string& reason) const;
};

#endif // GAME_HPP