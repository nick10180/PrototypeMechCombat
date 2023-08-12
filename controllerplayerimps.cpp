//
// Created by Nick on 8/8/2023.
//
#include "engine.h"
#include <iostream>
#include <utility>


eng::errorClass* eng::gameController::init() {
    //Creating save file pointer
    auto *savefile = new std::ifstream;
    auto *errors = new eng::errorClass;
    std::cout << "Enter your name (Must be perfect to save correctly)" << " :";
    std::cin >> plyName;                                                //This must be changed to allow save imp.

    //Create the player object before we mess with the name
    playerObj ply(0, 0, plyName);

    //Turn plyName into a full path
    saveLoc.append(plyName.append(".txt"));
    //savefile->open(saveLoc);                              //Open the playername.txt file

    std::cout << "Generating world..." << std::endl;
    savefile->close();
    this->turnCount = 0;
    delete savefile;

    loop(ply, errors);
    return errors;
}

void eng::gameController::generateMap(std::knuth_b mygen) {
    uint_fast32_t thisGen;
    //I have immediately written something that needs to be refactored.
    /*
     ********************Refactor this function
     */
    for (int i = 0; i < MAPSIZE; i++) {
        for (int j = 0; j < MAPSIZE; j++) {
            thisGen = mygen() % 100;
            if (thisGen > 85) {
                mapmap[i][j][0] = 0;       //Pit
            } else if (thisGen <= 1) {
                mapmap[i][j][0] = 9;     //Shop
            } else {
                mapmap[i][j][0] = 1;       //Floor
            }
        }
    }
}

//This sort of imp. might be cursed.
void eng::gameController::updateScreen(eng::playerObj *ply) {
    //Already ran into the limitation of the viewporting, since the PC can reach 0,0 there's a bunch of nonsense
    //Happening on the screen.
    //Going with the easy solution for now, (40, 10) is the new (0,0)
    if (!ply->isInRoom()) {
        for (int i = ply->getY() - 10, y = 0; i < MAPSIZE; i++, y++) {
            for (int j = ply->getX() - 40, x = 0; x < MAPSIZE; j++, x++) {
                if (x > VIEWPORTX) {break;}
                //Draw the PC if the current tile is the PC's tile.
                if (i == ply->getY() && j == ply->getX()) {
                    std::cout << "@";
                    continue;
                }

                switch (mapmap[i][j][0]) {
                    case 1:
                        std::cout << ".";           //Floor
                        break;
                    case 9:
                        std::cout << "$";           //Shop
                        break;
                    case 0:
                        std::cout << "P";           //Pit
                        break;
                }

            }
            if (y > VIEWPORTY) break;
        }
    }
}

eng::errorClass* eng::gameController::loop(eng::playerObj ply, errorClass *errors) {
    while (true) {
        //IF there is no savegame, we can generate this level
        auto *savefile = new std::ofstream;

        generateMap(genB);
        savefile->open(plyName, std::ios::app);     //Open in append mode

        if (!savefile->is_open()) {
            std::string saveError = "Unable to Open save file";
            eng::errorClass::setError(1, saveError, &errors->getErrorstack());
            return errors;
        }
        //Save the map to next line of file
        if (savefile->is_open()) {
            for (int i = 0; i < MAPSIZE; i++) {
                *savefile << "\n";
                for (int j = 0; j < MAPSIZE; j++) {
                    *savefile << mapmap[i][j][0];
                }
            }
        }
        /*
         * Right here is where we would update the game accounting to the players actions,
         * if he had any!
         */
        //ply.doAction(ply.getActions());

        updateScreen(&ply);

        ply;

        std::cout << "\n";
        std::cout << ply.getPlyName();

        std::cout << "\n\n That's the map!";
        getch();


        delete savefile;
        return errors;
    }
}


void eng::playerObj::doAction(std::vector<char> *buff) {
    //This is where we would do the action
    return;
}

void eng::errorClass::setError(int mycode, std::string &mystring, std::vector<error> *errstack) {
    auto *errp = new eng::errorClass::error;

    errp->errcode = mycode;
    errp->errstring = mystring;
    //Push the pointer to the error onto the stack.
    errstack->push_back(*errp);

    delete errp;
}

eng::errorClass::errorClass() {
}

std::vector<eng::errorClass::error> &eng::errorClass::getErrorstack() {
    return errorstack;
}

