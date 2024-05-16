#include "ocean.hpp"
#include "ships.hpp"
#include <iostream>
#include <memory>
#include <random>

/**
 Initializes the ocean grid with specified dimensions and sets up ships according to the provided counts
 Parameters:
  row: The number of rows in the ocean grid
  column: The number of columns in the ocean grid
  shipsCount: A vector containing counts of each type of ship to be placed in the ocean
 */
Ocean::Ocean(int row, int col, std::vector<int> shipsCount) : firedShots(0), sunkShips(0), totalShips(0), maxRow(row), maxColumn(col), maxShipsCount(shipsCount) {
    for (size_t i = 0; i < shipsCount.size(); ++i) {
        totalShips += shipsCount[i];
    }
    ships.resize(maxRow);
    for (int row = 0; row < maxRow; ++row) {
        ships[row].resize(maxColumn);
        for (int col = 0; col < maxColumn; col++) {
            // Initialize each cell with an EmptySea object
            ships[row][col] = std::make_shared<EmptySea>(row, col);
        }
    }
}

/**
 Checks if a specific grid position is occupied by a ship
 Returns true if the position is occupied by any ship other than an EmptySea
 */
bool Ocean::isOccupied(int row, int col) const {
    return !(ships[row][col]->getShipType() == Ship::TYPE_EMPTY);
}

/**
 Static method to determine if the maximum number of ships allowed on the grid is exceeded
 Parameters:
   maxRow: The number of rows in the grid.
   maxColumn: The number of columns in the grid.
   shipsCount: A vector of integers representing the number of each type of ship.
 Returns true if the calculated maximum capacity does not exceed 150% of the grid capacity, false otherwise.
 */
bool Ocean::isMaxShipsAllowed(int maxRow, int maxColumn, std::vector<int> shipsCount) {
    int maxCapacity = 0;
    std::vector<int> shipSize = Ship::shipSizes;
    for (size_t i = 0; i < shipsCount.size(); ++i) {
        maxCapacity += shipsCount[i] * (3 * (shipSize[i] + 2));
    }
    return maxCapacity <= maxRow * maxColumn * 1.5;
}

/**
 Calculates the minimum number of hits required to sink all ships in the ocean
 // Returns the total number of hits required to guarantee all ships are sunk
 */
int Ocean::getMinHitCounts() const {
    int minHitCounts = 0;
    std::vector<int> shipSize = Ship::shipSizes;
    for (size_t i = 0; i < maxShipsCount.size(); ++i) {
        minHitCounts += maxShipsCount[i] * shipSize[i];
    }
    return minHitCounts;
}

/**
 Determines if the game is over by checking if all ships have been sunk.
 Returns true if the number of sunk ships matches the total number of ships, otherwise false.
 */
bool Ocean::isGameOver() const {
    return sunkShips == totalShips;
}

/**
 Processes a shot at the specified grid location
 Parameters:
    row: Row index where the shot is fired.
    column: Column index where the shot is fired.
 Increments the shot counter and checks if the shot results in a ship being hit and possibly sunk.
 Returns true if the shot hits a ship, false otherwise.
 */
bool Ocean::shootAt(int row, int col) {
    bool effectiveShoot = ships[row][col]->shootAt(row, col);
    firedShots++;
    if (effectiveShoot && ships[row][col]->isSunk()) {
        sunkShips++;
    }
    return effectiveShoot;
}

/**
 Places a single ship randomly on the ocean grid
 Parameters:
    shipPtr: Shared pointer to the ship to be placed
 */
void Ocean::putShipRandomly(std::shared_ptr<Ship> shipPtr) {
    // Seed for generating random numbers
    std::random_device rd;
    // Random number generator
    std::default_random_engine gen(rd());
    // Distribution for row, colunm indices and boolean for orientation
    std::uniform_int_distribution<> rand_int_row(0, maxRow - 1);
    std::uniform_int_distribution<> rand_int_col(0, maxColumn - 1);
    std::bernoulli_distribution rand_bool(0.5);
    // generate random values for row, column and horizontal
    int randRow = rand_int_row(gen);
    int randCol = rand_int_col(gen);
    bool randHorizontal = rand_bool(gen);
    
    // Continuously generate new positions until a valid one is found
    while (
           !shipPtr->okToPlaceShipAt(randRow, randCol, randHorizontal, *this)) {
               randRow = rand_int_row(gen);
               randCol = rand_int_col(gen);
               randHorizontal = rand_bool(gen);
           }
    // Place the ship at the valid random position
    shipPtr->placeShipAt(randRow, randCol, randHorizontal, *this);
}

/**
 Places all ships specified in the maxShipsCount array randomly on the ocean grid
 */
void Ocean::putAllshipsRandomly() {
    // Ship type indices are: 0:Carrier, 1:Battleship, 2:Destroyer, 3:Submarine, 4:Patrolboat
    int currentShip = 0;
    int maxShipNum = totalShips;
    // Copy of ship counts to modify while placing ships
    std::vector<int> maxShipsCountCopy = maxShipsCount;
    // Place ships until all are placed
    while (maxShipNum > 0) {
        switch (currentShip) {
            case 0:
                // Check if more ships of the current type need to be placed
                if (maxShipsCountCopy[currentShip] > 0) {
                    putShipRandomly(std::make_shared<Carrier>());
                    // Decrement the count of this ship type
                    --maxShipsCountCopy[currentShip];
                    // Decrement the total number of ships to place
                    --maxShipNum;
                }
                break;
                
            case 1:
                // Check if more ships of the current type need to be placed
                if (maxShipsCountCopy[currentShip] > 0) {
                    putShipRandomly(std::make_shared<Battleship>());
                    // Decrement the count of this ship type
                    --maxShipsCountCopy[currentShip];
                    // Decrement the total number of ships to place
                    --maxShipNum;
                }
                break;
                
            case 2:
                if (maxShipsCountCopy[currentShip] > 0) {
                    putShipRandomly(std::make_shared<Destroyer>());
                    --maxShipsCountCopy[currentShip];
                    --maxShipNum;
                }
                break;
                
            case 3:
                if (maxShipsCountCopy[currentShip] > 0) {
                    putShipRandomly(std::make_shared<Submarine>());
                    --maxShipsCountCopy[currentShip];
                    --maxShipNum;
                }
                break;
                
            case 4:
                if (maxShipsCountCopy[currentShip] > 0) {
                    putShipRandomly(std::make_shared<Patrolboat>());
                    --maxShipsCountCopy[currentShip];
                    --maxShipNum;
                }
                break;
        }
        
        if (maxShipsCountCopy[currentShip] > 0) {
            continue;
        } else {
            ++currentShip;
        }
    }
}

void Ocean::print() const {
    // print the coordinates for the column
    std::cout << "  ";
    for (int col = 0; col < maxColumn; ++col) {
        if (col < 10) {
            std::cout << " " << col << " ";
        } else {
            std::cout << col << " ";
        }
    }
    std::cout << "\n";
    // use nested for loops to get and prints the ships
    // for the row
    for (int row = 0; row < maxRow; ++row) {
        // prints the coordinates before printing the ships
        if (row < 10) {
            std::cout << " " << row << " ";
        } else {
            std::cout << row << " ";
        }
        // for the column
        for (int col = 0; col < maxColumn; ++col) {
            // if the ship is sunk, or it's an empty sea got hit before, just print
            // the ship (will be "s" / "-")
            if (this->ships[row][col]->isSunk() == true ||
                (this->ships[row][col]->getShipType() == Ship::TYPE_EMPTY &&
                 this->ships[row][col]->getHit()[0] == true)) {
                // Output the representation of the ship at this position
                std::cout << *(this->ships[row][col]) << "  ";
            }
            
            // if the ship isn't sunk
            else {
                // gets the condition of the ship at the given location
                int bowRow = this->ships[row][col]->getBowRow();
                int bowColumn = this->ships[row][col]->getBowColumn();
                
                // iterates over the ship's hit array to check if the part is hit or not
                for (int l = 0; l < this->ships[row][col]->getLength(); ++l) {
                    if (bowRow == row && bowColumn == col) {
                        // if is hit, then print the ship
                        if (this->ships[row][col]->getHit()[l] == true) {
                            std::cout << *(this->ships[row][col]) << "  ";
                            break;
                        } else {
                            // otherwise, print ". "
                            std::cout << ".  ";
                            break;
                        }
                    } else {
                        if (this->ships[row][col]->isHorizontal()) {
                            --bowColumn;
                        } else {
                            --bowRow;
                        }
                    }
                }
            }
            // If it's the end of the column, prints an empty line
            if (col == maxColumn - 1) {
                std::cout << "\n";
            }
        }
    }
}

// Prints the Ocean with the location of the ships.(just for debugging)
void Ocean::printWithShips() const {
    // similar to print() but only shows the locations of the ships
    std::cout << "**The following map is shown for dugging purpose. Need to be removed while production.**\n\n";
    std::cout << "  ";
    for (int col = 0; col < maxColumn; ++col) {
        if (col < 10) {
            std::cout << " " << col << " ";
        } else {
            std::cout << col << " ";
        }
    }
    std::cout << "\n";
    for (int row = 0; row < maxRow; ++row) {
        // prints the coordinates before printing the ships
        if (row < 10) {
            std::cout << " " << row << " ";
        } else {
            std::cout << row << " ";
        }
        // Print a specific marker based on ship type or a blank space for empty sea
        for (int col = 0; col < maxColumn; ++col) {
            if (this->ships[row][col]->getShipType() == Ship::TYPE_CARRIER) {
                std::cout << "c  ";
            } else if (this->ships[row][col]->getShipType() == Ship::TYPE_BATTLESHIP) {
                std::cout << "b  ";
            } else if (this->ships[row][col]->getShipType() == Ship::TYPE_DESTROYER) {
                std::cout << "d  ";
            } else if (this->ships[row][col]->getShipType() == Ship::TYPE_SUBMARINE) {
                std::cout << "s  ";
            } else if (this->ships[row][col]->getShipType() == Ship::TYPE_PATROLBOAT) {
                std::cout << "p  ";
            } else {
                std::cout << "   ";
            }
            // If it's the end of the column, prints an empty line
            if (col == maxColumn - 1) {
                std::cout << "\n";
            }
        }
    }
    std::cout << "\n";
    std::cout << "**The above map is shown for dugging purpose. Need to be removed while production.**\n";
}
