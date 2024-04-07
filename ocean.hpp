#ifndef ocean_hpp
#define ocean_hpp

#include <vector>

class Ship;
class Ocean {

private:
  int maxRow, maxColumn, totalShips;
  int firedShots, sunkShips;
  std::vector<std::vector<std::shared_ptr<Ship>>> ships;
  std::vector<int> maxShipsCount;

  bool isOccupied(int row, int column) const;

public:
  static constexpr int SUGGESTED_MAXGRIDSIZE = 20;
  static bool isMaxShipsAllowed(int row, int column,
                                std::vector<int> shipsCount);

  Ocean(int row, int column, std::vector<int> shipsCount);

  int getMaxRow() const { return maxRow; }
  int getMaxColumn() const { return maxColumn; }
  int getFiredShots() const { return firedShots; }
  int getMinHitCounts() const;
  std::shared_ptr<Ship> &getShip(int row, int column) {
    return ships[row][column];
  }
  bool isGameOver() const;
  bool shootAt(int row, int column);
  void putShipRandomly(std::shared_ptr<Ship> shipPtr);
  void putAllshipsRandomly();
  void print() const;
  void printWithShips() const;
  virtual ~Ocean() = default;
};

#endif
