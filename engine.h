//
// Created by Nick on 8/6/2023.
// Game Engine Prototype

#include <fstream>
#include <random>
#include <chrono>

#ifndef PROTOTYPEMECHCOMBAT_ENGINE_H
#define PROTOTYPEMECHCOMBAT_ENGINE_H
namespace eng {
    //Hereonin, player will be ply

    class gameController {
        const static int MAPSIZE = 256;
        std::string saveLoc = "saves/";
        std::string plyName;
        int turnCount = 0;
        int mapmap[MAPSIZE][MAPSIZE];
        //Seed random number generator with true random value
        std::random_device rd;

        std::knuth_b genB;
        //std::cout << "\nRandom Number: " << genB() << std::endl;


    public:

        //Setup game Parameters including player name

        /*TODO
         * Display list of savegames/saveames to user and get response
         * include 'new user' response
         */
        gameController()= default;
        bool init() {




            std::ifstream *saveFile = new std::ifstream;
            std::cout << "Enter your name (Must be perfect to save correctly)" << " :";
            std::cin >> this->plyName;                                                //This must be changed to allow save imp.
            saveLoc.append(plyName.append(".txt"));
            saveFile->open(saveLoc);                              //Open the playername.txt file
            //Read until end of file

            //Write date and time on new line
            std::cout << "Generating world..." << std::endl;
            saveFile->close();
            this->turnCount = 0;
            return true;
        }

        bool loop(){
        //IF there is no savegame, we can generate this level
            std::ofstream *saveFile = new std::ofstream;
            generateMap(genB);
            saveFile->open(plyName, std::ios::app);     //Open in append mode
            //Save the map to next line of file
            if(saveFile->is_open()) {
                for (int i = 0; i < MAPSIZE; i++) {
                    *saveFile << "\n";
                    for (int j = 0; j < MAPSIZE; j++) {
                        *saveFile << mapmap[i][j];
                    }
                }
            }
            if (saveFile->is_open())
            return 0;
        }



        void generateMap(std::knuth_b genB){
            uint_fast32_t thisGen;
            //I have immediately written something that needs to be refactored.
            /*
             ********************Refactor this function
             */
            for(int i = 0; i < MAPSIZE; i++){
                for(int j = 0; j < MAPSIZE; j++){
                    thisGen = genB() % 100;
                    if (thisGen > 85){
                        mapmap[i][j] = 0;       //Pit
                    } else if (thisGen < 5){
                        mapmap[i][j] = 999;     //Shop
                    } else {
                        mapmap[i][j] = 1;       //Floor
                    }
                }
            }
        }
    };


}










#endif //PROTOTYPEMECHCOMBAT_ENGINE_H
