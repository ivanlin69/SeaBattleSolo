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
Battleship is a strategic, single-player game where the player attempts to sink a fleet of ships by guessing their locations on a hidden grid. The ships are placed automatically by the program on a grid at the start of the game. The player's goal is to sink all ships by making strategic guesses about their positions.

### Ship Types and Sizes
The game includes various types of ships, each occupying a different number of consecutive squares on the grid, arranged either horizontally or vertically:
- **Battleship**: Size of 4 cells.
- **Cruiser**: Size of 3 cells.
- **Destroyer**: Size of 2 cells.
- **Submarine**: Size of 1 cell.

Ships cannot overlap each other or extend off the grid edges. The number and type of ships can be customized if playing in a customizable mode.

### Gameplay
1. **Setup**: At the start of the game, the program automatically places the ships on the grid. The placement is random but adheres to the rules of non-overlapping and within the grid bounds.
2. **Playing**: The player takes turns guessing coordinates on the grid to find and hit the ships. Each guess is marked on the grid: hits are marked with an "x" and misses with an "-".
3. **Sinking Ships**: When all the squares that a ship occupies have been hit, that ship is considered sunk. The game notifies the player when a ship has been sunk and the ship will be marked marked with an "s".

### Winning the Game
The objective is to sink all ships on the grid. The game is won when all ships have been sunk, and the game provides statistics at the end, such as the number of shots fired compared to the optimal number of shots needed.

### Strategy Tips
- **Use a scattergun approach early on** to hit parts of ships.
- **Once you have a hit**, focus your next guesses around that area to quickly sink the ship.
- **Keep track of which ships have been sunk** and the size of ships that remain to inform your guessing strategy.

### Customization Options
In customizable mode, players can set the grid size and choose the number and types of ships, allowing for a personalized gameplay experience!


## Getting Started

### Prerequisites

- A modern C++ compiler that supports C++17 (e.g., GCC, Clang, MSVC)
- CMake for building the project (optional)

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/ivanlin69/EnhancedBattleShipGame.git
   cd EnhancedBattleShipGame
   ```
2. **Compile the Game** (make sure you have a C++ compiler installed):
   ```bash
   clang++ -std=c++17 -o Battleship main.cpp processor.cpp ocean.cpp ships.cpp
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
