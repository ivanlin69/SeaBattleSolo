#include "processor.hpp"

int main(int argc, const char *argv[]) {
    // A processor instance to manage the game
    Processor processor;
    processor.welcomeMessage();
    // If the mode selection indicates to exit, terminate the program
    if (processor.modeSelection() == 1) {
        return 0;
    }
    // Set up the game with initial configurations
    if (processor.gameSetUp() == 0) {
        // If setup is successful, proceed to the main game processing loop
        processor.gameProcessing();
    } else {
        // If setup fails or is aborted, exit the program
        return 0;
    }
    return 0;
}
