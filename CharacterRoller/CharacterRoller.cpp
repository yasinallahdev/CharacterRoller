// CharacterRoller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <random>
#include <memory>
#include <chrono>
#include "Character.h"

#define USE_SEED

// Program Goals:
// Rolling up NPCs

// NPCs divide their Level between these Skills
// (E.G.Level 2 Copper has 2 points)
// Mental
// Combat
// Resistance
// Utility
// Special

// Roll damage dice out of eachand gain that many Traits Points to divide between each Skill

// Traits must be tied to a skill, but can only stack with Traits from seperate skills.
// For example
// if Grunt has a Trait "Violence, Combat" he can't also pop "Bludgeoner, Combat"  but he might be able to pop "Kung Fu, Special"
// Traits add a Flat Bonus to any of these skills
// 0: D2
// 1: D4
// 3 : D6
// 5 : D8
// 8 : D10
// 10 : D12
// 15 : D20
// 16 : 1D20 + 1D4
// 18 : 1D20 + 1D6

int main(int* argc, const char** argv) {

    bool continueRunning = true;

    while (continueRunning) {


        std::cout << "Enter NPC Name: ";
        std::string npcName;
        std::getline(std::cin, npcName);

        std::cout << "Enter NPC level: ";
        uint64_t npcLevel = 0;
        std::cin >> npcLevel;
        uint_fast32_t seed = static_cast<uint_fast32_t>(std::chrono::system_clock::now().time_since_epoch().count());
        std::shared_ptr<std::mt19937> randomEngine = std::make_shared<std::mt19937>(
#ifdef USE_SEED
            seed
#endif
        );

        Character theCharacter(npcLevel, npcName, randomEngine);

        std::cout << "Would you like to input information for another character? (Y/N)? ";
        char choice = 'N';
        std::cin >> choice;

        if ((choice == 'Y') || (choice == 'y')) {
            continueRunning = true;
        } else {
            continueRunning = false;
        }


        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << '\n';


    }

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
