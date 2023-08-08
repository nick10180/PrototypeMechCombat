#include <iostream>
#include "engine.h"
#include <system_error>


int main() {
    std::cout << "Welcome to Mech combat!" << std::endl;
    bool err_flag = false;
    eng::gameController game;
    if (!err_flag){
        try {
            game.init();
        }
        catch (const std::system_error& error)
        {
            std::cout << "System Error!" << std::endl << "Error as follows: " << error.what();
        }

        return 0;
    }
}
