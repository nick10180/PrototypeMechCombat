#include <iostream>
#include "engine.h"
#include <system_error>


int main() {
    std::cout << "Welcome to Mech combat!" << std::endl;
    bool err_flag = false;
    eng::errorClass *error;
    eng::gameController game;
    if (!err_flag){
        try {
            error = game.init();
        }
        catch (const std::system_error& error)
        {
            std::cout << "System Error!" << std::endl << "Error as follows: " << error.what();
        }

        if(error->isError()){
            for (auto n: error->getErrorstack()) {
                std::cout << "Errors as follows:\n__________________________\n";
                std::cout << "Code " <<n.errcode << std::endl << n.errstring;
            }
        }
        getch();
        return 0;
    }
}
