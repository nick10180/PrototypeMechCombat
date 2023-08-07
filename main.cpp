#include <iostream>
#include "engine.h"

using namespace eng;
int main() {
    std::cout << "Welcome to Mech combat!" << std::endl;
    bool err_flag = false;
    gameController game;
    if (!err_flag){
        game.init();
        game.loop();
        return 0;
    }
}
