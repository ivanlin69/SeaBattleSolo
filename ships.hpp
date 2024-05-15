#ifndef ships_hpp
#define ships_hpp

#include <memory>
#include <string>
#include <vector>

class Ocean;
class Ship {
    
private:
    // Helper functor for isSunk
    struct IsTrue{
        bool operator()(bool h) const { return h; }
    };
    
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
    static const int CARRIER_SIZE;
    static const int BATTLESHIP_SIZE;
    static const int DESTROYER_SIZE;
    static const int SUBMARINE_SIZE;
    static const int PATROLBOAT_SIZE;
    
    static const std::string TYPE_CARRIER;
    static const std::string TYPE_BATTLESHIP;
    static const std::string TYPE_DESTROYER;
    static const std::string TYPE_SUBMARINE;
    static const std::string TYPE_PATROLBOAT;
    static const std::string TYPE_EMPTY;
    
    static const std::vector<int> shipSizes;
    // Helper function for initializing the shipSizes
    static std::vector<int> initializingShipSizes();
    
    // Constructor initializing the ship's length.
    Ship(int length);
    
    int getBowRow() const { return bowRow; }
    int getBowColumn() const { return bowColumn; }
    int getLength() const { return length; }
    const std::vector<bool> &getHit() const { return hit; }
    
    // Pure virtual, no implementation in the base class
    // Must be overridden by all derived classes (unless a derived class is also
    // abstract)
    virtual std::string getShipType() const = 0;
    
    // Methods to manage ship status and placement.
    bool isSunk() const;
    bool isHorizontal() const { return bowHorizontal; }
    bool isValidSpot(int row, int column, Ocean &ocean) const;
    bool isAdjacentEmpty(int row, int column, Ocean &ocean) const;
    bool okToPlaceShipAt(int row, int column, bool horizontal, Ocean &ocean) const;
    void placeShipAt(int row, int column, bool horizontal, Ocean &ocean);
    virtual bool shootAt(int row, int column);
    // Overloading the stream insertion operator for easy display
    friend std::ostream& operator<<(std::ostream &os, const Ship &ship);
    
    // Default virtual destructor for proper cleanup in derived classes
    virtual ~Ship() {}
};

// Concrete classes representing different types of ships
class Carrier : public Ship {
    
public:
    Carrier() : Ship(CARRIER_SIZE) {}
    std::string getShipType() const {
        return TYPE_CARRIER;
    }
};

class Battleship : public Ship {
    
public:
    Battleship() : Ship(BATTLESHIP_SIZE) {}
    std::string getShipType() const {
        return TYPE_BATTLESHIP;
    }
};

class Destroyer : public Ship {
    
public:
    Destroyer() : Ship(DESTROYER_SIZE) {}
    std::string getShipType() const {
        return TYPE_DESTROYER;
    }
};

class Submarine : public Ship {
    
public:
    Submarine() : Ship(SUBMARINE_SIZE) {}
    std::string getShipType() const {
        return TYPE_SUBMARINE;
    }
};

class Patrolboat : public Ship {
    
public:
    Patrolboat() : Ship(PATROLBOAT_SIZE) {}
    std::string getShipType() const {
        return TYPE_PATROLBOAT;
    }
};


class EmptySea : public Ship {
    
public:
    EmptySea(int row, int column) : Ship(1) {
        bowRow = row;
        bowColumn = column;
    }
    bool shootAt (int row, int column);
    bool isSunk() const { return false; }
    std::string getShipType() const {
        return TYPE_EMPTY;
    }
};

#endif
