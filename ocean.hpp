#ifndef ocean_hpp
#define ocean_hpp

#include <vector>

class Ship;
class Ocean {

private:
  std::vector<std::vector<std::shared_ptr<Ship>>> ships;
  int shotsFired;
  int hitCount;
  int shipsSunk;

public:
  Ocean();

  int getShotsFired() const { return shotsFired; }
  int getHitCount() const { return hitCount; }
  int getShipsSunk() const { return shipsSunk; }
  std::vector<std::vector<std::shared_ptr<Ship>>> &getShipArray() {
    return ships;
  }
  bool isOccupied(int row, int column) const;
  bool isGameOver() const;
  bool shootAt(int row, int column);
  void putShipRandomly(std::shared_ptr<Ship> shipPtr);
  void placeAllShipsRandomly();
  void print() const;
  void printWithShips() const;
};

#endif
