#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <memory>
#include <random>

Ocean::Ocean(int row, int column, std::vector<int> shipsCount)
    : firedShots(0), hitCounts(0), sunkShips(0), totalShips(0), maxRow(row),
      maxColumn(column), maxShipsCount(shipsCount) {
  std::cout << "shipsCount: " << shipsCount[0] << std::endl;
  for (size_t i = 0; i < shipsCount.size(); i++) {
    totalShips += shipsCount[i];
  }
  std::cout << "totalShips: " << totalShips << std::endl;

  ships.resize(maxRow);
  for (int i = 0; i < maxRow; i++) {
    ships[i].resize(maxColumn);
    for (int j = 0; j < maxColumn; j++) {
      // C++14 std::make_shared<>
      ships[i][j] = std::make_shared<EmptySea>(i, j);
    }
  }
}

bool Ocean::isMaxShipsAllowed(int maxRow, int maxColumn,
                              std::vector<int> shipsCount) {
  int maxCapacity = 0;
  int shipSize = Ship::BATTLESHIP_SIZE;
  for (size_t i = 0; i < shipsCount.size(); i++) {
    maxCapacity += shipsCount[i] * (3 * (shipSize + 2));
    shipSize--;
  }
  std::cout << "maxCapacity: " << maxCapacity << "maxRow: " << maxRow
            << "maxColumn: " << maxColumn << "size: " << maxRow * maxColumn * 2;
  return maxCapacity <= maxRow * maxColumn * 1.5;
}

bool Ocean::isOccupied(int row, int column) const {
  return ships[row][column]->getShipType() == Ship::TYPE_EMPTY ? false : true;
}

bool Ocean::isGameOver() const {
  return sunkShips == totalShips ? true : false;
}

bool Ocean::shootAt(int row, int column) {
  bool effectiveShoot = ships[row][column]->shootAt(row, column);
  firedShots++;
  if (effectiveShoot) {
    hitCounts++;
    if (ships[row][column]->isSunk())
      sunkShips++;
  }
  return effectiveShoot;
}

void Ocean::putShipRandomly(std::shared_ptr<Ship> shipPtr) {

  std::random_device rd;                                       // seed
  std::default_random_engine gen(rd());                        // generator
  std::uniform_int_distribution<> rand_int_row(0, maxRow - 1); // distribution
  std::uniform_int_distribution<> rand_int_column(0, maxColumn -
                                                         1); // distribution
  std::bernoulli_distribution rand_bool(0.5);
  // generate random values for row, column and horizontal
  int randRow = rand_int_row(gen);
  int randColumn = rand_int_column(gen);
  bool randHorizontal = rand_bool(gen);

  // update the conditions with random until okToPlaceShipAt is true
  while (
      !shipPtr->okToPlaceShipAt(randRow, randColumn, randHorizontal, *this)) {

    randRow = rand_int_row(gen);
    randColumn = rand_int_column(gen);
    randHorizontal = rand_bool(gen);
  }
  // then place the ship
  shipPtr->placeShipAt(randRow, randColumn, randHorizontal, *this);
}

void Ocean::putAllshipsRandomly() {
  // 0:Battleship, 1:Cruiser, 2:Destroyer, 3:Submarine
  int currentShip = 0;
  int maxShipNum = totalShips;

  while (maxShipNum > 0) {
    switch (currentShip) {
    case 0:
      if (maxShipsCount[currentShip] > 0) {
        putShipRandomly(std::make_shared<Battleship>());
        maxShipsCount[currentShip]--;
        maxShipNum--;
      }
      break;

    case 1:
      if (maxShipsCount[currentShip] > 0) {
        putShipRandomly(std::make_shared<Cruiser>());
        maxShipsCount[currentShip]--;
        maxShipNum--;
      }
      break;

    case 2:
      if (maxShipsCount[currentShip] > 0) {
        putShipRandomly(std::make_shared<Destroyer>());
        maxShipsCount[currentShip]--;
        maxShipNum--;
      }
      break;

    case 3:
      if (maxShipsCount[currentShip] > 0) {
        putShipRandomly(std::make_shared<Submarine>());
        maxShipsCount[currentShip]--;
        maxShipNum--;
      }
      break;
    }

    if (maxShipsCount[currentShip] > 0) {
      continue;
    } else {
      currentShip++;
    }
  }
}

void Ocean::print() const {
  // print the coordinates for the column
  std::cout << "  ";
  for (int i = 0; i < maxColumn; i++) {
    if (i < 10) {
      std::cout << " " << i << " ";
    } else {
      std::cout << i << " ";
    }
  }
  std::cout << "\n";
  // use nested for loops to get and prints the ships
  // for the row
  for (int i = 0; i < maxRow; i++) {
    // prints the coordinates before printing the ships
    if (i < 10) {
      std::cout << " " << i << " ";
    } else {
      std::cout << i << " ";
    }
    // for the column
    for (int j = 0; j < maxColumn; j++) {
      // if the ship is sunk, or it's an empty sea got hit before, just print
      // the ship (will be "s" / "-")
      if (this->ships[i][j]->isSunk() == true ||
          (this->ships[i][j]->getShipType() == Ship::TYPE_EMPTY &&
           this->ships[i][j]->getHit()[0] == true)) {
        std::cout << *(this->ships[i][j]) << "  ";
      }

      // if the ship isn't sunk
      else {
        // gets the condition of the ship at the given location
        int bowRow = this->ships[i][j]->getBowRow();
        int bowColumn = this->ships[i][j]->getBowColumn();

        // iterates over the ship's hit array to check if the part is hit or not
        for (int k = 0; k < this->ships[i][j]->getLength(); k++) {

          if (bowRow == i && bowColumn == j) {
            // if is hit, then print the ship
            if (this->ships[i][j]->getHit()[k] == true) {
              std::cout << *(this->ships[i][j]) << "  ";
              break;
            }
            // otherwise, print "."
            else {
              std::cout << ".  ";
              break;
            }
          }

          else {
            if (this->ships[i][j]->isHorizontal()) {
              bowColumn--;
            } else {
              bowRow--;
            }
          }
        }
      }
      // lastly, if it's the end of the column, prints an empty line
      if (j == maxColumn - 1) {
        std::cout << "\n";
      }
    }
  }
}

/**
 * Prints the Ocean with the location of the ships.(just for debugging)
 */
void Ocean::printWithShips() const {
  // similar to print() but only shows the locations of the ships

  // print the coordinates for the column
  std::cout << "  ";
  for (int i = 0; i < maxColumn; i++) {
    if (i < 10) {
      std::cout << " " << i << " ";
    } else {
      std::cout << i << " ";
    }
  }
  std::cout << "\n";
  for (int i = 0; i < maxRow; i++) {
    // prints the coordinates before printing the ships
    if (i < 10) {
      std::cout << " " << i << " ";
    } else {
      std::cout << i << " ";
    }

    for (int j = 0; j < maxColumn; j++) {
      // prints the ships
      if (this->ships[i][j]->getShipType() == Ship::TYPE_BATTLESHIP) {
        std::cout << "b  ";
      } else if (this->ships[i][j]->getShipType() == Ship::TYPE_CRUISER) {
        std::cout << "c  ";
      } else if (this->ships[i][j]->getShipType() == Ship::TYPE_DESTROYER) {
        std::cout << "d  ";
      } else if (this->ships[i][j]->getShipType() == Ship::TYPE_SUBMARINE) {
        std::cout << "s  ";
      } else {
        std::cout << "   ";
      }
      // lastly, if it's the end of the column, prints an empty line
      if (j == maxColumn - 1) {
        std::cout << "\n";
      }
    }
  }
  std::cout << "\n";
}
