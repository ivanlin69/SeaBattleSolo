#include "processor.hpp"

int main(int argc, const char *argv[]) {

  Processor processor;
  processor.modeSelection();
  processor.gameSetUp();

  /*
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
        std::cout << "There are too many ships on the ocean, please try
  again " "to lower the number of ships. \n";
      }
    } while (true);
  }

  Ocean ocean(maxRow, maxColumn,
              {battleshipCount, cruiserCount, destroyerCount,
  submarineCount});
*/
  // sets up and run the game
  processor.gameProcessing();

  return 0;
}
