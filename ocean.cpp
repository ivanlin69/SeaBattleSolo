#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <random>

Ocean::Ocean() : shotsFired(0), hitCount(0), shipsSunk(0) {
  ships.resize(10);
  for (int i = 0; i < 10; i++) {
    ships[i].resize(10);
    for (int j = 0; j < 10; j++) {
      ships[i][j] = std::make_shared<EmptySea>();
      ships[i][j]->placeShipAt(i, j, false, *this);
    }
  }
}

bool Ocean::isOccupied(int row, int column) const {
  if (ships[row][column]->getShipType() == "empty")
    return false;
  return true;
}

bool Ocean::isGameOver() const {
  if (shipsSunk == 10)
    return true;
  return false;
}

bool Ocean::shootAt(int row, int column) {

  std::shared_ptr<Ship> &ship = getShipArray()[row][column];
  bool effectiveShoot = ship->shootAt(row, column);

  shotsFired++;

  if (effectiveShoot) {
    hitCount++;
    if (ship->isSunk())
      shipsSunk++;
  }
  return effectiveShoot;
}

void Ocean::putShipRandomly(std::shared_ptr<Ship> shipPtr) {

  std::random_device rd;                          // seed
  std::default_random_engine gen(rd());           // generator
  std::uniform_int_distribution<> rand_int(0, 9); // distribution
  std::bernoulli_distribution rand_bool(0.5);
  // generate random values for row, column and horizontal
  int randRow = rand_int(gen);
  int randColumn = rand_int(gen);
  bool randHorizontal = rand_bool(gen);

  // update the conditions with random until okToPlaceShipAt is true
  while (
      !shipPtr->okToPlaceShipAt(randRow, randColumn, randHorizontal, *this)) {

    randRow = rand_int(gen);
    randColumn = rand_int(gen);
    randHorizontal = rand_bool(gen);
  }
  // then place the ship
  shipPtr->placeShipAt(randRow, randColumn, randHorizontal, *this);
}

void Ocean::placeAllShipsRandomly() {
  // creates instances of ships and uses helper method putShipRandomly to put
  // the ship randomly
  putShipRandomly(std::make_unique<Battleship>());
  for (int i = 0; i < 2; i++) {
    putShipRandomly(std::make_unique<Cruiser>());
  }
  for (int i = 0; i < 3; i++) {
    putShipRandomly(std::make_unique<Destroyer>());
  }
  for (int i = 0; i < 4; i++) {
    putShipRandomly(std::make_unique<Submarine>());
  }
}

void Ocean::print() const {
  // print the coordinates for the column
  std::cout << ("  0 1 2 3 4 5 6 7 8 9 \n");
  // use nested for loops to get and prints the ships
  // for the row
  for (int i = 0; i < 10; i++) {
    // prints the coordinates before printing the ships
    std::cout << i << " ";
    // for the column
    for (int j = 0; j < 10; j++) {
      // if the ship is sunk, or it's an empty sea got hit before, just print
      // the ship (will be "s" / "-")
      if (this->ships[i][j]->isSunk() == true ||
          (this->ships[i][j]->getShipType() == "empty" &&
           this->ships[i][j]->getHit()[0] == true)) {
        std::cout << *(this->ships[i][j]) << " ";
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
              std::cout << *(this->ships[i][j]) << " ";
              break;
            }
            // otherwise, print "."
            else {
              std::cout << ". ";
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
      if (j == 9) {
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
  std::cout << "  0 1 2 3 4 5 6 7 8 9 \n";
  for (int i = 0; i < 10; i++) {
    // prints the coordinates before printing the ships
    std::cout << i << " ";

    for (int j = 0; j < 10; j++) {
      // prints the ships
      if (this->ships[i][j]->getShipType() == "battleship") {
        std::cout << "b"
                  << " ";
      } else if (this->ships[i][j]->getShipType() == "cruiser") {
        std::cout << "c"
                  << " ";
      }

      else if (this->ships[i][j]->getShipType() == "destroyer") {
        std::cout << "d"
                  << " ";
      }

      else if (this->ships[i][j]->getShipType() == "submarine") {
        std::cout << "s"
                  << " ";
      }

      else {
        std::cout << " "
                  << " ";
      }

      // lastly, if it's the end of the column, prints an empty line
      if (j == 9) {
        std::cout << "\n";
      }
    }
  }
  std::cout << "\n";
}
