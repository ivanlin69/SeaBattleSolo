#include "ships.hpp"
#include "ocean.hpp"
#include <iostream>
#include <string>
#include <vector>

Ship::Ship(int length)
    : bowRow(-1), bowColumn(-1), length(length), bowHorizontal(false) {
  hit.resize(length, false);
}

bool Ship::isSunk() const {
  return std::all_of(hit.begin(), hit.end(), [](bool h) { return h; });
}

bool Ship::isValidSpot(int row, int column, Ocean &ocean) const {
  return !(row < 0 || column < 0 || row > ocean.getMaxRow() - 1 ||
           column > ocean.getMaxColumn() - 1);
}

bool Ship::isAdjacentEmpty(int row, int column, Ocean &ocean) const {
  // Check all adjacent cells (8 directions)
  for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
    for (int colOffset = -1; colOffset <= 1; colOffset++) {
      int curRow = row + rowOffset;
      int curColumn = column + colOffset;

      // Skip the check for the original position or out-of-bound spots
      if ((rowOffset == 0 && colOffset == 0) ||
          !(isValidSpot(curRow, curColumn, ocean)))
        continue;

      if (ocean.getShip(curRow, curColumn)->getShipType() != Ship::TYPE_EMPTY) {
        return false;
      }
    }
  }
  return true;
}

bool Ship::okToPlaceShipAt(int row, int column, bool horizontal,
                           Ocean &ocean) const {

  for (int i = 0; i < getLength(); i++) {
    int curRow = horizontal ? row : (row - i);
    int curColumn = horizontal ? (column - i) : column;

    if (!(isValidSpot(curRow, curColumn, ocean)) ||
        (ocean.getShip(curRow, curColumn)->getShipType() != Ship::TYPE_EMPTY))
      return false;

    if (!isAdjacentEmpty(curRow, curColumn, ocean))
      return false;
  }
  return true;
}

void Ship::placeShipAt(int row, int column, bool horizontal, Ocean &ocean) {
  bowRow = row;
  bowColumn = column;
  bowHorizontal = horizontal;

  for (int i = 0; i < getLength(); i++) {
    ocean.getShip(horizontal ? row : row - i,
                  horizontal ? column - i : column) = shared_from_this();
  }
}

bool Ship::shootAt(int row, int column) {

  if (isSunk()) {
    return false;
  }

  int curRow = bowRow;
  int curCol = bowColumn;

  for (int i = 0; i < length; i++) {
    if (curRow == row && curCol == column) {
      hit[i] = true;
      return true;
    }
    bowHorizontal ? curCol-- : curRow--;
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const Ship &ship) {
  if (ship.getShipType() == Ship::TYPE_EMPTY) {
    ship.isSunk() ? os << "-" : os << ".";
  } else {
    ship.isSunk() ? os << "s" : os << "x";
  }
  return os;
}

bool EmptySea::shootAt(int row, int column) {
  if (bowRow == row && bowColumn == column) {
    hit[0] = true;
  }
  return false;
}
