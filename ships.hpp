#ifndef ships_hpp
#define ships_hpp

#include <memory>
#include <string>
#include <vector>

class Ocean;

class Ship : public std::enable_shared_from_this<Ship> {

protected:
  static constexpr int BATTLESHIP_SIZE = 4;
  static constexpr int CRUISER_SIZE = 3;
  static constexpr int DESTROYER_SIZE = 2;
  static constexpr int SUBMARINE_SIZE = 1;
  static const std::string BATTLESHIP_TYPE;
  static const std::string CRUISER_TYPE;
  static const std::string DESTROYER_TYPE;
  static const std::string SUBMARINE_TYPE;

private:
  int bowRow, bowColumn, length;
  bool horizontal;
  std::vector<bool> hit;

public:
  Ship(int l);

  int getBowRow() const { return bowRow; }
  int getBowColumn() const { return bowColumn; }
  int getLength() const { return length; }
  const std::vector<bool> &getHit() const { return hit; }
  virtual std::string getShipType() const = 0;
  void setBowRow(int r) { bowRow = r; }
  void setBowColumn(int c) { bowColumn = c; }
  void setHorizontal(bool h) { horizontal = h; }
  void setHit(int r, bool b) { hit[r] = b; }

  bool isSunk() const;
  bool isHorizontal() const { return horizontal; }
  bool isValidSpot(int row, int column, Ocean &ocean) const;
  bool isAdjacentEmpty(int row, int column, Ocean &ocean) const;
  bool okToPlaceShipAt(int row, int column, bool horizontal,
                       Ocean &ocean) const;
  void placeShipAt(int row, int column, bool horizontal, Ocean &ocean);
  virtual bool shootAt(int row, int column);

  friend std::ostream &operator<<(std::ostream &os, const Ship &s);
  virtual ~Ship() = default;
};

class Battleship : public Ship {

public:
  Battleship() : Ship(BATTLESHIP_SIZE) {}
  std::string getShipType() const { return BATTLESHIP_TYPE; }
};

class Cruiser : public Ship {

public:
  Cruiser() : Ship(CRUISER_SIZE) {}
  std::string getShipType() const { return CRUISER_TYPE; }
};

class Destroyer : public Ship {

public:
  Destroyer() : Ship(DESTROYER_SIZE) {}
  std::string getShipType() const { return DESTROYER_TYPE; }
};

class Submarine : public Ship {

public:
  Submarine() : Ship(SUBMARINE_SIZE) {}
  std::string getShipType() const { return SUBMARINE_TYPE; }
};

class EmptySea : public Ship {

public:
  EmptySea() : Ship(1) {}
  bool shootAt(int row, int column);
  bool isSunk() const { return false; }
  std::string getShipType() const { return "empty"; }
};

#endif
