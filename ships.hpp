#ifndef ships_hpp
#define ships_hpp

#include <memory>
#include <string>
#include <vector>

class Ocean;
class Ship : public std::enable_shared_from_this<Ship> {

protected:
  std::vector<bool> hit;
  int bowRow, bowColumn, length;
  bool bowHorizontal;

public:
  static constexpr int BATTLESHIP_SIZE = 4;
  static constexpr int CRUISER_SIZE = 3;
  static constexpr int DESTROYER_SIZE = 2;
  static constexpr int SUBMARINE_SIZE = 1;

  // C++17, inline variable
  static inline const std::string TYPE_BATTLESHIP = "battleship";
  static inline const std::string TYPE_CRUISER = "cruiser";
  static inline const std::string TYPE_DESTROYER = "destroyer";
  static inline const std::string TYPE_SUBMARINE = "submarine";
  static inline const std::string TYPE_EMPTY = "empty";

  Ship(int length);

  int getBowRow() const { return bowRow; }
  int getBowColumn() const { return bowColumn; }
  int getLength() const { return length; }
  const std::vector<bool> &getHit() const { return hit; }
  // Pure virtual, no implementation in the base class
  // Must be overridden by all derived classes (unless a derived class is also
  // abstract)
  virtual std::string getShipType() const = 0;

  bool isSunk() const;
  bool isHorizontal() const { return bowHorizontal; }
  bool isValidSpot(int row, int column, Ocean &ocean) const;
  bool isAdjacentEmpty(int row, int column, Ocean &ocean) const;
  bool okToPlaceShipAt(int row, int column, bool horizontal,
                       Ocean &ocean) const;
  void placeShipAt(int row, int column, bool horizontal, Ocean &ocean);
  virtual bool shootAt(int row, int column);

  friend std::ostream &operator<<(std::ostream &os, const Ship &ship);
  virtual ~Ship() = default;
};

class Battleship : public Ship {

public:
  Battleship() : Ship(BATTLESHIP_SIZE) {}
  std::string getShipType() const { return TYPE_BATTLESHIP; }
};

class Cruiser : public Ship {

public:
  Cruiser() : Ship(CRUISER_SIZE) {}
  std::string getShipType() const { return TYPE_CRUISER; }
};

class Destroyer : public Ship {

public:
  Destroyer() : Ship(DESTROYER_SIZE) {}
  std::string getShipType() const { return TYPE_DESTROYER; }
};

class Submarine : public Ship {

public:
  Submarine() : Ship(SUBMARINE_SIZE) {}
  std::string getShipType() const { return TYPE_SUBMARINE; }
};

class EmptySea : public Ship {

public:
  EmptySea(int row, int column) : Ship(1) {
    bowRow = row;
    bowColumn = column;
  }
  bool shootAt(int row, int column);
  bool isSunk() const { return false; }
  std::string getShipType() const { return TYPE_EMPTY; }
};

#endif
