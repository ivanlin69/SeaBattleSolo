#include "processor.hpp"
#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

void Processor::modeSelection() {
  std::cout << "Welcom to the Battleship Game! Your goal is to destroy all "
               "ships in the ocean with as few shots as possible.\n";

  do {
    std::cout << "First of all, choose the mode you want to play: \n"
              << "Enter '1' for Standard Mode \n"
              << "Enter '2' for Custom Mode \n"
              << "Or enter '--exit' to leave the game.\n";

    std::string userInput;
    std::getline(std::cin, userInput);

    if (userInput == "--exit") {
      std::cout << "\nThank you and good bye.\n";
      return;
    } else if (userInput == "1") {
      std::cout << "You choose the Standard Mode. Let's go! \n";
    } else if (userInput == "2") {
      mode = 2;
      std::cout << "You choose the Custom Mode. Let's go! \n";
    } else {
      std::cout << "Invalid input. Please try again.\n";
      continue;
    }
    break;
  } while (true);
}

void Processor::gameSetUp() {
  int maxRow = 10;
  int maxColumn = 10;
  int battleshipCount = 1;
  int cruiserCount = 2;
  int destroyerCount = 3;
  int submarineCount = 4;

  if (mode == 2) {
    do {
      std::cout << "Please enter the maximum size of the row: \n";
      std::cin >> maxRow;
      std::cout << "Please enter the maximum size of the column: \n";
      std::cin >> maxColumn;
      std::cout << "Please enter the number of battleships: \n";
      std::cin >> battleshipCount;
      std::cout << "Please enter the maximum size of cruisers: \n";
      std::cin >> cruiserCount;
      std::cout << "Please enter the maximum size of destroyers: \n";
      std::cin >> destroyerCount;
      std::cout << "Please enter the maximum size of submarines: \n";
      std::cin >> submarineCount;

      std::cout << "Result:"
                << "maxRow: " << maxRow << "maxColumn: " << maxColumn
                << "battleshipCount: " << battleshipCount
                << "cruiserCount: " << cruiserCount
                << "destroyerCount: " << destroyerCount
                << "submarineCount: " << submarineCount << "\n";

      bool isAllowed = Ocean::isMaxShipsAllowed(
          maxRow, maxColumn,
          {battleshipCount, cruiserCount, destroyerCount, submarineCount});

      if (isAllowed) {
        break;
      } else {
        std::cout << "There are too many ships on the ocean, please try again "
                     "to lower the number of ships. \n";
      }
    } while (true);
  }

  // std::make_unique is a template function, the type of parameters must
  //  sometimes be explicitly specified to help the compiler with type deduction

  ocean =
      std::make_unique<Ocean>(maxRow, maxColumn,
                              std::vector<int>{battleshipCount, cruiserCount,
                                               destroyerCount, submarineCount});
};

void Processor::gameProcessing() {

  ocean->putAllshipsRandomly();
  std::cout << "\n";
  ocean->print();
  std::cout << "\n";

  // just for debugging
  ocean->printWithShips();

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {

    int targetRow;
    int targetColumn;
    bool effectiveShot;

    // get and parse the user input
    do {
      std::cout
          << "Please enter the location you want to shoot at - (Row,Column) \n";
      std::cout << "(Two numbers separated by a comma (e.g., 3,9).): \n";
      std::cout << "Or enter --exit to leave the game.\n";

      std::string userInput;
      std::getline(std::cin, userInput);

      if (userInput == "--exit") {
        std::cout << "\nThank you and good bye.\n";
        return;
      }

      char delimiter;
      std::stringstream stringStream(userInput);
      stringStream >> targetRow >> delimiter >> targetColumn;

      // For debugging
      std::cout << std::endl
                << "targetRow: " << targetRow << std::endl
                << "delimiter: " << delimiter << std::endl
                << "targetColumn: " << targetColumn << std::endl;

      if (stringStream.fail()) {
        std::cout << "Invalid input. Please try again.\n";
        continue;
      }

      if (targetRow >= ocean->getMaxColumn() ||
          targetColumn >= ocean->getMaxColumn()) {
        std::cout << "The specified row or column is outside the valid range. "
                     "Please try again.\n";
        continue;
      }

      break;
    } while (true);

    effectiveShot = ocean->shootAt(targetRow, targetColumn);

    if (effectiveShot) {
      std::cout << "Fired. You hit a ship! \n";
      if (ocean->getShip(targetRow, targetColumn)->isSunk()) {
        std::cout << "You just sank a ship - "
                  << ocean->getShip(targetRow, targetColumn)->getShipType()
                  << ". ";
      }
    }

    else {
      std::cout << "You missed a shot. ";
    }

    std::cout << "The ocean is updated for you: \n";
    ocean->print();
    std::cout << "\n";

    if (ocean->isGameOver() == true) {
      std::cout << "Game over! All the ships were sunk.\n";
      std::cout << "Number of total shots fired: " << ocean->getFiredShots()
                << ". \n";
      std::cout << "Number of hits: " << ocean->getHitCounts() << ". \n";
      break;
    }
  }

  std::cout << "\nThank you and good bye.\n";
}
