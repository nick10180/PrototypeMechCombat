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
        std::string plyName;

        struct playerPos {
            int x, y;
        };
        playerPos curPos;

    public:
        playerObj(int x, int y, const std::string& newName) {
            curPos.x = 0;
            curPos.y = 0;
            plyName = newName;
        }

        int getX() {
            return curPos.x;
        }
        int getY() {
            return curPos.y;
        }

        // Getter method for plyName  (CHATGPT made these, using const is a good idea! I'm gonna start doing that...)
        std::string getPlyName() const {
            return plyName;
        }

        // Setter method for plyName (But then chatgpt said this one too)
        //
        void setPlyName(const std::string& newName) {
            plyName = newName;
        }
    };
    //Hereonin, player will be ply

    class gameController {
        std::string plyName;
        const static int MAPSIZE = 128;
        /*
         * We're gonna have to talk about the ATTRIBUTE stack.
         * Each tile on the map has the ability to hold a certain number of max attributes, set here,
         * Since plaintext is expensive on the space, these attributes will just be a god-dang number
         * and a godforsaken ever-growing map of their meanings.
         * Also, probably important to mention somewhere that mapmap[i][j][0] represents the type of tile
         *
         */
        const static int ATTRIBUTES = 3;
        const static int VIEWPORTX = 80;
        const static int VIEWPORTY = 20;
        std::string saveLoc = "saves/";

        int turnCount = 0;
        int mapmap[MAPSIZE][MAPSIZE][ATTRIBUTES];
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
        //Init function to tidy up the space
        bool init();
        //Main game loop
        bool loop(playerObj ply);
        //Map generator, directly sets the mapstate in mapmap
        void generateMap(std::knuth_b genB);
        //Screen Updater
        void updateScreen(playerObj ply);


    };


}





#endif //PROTOTYPEMECHCOMBAT_ENGINE_H
