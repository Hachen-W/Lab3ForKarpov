#include <iostream>
#include <chrono>
#include <thread>
#include "../lib/game/game.hpp"

using namespace std;

int main() {
    Game game;
    game.generatePlayground(5, 7);
    bool flag = true;
    while (flag) {
        //cout << game;
        game.makeStep();
        cout << "~~~~~~~~~~~~~~~~~"<< endl; //system("clear");
        cout << game;
        //cout << "Continue?" << endl;
        //cin >> flag;
    }
    
    return 0;
}