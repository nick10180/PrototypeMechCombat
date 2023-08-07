//
// Created by Nick on 8/6/2023.
// Game Engine Prototype

#include <fstream>
#include <random>


#ifndef PROTOTYPEMECHCOMBAT_ENGINE_H
#define PROTOTYPEMECHCOMBAT_ENGINE_H
namespace eng {
    //Hereonin, player will be ply

    class gameController {
        std::string plyName;
        int turnCount = 0;



        std::random_device rd;
        unsigned seed;

    public:

        //Setup game Parameters including player name

        /*TODO
         * Display list of savegames/saveames to user and get response
         * include 'new user' response
         */
        gameController()= default;
        bool init() {


            //Seed random number generator with true random value
            std::knuth_b genB (this->seed);
            std::cout << "\nRandom Number: " << genB() << std::endl;

            std::ofstream *saveFile = new std::ofstream;
            std::cout << "Enter your name (Must be perfect to save correctly)" << " :";
            std::cin
                    >> this->plyName;                                                //This must be changed to allow save imp.
            saveFile->open(plyName.append(".txt"));                              //Open the playername.txt file
            //Read until end of file
            //Write date and time on new line
            saveFile->close();
            this->turnCount = 0;
            return true;
        }

        bool loop(){

        }
    };


}










#endif //PROTOTYPEMECHCOMBAT_ENGINE_H
