//
// Created by Nick on 8/6/2023.
// Game Engine Prototype

#include <fstream>

#ifndef PROTOTYPEMECHCOMBAT_ENGINE_H
#define PROTOTYPEMECHCOMBAT_ENGINE_H
namespace eng {
    //Hereonin, player will be ply

    class gameController {
        std::string plyName;
        int turnCount = 0;


    public:

        //Setup game Parameters including player name

        /*TODO
         * Display list of savegames/saveames to user and get response
         * include 'new user' response
         */
        gameController()= default;
        bool init() {
            std::ofstream saveFile;
            std::cout << "Enter your name (Must be perfect to save correctly)" << " :";
            std::cin
                    >> this->plyName;                                                //This must be changed to allow save imp.
            saveFile.open(plyName.append(".txt"));                              //Open the playername.txt file
            //Read until end of file
            //Write date and time on new line
            saveFile.close();
            this->turnCount = 0;
            return true;
        }


    };


}










#endif //PROTOTYPEMECHCOMBAT_ENGINE_H
