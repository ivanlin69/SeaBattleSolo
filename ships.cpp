#include "ships.hpp"
#include "ocean.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const std::string Ship::BATTLESHIP_TYPE = "battleship";
const std::string Ship::CRUISER_TYPE = "cruiser";
const std::string Ship::DESTROYER_TYPE = "destroyer";
const std::string Ship::SUBMARINE_TYPE = "submarine";

Ship::Ship(int l) : bowRow(-1), bowColumn(-1), length(l), horizontal(false) {
  hit.resize(l, false);
}

bool Ship::isSunk() const {
  return std::all_of(hit.begin(), hit.end(), [](bool h) { return h; });
}

bool Ship::isValidSpot(int row, int column, Ocean &ocean) const {

  auto rowLimit = ocean.getShipArray().size() - 1;
  auto colLimit = ocean.getShipArray()[0].size() - 1;

  return !(row < 0 || column < 0 || row > rowLimit || column > colLimit);
}

bool Ship::isAdjacentEmpty(int row, int column, Ocean &ocean) const {

  for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
    for (int colOffset = -1; colOffset <= 1; colOffset++) {
      int curRow = row + rowOffset;
      int curColumn = column + colOffset;

      if ((rowOffset == 0 && colOffset == 0) ||
          !(isValidSpot(curRow, curColumn, ocean)))
        continue;

      if (ocean.getShipArray()[curRow][curColumn]->getShipType() != "empty") {
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
        (ocean.getShipArray()[curRow][curColumn]->getShipType() != "empty"))
      return false;

    if (!isAdjacentEmpty(curRow, curColumn, ocean))
      return false;
  }
  return true;
}

void Ship::placeShipAt(int row, int column, bool horizontal, Ocean &ocean) {
  setBowRow(row);
  setBowColumn(column);
  setHorizontal(horizontal);

  for (int i = 0; i < getLength(); i++) {
    if (horizontal) {
      ocean.getShipArray()[row][column - i] = shared_from_this();
    } else {
      ocean.getShipArray()[row - i][column] = shared_from_this();
    }
  }
}

bool Ship::shootAt(int row, int column) {

  if (isSunk()) {
    return false;
  }

  int curRow = getBowRow();
  int curCol = getBowColumn();

  for (int i = 0; i < getLength(); i++) {
    if (curRow == row && curCol == column) {
      setHit(i, true);
      return true;
    }
    isHorizontal() ? curCol-- : curRow--;
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const Ship &s) {
  if (s.getShipType() == "empty") {
    s.isSunk() ? os << "-" : os << ".";
  } else {
    s.isSunk() ? os << "s" : os << "x";
  }
  return os;
}

bool EmptySea::shootAt(int row, int column) {
  if (getBowRow() == row && getBowColumn() == column) {
    setHit(0, true);
  }
  return false;
}
