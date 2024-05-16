#ifndef ocean_hpp
#define ocean_hpp

#include <vector>

class Ship;

// Represents the game board and manages the grid and state of ships
class Ocean {
    
private:
    // Dimensions of the ocean grid
    int maxRow, maxColumn;
    // Total number of ships that can be placed in the ocean
    int totalShips;
    // Total number of shots fired by the player
    int firedShots;
    // Number of ships that have been sunk
    int sunkShips;
    // 2D grid of ships
    std::vector<std::vector<std::shared_ptr<Ship>>> ships;
    // Max number of each type of ship allowed
    std::vector<int> maxShipsCount;
    // Helper function to determine if a cell is occupied by a ship
    bool isOccupied(int row, int col) const;
    
public:
    static constexpr int SUGGESTED_MAXGRIDSIZE = 20;
    // Determine if the maximum number of ships have been placed
    static bool isMaxShipsAllowed(int row, int col, std::vector<int> shipsCount);
    // Constructor to initialize the ocean grid with specific dimensions and ship counts
    Ocean(int row, int col, std::vector<int> shipsCount);
    
    int getMaxRow() const { return maxRow; }
    int getMaxColumn() const { return maxColumn; }
    int getFiredShots() const { return firedShots; }
    // Returns the minimum number of hits needed to sink all ships (for game evaluation)
    int getMinHitCounts() const;
    std::shared_ptr<Ship> &getShip(int row, int col) { return ships[row][col]; }
    bool isGameOver() const;
    // Processes a shot at a given position, returning true if a ship is hit
    bool shootAt(int row, int col);
    void putShipRandomly(std::shared_ptr<Ship> shipPtr);
    // Places a ship randomly on the grid, used during game setup
    void putAllshipsRandomly();
    // Print the ocean grid without showing all ships (for game play)
    void print() const;
    // Print the ocean grid with ships visible (for testing)
    void printWithShips() const;
    ~Ocean() = default;
};

#endif
