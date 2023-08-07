#include <iostream>
#include "engine.h"


int main() {
    std::cout << "Welcome to Mech combat!" << std::endl;
    bool err_flag = false;
    eng::gameController game;
    if (!err_flag){
        game.init();
        game.loop();
        return 0;
    }
}
