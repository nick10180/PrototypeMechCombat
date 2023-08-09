//
// Created by Nick on 8/8/2023.
//
#include "engine.h"
#include <iostream>

bool eng::gameController::init() {
    //Creating save file pointer
    std::ifstream *saveFile = new std::ifstream;
    std::cout << "Enter your name (Must be perfect to save correctly)" << " :";
    std::cin
            >> plyName;                                                //This must be changed to allow save imp.

    //Create the player object before we mess with the name
    playerObj ply(0, 0, plyName);

    //Turn plyName into a full path
    saveLoc.append(plyName.append(".txt"));
    //saveFile->open(saveLoc);                              //Open the playername.txt file

    std::cout << "Generating world..." << std::endl;
    saveFile->close();
    this->turnCount = 0;
    delete saveFile;

    loop(ply);
    return true;
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
void eng::gameController::updateScreen(eng::playerObj ply) {
    //Already ran into the limitation of the viewporting, since the PC can reach 0,0 there's a bunch of nonsense
    //Happening on the screen.
    for (int i = ply.getY() - 10, y = 0; i < MAPSIZE; i++, y++) {
        for (int j = ply.getX() - 40, x = 0; x < MAPSIZE; j++, x++) {
            if (x > VIEWPORTX) break;

            //Draw the PC if the current tile is the PC's tile.
            if (i == ply.getY() && j == ply.getX()) {
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

bool eng::gameController::loop(eng::playerObj ply) {
    while (true) {
        //IF there is no savegame, we can generate this level
        auto *saveFile = new std::ofstream;

        generateMap(genB);
        saveFile->open(plyName, std::ios::app);     //Open in append mode

        if (!saveFile->is_open()) {
            std::cout << "\n\nFailed to open save file! Maybe your directory is write protected?";
            return true;
        }
        //Save the map to next line of file
        if (saveFile->is_open()) {
            for (int i = 0; i < MAPSIZE; i++) {
                *saveFile << "\n";
                for (int j = 0; j < MAPSIZE; j++) {
                    *saveFile << mapmap[i][j][0];
                }
            }
        }
        /*
         * Right here is where we would update the game accounting to the players actions,
         * if he had any!
         */
        ply.doAction(ply.getActions());

        updateScreen(ply);

        ply;

        std::cout << "\n";
        std::cout << ply.getPlyName();

        std::cout << "\n\n That's the map!";
        getch();


        delete saveFile;
        return 0;
    }
}


void eng::playerObj::doAction(std::vector<char> *buff) {
    //This is where we would do the action
    return;
}

eng::errorClass::error* eng::errorClass::setError(int mycode, std::string mystring) {
    auto* errp = new eng::errorClass::error;

    errp->errcode = mycode;
    errp->errstring = mystring;
    //Push the pointer to the error onto the stack.
    errorstack.push_back(errp);

    return errp;
}

