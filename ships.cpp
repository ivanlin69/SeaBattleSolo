#include "ships.hpp"
#include "ocean.hpp"
#include <iostream>
#include <string>
#include <vector>

const std::string Ship::TYPE_CARRIER = "Carrier";
const std::string Ship::TYPE_BATTLESHIP = "Battleship";
const std::string Ship::TYPE_DESTROYER = "Destroyer";
const std::string Ship::TYPE_SUBMARINE = "Submarine";
const std::string Ship::TYPE_PATROLBOAT = "PatrolBoat";
const std::string Ship::TYPE_EMPTY = "EmptySea";

const std::vector<int> Ship::shipSizes = {Ship::CARRIER_SIZE, Ship::BATTLESHIP_SIZE, Ship::DESTROYER_SIZE, Ship::SUBMARINE_SIZE, Ship::PATROLBOAT_SIZE};


// Initializes a ship with specified length, setting default values for bow position and orientation
// The ship's hit vector is also initialized(not hit (false) for all segments)
Ship::Ship(int length)
: bowRow(-1), bowColumn(-1), length(length), bowHorizontal(false) {
    hit.resize(length, false);
}

// Checks if the ship is completely sunk
// If all segments of the 'hit' vector has been hit(marked true), return true
bool Ship::isSunk() const {
    return std::all_of(hit.begin(), hit.end(), [](bool h) { return h; });
}

// Checks if a specified position is within the boundaries of the ocean
// Returns false if outside the bounds; otherwise, returns true
bool Ship::isValidSpot(int row, int column, Ocean &ocean) const {
    return !(row < 0 || column < 0 || row > ocean.getMaxRow() - 1 ||
             column > ocean.getMaxColumn() - 1);
}

/**
 Checks if all cells adjacent to a specified position (row, column) are empty
 This method ensures that no other ships are placed adjacent (diagonally, horizontally, or vertically) to the given position
 Returns true if all adjacent cells are empty; otherwise, returns false
 */
bool Ship::isAdjacentEmpty(int row, int column, Ocean &ocean) const {
    // Check all adjacent cells (8 directions)
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
        for (int colOffset = -1; colOffset <= 1; colOffset++) {
            int curRow = row + rowOffset;
            int curColumn = column + colOffset;
            
            // Skip the check for the original position or out-of-bound spots
            if ((rowOffset == 0 && colOffset == 0) || !(isValidSpot(curRow, curColumn, ocean)))
                continue;
            // If any adjacent cell contains a part of a ship, return false
            if (ocean.getShip(curRow, curColumn)->getShipType() != Ship::TYPE_EMPTY) {
                return false;
            }
        }
    }
    return true;
}

/**
 Validates if a ship can be placed at the specified position with the given orientation.
 Returns true if the ship can be placed; otherwise, returns false.
 */
bool Ship::okToPlaceShipAt(int row, int column, bool horizontal, Ocean &ocean) const {
    
    for (int i = 0; i < getLength(); ++i) {
        int curRow = horizontal ? row : (row - i);
        int curColumn = horizontal ? (column - i) : column;
        // Check if the current segment's position is valid and empty
        if (!(isValidSpot(curRow, curColumn, ocean)) ||
            ocean.getShip(curRow, curColumn)->getShipType() != Ship::TYPE_EMPTY)
            return false;
        // Ensure no adjacent cells have ships
        if (!isAdjacentEmpty(curRow, curColumn, ocean))
            return false;
    }
    return true;
}

/**
 Places the ship at the specified position within the ocean grid
 This method updates the ship's position and orientation, then marks the ship's presence in the ocean grid
 */
void Ship::placeShipAt(int row, int column, bool horizontal, Ocean &ocean) {
    bowRow = row;
    bowColumn = column;
    bowHorizontal = horizontal;
    // Place the ship in the ocean, marking each segment
    for (int i = 0; i < getLength(); i++) {
        ocean.getShip(horizontal ? row : row - i,
                      horizontal ? column - i : column) = shared_from_this();
    }
}

/**
 Attempts to shoot at a specified position(a ship cannot be shot at if it is already sunk)
 Returns true if the shot hits any part of the ship, otherwise false.
 */
bool Ship::shootAt(int row, int column) {
    
    if (isSunk()) {
        return false;
    }
    
    int curRow = bowRow;
    int curCol = bowColumn;
    // Check each segment of the ship to see if it matches the targeted position
    for (int i = 0; i < length; i++) {
        if (curRow == row && curCol == column) {
            hit[i] = true;
            return true;
        }
        // Update the position to check next segment based on orientation
        bowHorizontal ? curCol-- : curRow--;
    }
    // Shot missed
    return false;
}

/**
 Overloads the stream insertion operator for Ship objects
 Uses for easy printing of the ship's status (hit or not hit) to standard output
 */
std::ostream &operator<<(std::ostream &os, const Ship &ship) {
    if (ship.getShipType() == Ship::TYPE_EMPTY) {
        // treat an Empty sea differently for display
        ship.isSunk() ? os << "-" : os << ".";
    } else {
        ship.isSunk() ? os << "s" : os << "x";
    }
    return os;
}
/**
 Overrides for EmptySea class
 It should always return false as the EmptySea cannot be "hit"
 */
bool EmptySea::shootAt(int row, int column) {
    if (bowRow == row && bowColumn == column) {
        hit[0] = true;
    }
    return false;
}
