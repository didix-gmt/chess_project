#include "game.hpp"
#include <iostream>
using namespace std;

int main() {
    Game myGame;
    bool stop(false);
    do {    
        myGame.display();
        stop = myGame.move();
    cout << myGame.canonicalPosition() << " " << myGame.getGameResult() << endl;
    } while (!stop);
    
    return 0;
} // main