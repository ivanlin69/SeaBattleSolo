#ifndef processor_hpp
#define processor_hpp

#include "ocean.hpp"
#include <memory>

// The Processor class manages the game logic and interactions for the game.
class Processor {
    
private:
    std::unique_ptr<Ocean> ocean;
    // Represents the current game mode(0: Standard Mode; 1: Custom Mode)
    int mode;
    
public:
    // Default constructor, initializes the game mode to 0
    Processor() : mode(0) {};
    // Displays the welcome message at the start of the game
    void welcomeMessage();
    // Prompts the user to select the game mode
    int modeSelection();
    // Sets up the game
    int gameSetUp();
    // Processes the main game logic, handling turns, user inputs, and game state
    void gameProcessing();
    // Displays the ending message based on the outcome of the game
    void endMessage();
    ~Processor() {}
};

#endif
