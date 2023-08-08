//
// Created by Nick on 8/6/2023.
// Game Engine Prototype

#include <fstream>
#include <random>
#include <chrono>
#include <conio.h>

#ifndef PROTOTYPEMECHCOMBAT_ENGINE_H
#define PROTOTYPEMECHCOMBAT_ENGINE_H
namespace eng {

    class playerObj {
        struct playerPos {
            int x, y;
        };
        playerPos curPos;

    public:
        playerObj() {
            curPos.x = 0;
            curPos.y = 0;
        }


    };
    //Hereonin, player will be ply

    class gameController {
        const static int MAPSIZE = 128;
        const static int VIEWPORTX = 80;
        const static int VIEWPORTY = 20;
        std::string saveLoc = "saves/";
        std::string plyName;
        int turnCount = 0;
        int mapmap[MAPSIZE][MAPSIZE];
        int viewOffsetX = 0, viewOffsetY = 0;
        //Seed random number generator with true random value
        //std::random_device rd;

        std::knuth_b genB;
        //std::cout << "\nRandom Number: " << genB() << std::endl;

    public:

        //Setup game Parameters including player name

        /*TODO
         * Display list of savegames/saveames to user and get response
         * include 'new user' response
         */
        gameController() = default;

        bool init() {
            std::ifstream *saveFile = new std::ifstream;
            std::cout << "Enter your name (Must be perfect to save correctly)" << " :";
            std::cin
                    >> this->plyName;                                                //This must be changed to allow save imp.
            saveLoc.append(plyName.append(".txt"));
            saveFile->open(saveLoc);                              //Open the playername.txt file

            std::cout << "Generating world..." << std::endl;
            saveFile->close();
            this->turnCount = 0;
            delete saveFile;
            playerObj ply;
            loop(ply);
            return true;
        }


        bool loop(playerObj ply) {
            while (true) {
                //IF there is no savegame, we can generate this level
                std::ofstream *saveFile = new std::ofstream;

                generateMap(genB);
                saveFile->open(plyName, std::ios::app);     //Open in append mode

                if (!saveFile->is_open()) {
                    std::cout << "\n\nFailed to open save file! Maybe your directory is write protected?";
                    return 1;
                }
                //Save the map to next line of file
                if (saveFile->is_open()) {
                    for (int i = 0; i < MAPSIZE; i++) {
                        *saveFile << "\n";
                        for (int j = 0; j < MAPSIZE; j++) {
                            *saveFile << mapmap[i][j];
                        }
                    }
                }
                updateScreen();
                //Draw the screen!!!!!!!!!

                std::cout << "\n";

                std::cout << "\n\n That's the map!";
                getch();


                delete saveFile;
                return 0;
            }
        }

        void updateScreen() {
            for (int i = 0 + viewOffsetY, y = 0; i < MAPSIZE; i++, y++) {
                for (int j = 0 + viewOffsetX, x = 0; x < MAPSIZE; j++, x++) {
                    if (x > VIEWPORTX) break;
                    switch (mapmap[i][j]) {
                        case 1:
                            std::cout << ".";           //Floor
                            break;
                        case 9:
                            std::cout << "$";           //Shop
                            break;
                        case 0:
                            std::cout << "P";           //Pit
                    }
                }
                if (y > VIEWPORTY) break;
            }
        }

        void generateMap(std::knuth_b genB) {
            uint_fast32_t thisGen;
            //I have immediately written something that needs to be refactored.
            /*
             ********************Refactor this function
             */
            for (int i = 0; i < MAPSIZE; i++) {
                for (int j = 0; j < MAPSIZE; j++) {
                    thisGen = genB() % 100;
                    if (thisGen > 85) {
                        mapmap[i][j] = 0;       //Pit
                    } else if (thisGen <= 1) {
                        mapmap[i][j] = 9;     //Shop
                    } else {
                        mapmap[i][j] = 1;       //Floor
                    }
                }
            }
        }
    };


}





#endif //PROTOTYPEMECHCOMBAT_ENGINE_H
