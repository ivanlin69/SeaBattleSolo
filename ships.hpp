#ifndef ships_hpp
#define ships_hpp

#include <memory>
#include <string>
#include <vector>

class Ocean;
class Ship : public std::enable_shared_from_this<Ship> {
    
protected:
    // Tracks hits on each segment of the ship
    std::vector<bool> hit;
    // Coordinates of the bow (front) of the ship
    int bowRow, bowColumn;
    // Length of the ship
    int length;
    // Orientation of the ship (true if horizontal)
    bool bowHorizontal;
    
public:
    // Ship sizes as constants
    static constexpr int CARRIER_SIZE = 5;
    static constexpr int BATTLESHIP_SIZE = 4;
    static constexpr int DESTROYER_SIZE = 3;
    static constexpr int SUBMARINE_SIZE = 2;
    static constexpr int PATROLBOAT_SIZE = 1;
    
    
    // C++17, inline variable
    // Ship types as inline variables for easy modification and access
    static inline std::vector<int> shipSizes = {CARRIER_SIZE, BATTLESHIP_SIZE, DESTROYER_SIZE, SUBMARINE_SIZE, PATROLBOAT_SIZE};
    static inline const std::string TYPE_CARRIER = "Carrier";
    static inline const std::string TYPE_BATTLESHIP = "Battleship";
    static inline const std::string TYPE_DESTROYER = "Destroyer";
    static inline const std::string TYPE_SUBMARINE = "Submarine";
    static inline const std::string TYPE_PATROLBOAT = "PatrolBoat";
    static inline const std::string TYPE_EMPTY = "EmptySea";
    
    // Constructor initializing the ship's length.
    Ship(int length);
    
    int getBowRow() const { return bowRow; }
    int getBowColumn() const { return bowColumn; }
    int getLength() const { return length; }
    const std::vector<bool> &getHit() const { return hit; }
    
    // Pure virtual, no implementation in the base class
    // Must be overridden by all derived classes (unless a derived class is also abstract)
    virtual std::string getShipType() const = 0;
    
    // Methods to manage ship status and placement.
    bool isSunk() const;
    bool isHorizontal() const { return bowHorizontal; }
    bool isValidSpot(int row, int col, Ocean &ocean) const;
    bool isAdjacentEmpty(int row, int col, Ocean &ocean) const;
    bool okToPlaceShipAt(int row, int col, bool horizontal, Ocean &ocean) const;
    void placeShipAt(int row, int col, bool horizontal, Ocean &ocean);
    virtual bool shootAt(int row, int col);
    // Overloading the stream insertion operator for easy display
    friend std::ostream& operator<<(std::ostream &os, const Ship &ship);
    
    // Default virtual destructor for proper cleanup in derived classes
    virtual ~Ship() = default;
};

// Concrete classes representing different types of ships
class Carrier : public Ship {
    
public:
    Carrier() : Ship(CARRIER_SIZE) {}
    std::string getShipType() const override {
        return TYPE_CARRIER;
    }
};

class Battleship : public Ship {
    
public:
    Battleship() : Ship(BATTLESHIP_SIZE) {}
    std::string getShipType() const override {
        return TYPE_BATTLESHIP;
    }
};

class Destroyer : public Ship {
    
public:
    Destroyer() : Ship(DESTROYER_SIZE) {}
    std::string getShipType() const override {
        return TYPE_DESTROYER;
    }
};

class Submarine : public Ship {
    
public:
    Submarine() : Ship(SUBMARINE_SIZE) {}
    std::string getShipType() const override {
        return TYPE_SUBMARINE;
    }
};

class Patrolboat : public Ship {
    
public:
    Patrolboat() : Ship(PATROLBOAT_SIZE) {}
    std::string getShipType() const override {
        return TYPE_PATROLBOAT;
    }
};


class EmptySea : public Ship {
    
public:
    EmptySea(int row, int col) : Ship(1) {
        bowRow = row;
        bowColumn = col;
    }
    bool shootAt (int row, int col) override;
    bool isSunk() const { return false; }
    std::string getShipType() const override {
        return TYPE_EMPTY;
    }
};

#endif
