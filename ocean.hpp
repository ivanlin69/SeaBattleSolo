#ifndef ocean_hpp
#define ocean_hpp

#include <vector>

class Ship;
class Ocean {

private:
  std::vector<std::vector<std::shared_ptr<Ship>>> ships;
  int maxRow;
  int maxColumn;
  int totalShips;
  std::vector<int> maxShipsCount;
  int firedShots;
  int hitCounts;
  int sunkShips;

  bool isOccupied(int row, int column) const;

public:
  static bool isMaxShipsAllowed(int row, int column,
                                std::vector<int> shipsCount);

  Ocean(int row, int column, std::vector<int> shipsCount);

  int getMaxRow() const { return maxRow; }
  int getMaxColumn() const { return maxColumn; }
  int getFiredShots() const { return firedShots; }
  int getHitCounts() const { return hitCounts; }

  std::shared_ptr<Ship> &getShip(int row, int column) {
    return ships[row][column];
  }
  bool isGameOver() const;
  bool shootAt(int row, int column);
  void putShipRandomly(std::shared_ptr<Ship> shipPtr);
  void putAllshipsRandomly();
  void print() const;
  void printWithShips() const;
};

#endif
