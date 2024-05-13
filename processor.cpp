#include "processor.hpp"
#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

void Processor::welcomeMessage() {
    std::cout << "\n";
    std::cout << "================================================================\n";
    std::cout << " _________            __________         __    __  .__\n";
    std::cout << "/   _____/ ____ _____ \\______   \\_____ _/  |__/  |_|  |   ____\n";
    std::cout << "\\_____  \\_/ __ \\\\__  \\ | __ |  _/\\__  \\    __\\   __\\  | _/ __ \\\n";
    std::cout << "/        \\  ___/ / __ \\|    |   \\ / __ \\|  |  |  | |  |_\\  ___/\n";
    std::cout << "/_______ /\\___  >____  /______  /(____  /__|  |__| |____/\\___  >\n";
    std::cout << "       \\/     \\/     \\/       \\/      \\/                     \\/\n";
    std::cout << "                  _________      .__\n";
    std::cout << "                 /   _____/ ____ |  |   ____\n";
    std::cout << "                 \\_____  \\ /  _ \\|  |  /  _ \\\n";
    std::cout << "                 /        (  <_> )  |_(  <_> )\n";
    std::cout << "                 /______ / \\____/|____/\\____/              \n";
    std::cout << "                       \\/                              -v2.51\n";
    std::cout << "================================================================\n";
    
    std::cout << "\nWelcom to the Sea Battle Solo!\n"
    << "Your goal is to destroy all "
    "ships in the ocean with as few shots as possible.\n\n";
}

int Processor::modeSelection() {
    
    do {
        std::cout << "First of all, please choose the mode you want to play!\n"
        << "- Enter '0' for Standard Mode\n"
        << "- Enter '1' for Custom Mode\n"
        << "- Or enter '--exit' to leave the game:\n";
        
        std::string userInput;
        std::getline(std::cin, userInput);
        
        if (userInput == "--exit") {
            endMessage();
            return 1;
        } else if (userInput == "0") {
            std::cout << "You choose the Standard Mode ...\n\n";
        } else if (userInput == "1") {
            mode = 1;
            std::cout << "You choose the Custom Mode ... \n\n";
        } else {
            std::cout << "Invalid input. Please try again.\n\n";
            continue;
        }
        break;
    } while (true);
    return 0;
}

int Processor::gameSetUp() {
    // Default values for Standard Mode
    int maxRow = 10;
    int maxColumn = 10;
    int carrierCount = 1;
    int battleshipCount = 1;
    int destroyerCount = 2;
    int submarineCount = 3;
    int patrolboatCount = 4;
    
    std::string userInput;
    // If the mode is set to a custom setup
    if (mode == 1) {
        // Collect custom dimensions from the user
        do {
            std::cout << "\nPlease enter the maximum size of the map - (Row, Column)\n" << "(Two numbers separated by a comma (e.g., 6,8).): \n";
            std::cout << "Or enter '--exit' to leave the game.\n";
            
            std::getline(std::cin, userInput);
            
            if (userInput == "--exit") {
                endMessage();
                // Exit with a code indicating the game setup was aborted
                return 1;
            }
            
            char delimiter;
            std::stringstream stringStream(userInput);
            stringStream >> maxRow >> delimiter >> maxColumn;
            
            if (stringStream.fail()) {
                std::cout << "Invalid input. Please try again.\n";
                continue;
            }
            
            if (maxRow >= Ocean::SUGGESTED_MAXGRIDSIZE ||
                maxColumn >= Ocean::SUGGESTED_MAXGRIDSIZE || maxRow < 0 ||
                maxColumn < 0) {
                std::cout << "\nThe specified row or column is outside the valid "
                "range. Please try again.\n";
                continue;
            }
            break;
        } while (true);
        
        // Collect custom ship counts from the user
        do {
            std::cout << "\nPlease enter the numbers of ships - (Carrier, Battleship, Destroyer, Submarine, PatrolBoat)\n"
            << "(Four numbers separated by a comma (e.g., 1,1,2,3,4).):\n";
            std::cout << "Or enter '--exit' to leave the game.\n";
            
            std::getline(std::cin, userInput);
            
            if (userInput == "--exit") {
                endMessage();
                return 1;
            }
            
            char delimiter;
            std::stringstream stringStream(userInput);
            stringStream >> carrierCount >> delimiter >> battleshipCount >> delimiter >> destroyerCount >> delimiter >> submarineCount >> delimiter >> patrolboatCount;
            
            if (stringStream.fail()) {
                std::cout << "Invalid input. Please try again.\n";
                continue;
            }
            // Check if the input fails or the ship numbers are not allowed
            bool isAllowed = Ocean::isMaxShipsAllowed(maxRow, maxColumn, {carrierCount, battleshipCount, destroyerCount, submarineCount, patrolboatCount});
            
            if (isAllowed) {
                break;
            } else {
                std::cout << "\nThere are too many ships on the ocean, please try again to lower the numbers of ships. \n";
                continue;
            }
            break;
        } while (true);
    }
    
    // std::make_unique is a template function, the type of parameters must
    //  sometimes be explicitly specified to help the compiler with type deduction
    // Create and initialize the Ocean object with the default/specified dimensions and ship counts
    ocean = std::make_unique<Ocean>(maxRow, maxColumn, std::vector<int>{carrierCount, battleshipCount, destroyerCount, submarineCount, patrolboatCount});
    // Indicates a successful setup
    return 0;
};

/** Handles the main gameplay loop, including player interaction and game state updates
 */
void Processor::gameProcessing() {
    std::cout << "... The challenge begins ... Let's Go!\n";
    ocean->putAllshipsRandomly();
    std::cout << "\n";
    ocean->print();
    std::cout << "\n";
    
    // Debugging: print the ocean with ships visible (need to be removed in production)
    ocean->printWithShips();
    
    while (true) {
        
        int targetRow;
        int targetColumn;
        bool effectiveShot;
        
        // Get and validate user input for shooting coordinates
        do {
            std::cout << "\nPlease enter the location you want to shoot at - (Row, Column) \n";
            std::cout << "(Two numbers separated by a comma (e.g., 3,9).): \n";
            std::cout << "Or enter '--exit' to leave the game.\n";
            
            std::string userInput;
            std::getline(std::cin, userInput);
            
            if (userInput == "--exit") {
                endMessage();
                return;
            }
            
            char delimiter;
            std::stringstream stringStream(userInput);
            stringStream >> targetRow >> delimiter >> targetColumn;
            
            if (stringStream.fail()) {
                std::cout << "Invalid input. Please try again.\n";
                continue;
            }
            
            if (targetRow >= ocean->getMaxColumn() ||
                targetColumn >= ocean->getMaxColumn() || targetRow < 0 ||
                targetColumn < 0) {
                std::cout
                << "\nThe specified row or column is outside the valid range. "
                "Please try again.\n";
                continue;
            }
            break;
        } while (true);
        // Attempt to shoot at the given location
        effectiveShot = ocean->shootAt(targetRow, targetColumn);
        
        if (effectiveShot) {
            std::cout << "\nFired! You hit a ship!\n";
            if (ocean->getShip(targetRow, targetColumn)->isSunk()) {
                std::cout << "You just sank a ship - "
                << ocean->getShip(targetRow, targetColumn)->getShipType()
                << ". \n";
            }
        }
        
        else {
            std::cout << "\nYou missed a shot.\n";
        }
        // Update and display the ocean's state
        std::cout << "The ocean is updated: \n\n";
        ocean->print();
        std::cout << "\n";
        
        if (ocean->isGameOver() == true) {
            std::cout << "Game over! All the ships were sunk.\n\n";
            std::cout << "The number of total shots fired: " << ocean->getFiredShots() << ". \n";
            std::cout << "FYI, the minimum shot number used to close game is: " << ocean->getMinHitCounts() << "\n";
            // Provide feedback based on performance
            if (ocean->getFiredShots() - ocean->getMinHitCounts() <=
                ocean->getMinHitCounts() * 0.2) {
                std::cout << "\nGreat job! You're an expert!\n";
            } else {
                std::cout << "\nNicely done! Try to achieve a lower number next time!\n";
            }
            break;
        }
    }
    endMessage();
}

void Processor::endMessage() {
    std::cout << "\nThank you and good bye.\n\n";
    std::cout << "           |>   |>   |>              \n";
    std::cout << "          )_)  )_)  )_)              \n";
    std::cout << "         )___))___))___)\\           \n";
    std::cout << "        )____)____)_____)            \n";
    std::cout << "      _____|____|____|____\\___      \n";
    std::cout << "  -^-/                       /-^-^-  \n";
    std::cout << "    ^^^ ^^^^^^^^ ^^^^^^^^^ ^^^^  ^^  \n";
    std::cout << "================================================================\n";
}
