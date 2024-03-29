#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {

  std::string userInput;
  std::vector<char> userInputArray;
  int inputRow;
  int inputColumn;
  bool effectiveShot;

  std::cout << "Welcom to the Battleship Game! Your goal is to destroy all "
               "ships in the ocean with as few shots as possible.\n";
  std::cout << "Let's go! Here is the map: \n";

  // sets up the game
  Ocean ocean;
  ocean.placeAllShipsRandomly();
  std::cout << "\n";
  ocean.print();
  std::cout << "\n";

  // just for debugging
  ocean.printWithShips();

  while (true) {

    // get and parse the user input
    do {
      std::cout << "Enter the location you want to shoot at - (Row,Column) \n";
      std::cout << "(0 to 9, comma separated.): \n";
      std::cout << "Or enter --exit to leave the game.\n";

      std::cin >> userInput;

      if (userInput == "--exit") {
        std::cout << "\nThank you and good bye.\n";
        return 0;
      }
      // if the user input is invalid, stay in the loop
      else if (userInput.length() != 3) {
        std::cout << "Invalid input. Please try again.\n";
        continue;
      }

      inputRow = userInput[0] - '0';
      inputColumn = userInput[2] - '0';
      break;

    } while (true);

    effectiveShot = ocean.shootAt(inputRow, inputColumn);

    if (effectiveShot) {
      std::cout << "Fired. You hit a ship! \n";
      if (ocean.getShipArray()[inputRow][inputColumn]->isSunk()) {
        std::cout << "You just sank a ship - "
                  << ocean.getShipArray()[inputRow][inputColumn]->getShipType()
                  << ". ";
      }
    }

    else {
      std::cout << "You missed a shot. ";
    }

    std::cout << "The ocean is updated for you: \n";
    ocean.print();
    std::cout << "\n";

    if (ocean.isGameOver() == true) {
      std::cout << "Game over! All the ships were sunk.\n";
      std::cout << "Number of total shots fired: " << ocean.getShotsFired()
                << ". \n";
      std::cout << "Number of hits: " << ocean.getHitCount() << ". \n";
      break;
    }
  }

  std::cout << "\nThank you and good bye.\n";

  return 0;
}
