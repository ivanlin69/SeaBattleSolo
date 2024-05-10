# Battleship Game Enhanced

## Description
This project is a classic Battleship game implemented in C++. This version of the game is designed to be played on the command line and offers both a standard and a customizable game mode.

## Features
- **Customizable Grid Size**: Players can set the size of the game board.
- **Variable Number of Ships**: Players can decide how many ships of each type they want to place.
- **Random Ship Placement**: Ships are placed randomly on the board at the start of the game.
- **Gameplay Statistics**: Post-game, the game provides statistics such as the number of shots fired and the optimal number of shots. It also evaluates the user's performance, offering feedback based on how closely their shot count approached the minimum shots needed.
- **Debugging Views**: A view mode to see where all ships are located (for testing purposes).

## Game Rules and Mechanics

### Overview
Battleship is a strategic game where each player tries to sink the other's fleet of ships by guessing their locations on a hidden grid. The game is played on two grids per player: one for placing your own ships and another for marking your shots against the opponent.

### Ship Types and Sizes
In this version of Battleship, the fleet consists of the following types of ships, each with different sizes:
- **Battleship**: Size of 4 cells.
- **Cruiser**: Size of 3 cells.
- **Destroyer**: Size of 2 cells.
- **Submarine**: Size of 1 cell.

Each ship occupies a set number of consecutive squares on the grid, arranged either horizontally or vertically. The number and type of ships can be customized in the game settings.

### Gameplay
1. **Setup**: At the start of the game, players place their ships on their respective grids. Ships can be placed either horizontally or vertically but not diagonally, and they cannot overlap each other or go off the edge of the board.
2. **Playing**: Players take turns guessing coordinates on the opponent's grid, attempting to hit the opponent’s ships. On a hit, the game marks that grid position and the player takes another turn. On a miss, the turn passes to the opponent.
3. **Scoring Hits and Misses**: The game records each shot as a hit or a miss and marks this on the grid. Hits are typically marked with an "X" and misses with an "O".
4. **Sinking Ships**: When all the squares that a ship occupies have been hit, the ship is considered sunk. The game notifies the player when a ship has been sunk.

### Winning the Game
The game is won by the player who first sinks all the ships of the opponent. The game ends immediately when all ships of one player are sunk, declaring that player the winner.

### Strategy Tips
- **Try to randomize your shots** at the beginning of the game to cover ground efficiently.
- **Use patterns** once you have a hit to figure out the direction of the ship.
- **Remember the sizes of remaining ships** to better guess where they might be placed based on the available space.

### Customization Options
Players can customize the game by setting the grid size and the number and types of ships, making each game unique and tailored to their preference.

## Getting Started

### Prerequisites

- A modern C++ compiler that supports C++17 (e.g., GCC, Clang, MSVC)
- CMake for building the project (optional)

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/battleship-game.git
   cd battleship-game
   ```
2. **Compile the Game** (make sure you have a C++ compiler installed):
   ```bash
   clang++ -std=c++17 -o Battleship main.cpp Processor.cpp Ocean.cpp Ship.cpp
   ```
3. **Run the game**
   ```bash
   ./Battleship
   ```
   
## How to Play
- **Start the Game**: Run the executable after building.
- **Choose Your Mode**: Select the standard mode or customize your game setup.
- **Gameplay**: Follow the on-screen instructions to enter the coordinates where you wish to shoot.
- **Ending the Game**: The game ends automatically once all ships are sunk, or you can exit prematurely by typing --exit.

## Customization and Extensibility
- **Modular Design**: The Battleship game codebase is structured in a modular fashion, making it straightforward to customize elements like game rules, board size, and ship types. Developers can extend or modify the game mechanics according to their needs.
- **Plug-and-Play Functionality**: The game's architecture allows for easy adaptation, enabling users to easily change game settings such as the map size and number of ships. This flexibility also facilitates integration into larger systems or applications, allowing the Battleship game to function as a component within a more complex software environment.
- **Configurable Gameplay Options**: The game supports various configuration settings that allow users to adjust gameplay dynamics. This includes setting different game modes, adjusting the difficulty level, or customizing the number of ships and their placement, enhancing the game's replayability and challenge.

## Contributing
Contributions to the Sudoku Solver are welcome! Please fork the repository and submit a pull request with your enhancements.

## License
This project is licensed under the MIT License - see the [MIT License Documentation](https://opensource.org/licenses/MIT) for details.

## Contact
For support, please feel free to contact me.
