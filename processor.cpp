#include "processor.hpp"
#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

void Processor::welcomeMessage() {
  std::cout << "\n\n";
  std::cout << "===========================================================\n";
  std::cout << "   ._____      ___   ._______._______.____    ______\n";
  std::cout << "   |  _  \\    /   \\  |       |       ||  |    |   __|\n";
  std::cout << "   | |_) |   /  ^  \\ `--|  |-`-|  |--`|  |    |  |__   \n";
  std::cout << "   |  _ <   /  /_\\  \\   |  |   |  |   |  |    |   __|  \n";
  std::cout << "   | |_) | /  _____  \\  |  |   |  |   |  `---.|  |____ \n";
  std::cout << "   |_____//__/     \\__\\ |__|   |__|   |______||_______|\n";

  std::cout << "        _______. __    __   __  .______\n";
  std::cout << "       /       ||  |  |  | |  | |   _  \\\n";
  std::cout << "       |  (----`|  |__|  | |  | |  |_) | \n";
  std::cout << "       \\   \\    |   __   | |  | |   ___/\n";
  std::cout << "   .----)   |   |  |  |  | |  | |  |\n";
  std::cout << "   |_______/    |__|  |__| |__| | _|               -v2.10\n";
  std::cout << "===========================================================\n";

  std::cout << "\nWelcom to the Battleship Game!\n"
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
  int battleshipCount = 1;
  int cruiserCount = 2;
  int destroyerCount = 3;
  int submarineCount = 4;

  std::string userInput;

  if (mode == 1) {
    do {
      std::cout
          << "\nPlease enter the maximum size of the map - (Row, Column)\n"
          << "(Two numbers separated by a comma (e.g., 6,8).): \n";
      std::cout << "Or enter '--exit' to leave the game.\n";

      std::getline(std::cin, userInput);

      if (userInput == "--exit") {
        endMessage();
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

    do {
      std::cout << "\nPlease enter the numbers of ships - "
                   "(Battleship, Cruiser, Destroyer, Submarine)\n"
                << "(Four numbers separated by a comma (e.g., 1,2,3,4).):\n";
      std::cout << "Or enter '--exit' to leave the game.\n";

      std::getline(std::cin, userInput);

      if (userInput == "--exit") {
        endMessage();
        return 1;
      }

      char delimiter;
      std::stringstream stringStream(userInput);
      stringStream >> battleshipCount >> delimiter >> cruiserCount >>
          delimiter >> destroyerCount >> delimiter >> submarineCount;

      if (stringStream.fail()) {
        std::cout << "Invalid input. Please try again.\n";
        continue;
      }

      bool isAllowed = Ocean::isMaxShipsAllowed(
          maxRow, maxColumn,
          {battleshipCount, cruiserCount, destroyerCount, submarineCount});

      if (isAllowed) {
        break;
      } else {
        std::cout
            << "\nThere are too many ships on the ocean, please try again "
               "to lower the numbers of ships. \n";
        continue;
      }
      break;
    } while (true);

    /*std::cout << "Result:"
              << "maxRow: " << maxRow << "maxColumn: " << maxColumn
              << "battleshipCount: " << battleshipCount
              << "cruiserCount: " << cruiserCount
              << "destroyerCount: " << destroyerCount
              << "submarineCount: " << submarineCount << "\n";
              */

    // Use std::cin.ignore(1); if you are certain there's only one character
    // to ignore. Use
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
    // '\n'); for complete clearance of the line to prevent any leftover input
    // from affecting subsequent reads.
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // std::cin.ignore(1);
  }

  // std::make_unique is a template function, the type of parameters must
  //  sometimes be explicitly specified to help the compiler with type
  //  deduction
  ocean =
      std::make_unique<Ocean>(maxRow, maxColumn,
                              std::vector<int>{battleshipCount, cruiserCount,
                                               destroyerCount, submarineCount});
  return 0;
};

void Processor::gameProcessing() {
  std::cout << "\n... The challenge begins ... Let's Go!\n";
  ocean->putAllshipsRandomly();
  std::cout << "\n";
  ocean->print();
  std::cout << "\n";

  // just for debugging
  ocean->printWithShips();

  while (true) {

    int targetRow;
    int targetColumn;
    bool effectiveShot;

    // get and parse the user input
    do {
      std::cout << "\nPlease enter the location you want to shoot at - "
                   "(Row, Column) \n";
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

    std::cout << "The ocean is updated: \n\n";
    ocean->print();
    std::cout << "\n";

    if (ocean->isGameOver() == true) {
      std::cout << "Game over! All the ships were sunk.\n\n";
      std::cout << "The number of total shots fired: " << ocean->getFiredShots()
                << ". \n";
      std::cout << "FYI, the minimum shot number used to close game is: "
                << ocean->getMinHitCounts() << "\n";

      if (ocean->getFiredShots() - ocean->getMinHitCounts() <=
          ocean->getMinHitCounts() * 0.2) {
        std::cout << "\nGreat job! You're an expert!\n";
      } else {
        std::cout
            << "\nNicely done! Try to achieve a lower number next time!\n";
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
  std::cout << "===========================================================\n";
}
