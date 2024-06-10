
# Catan Game Project

## Author: Sapir Dahan
**ID:** 325732972  
**Email:** sapirdahan2003@gmail.com

---

## Table of Contents
- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Card Hierarchy](#card-hierarchy)
- [Installation](#installation)
- [Usage](#usage)
- [Compilation and Execution](#compilation-and-execution)
- [Testing](#testing)
- [Memory Management](#memory-management)
- [Code Analysis](#code-analysis)
- [License](#license)

## Introduction
This project is an implementation of the popular board game "Catan". The game involves players collecting resources, building roads and settlements, and earning points to win the game. This implementation includes classes for players, cards, and the game board, as well as game logic to manage turns and resource distribution.

## Project Structure
The project consists of the following files:

- **Header Files:**
    - `Card.hpp`: Abstract base class for different types of cards.
    - `CardType.hpp`: Enum class defining different types of cards.
    - `DevelopmentCard.hpp`: Derived class for development cards.
    - `Dice.hpp`: Class for simulating dice rolls.
    - `Hexagon.hpp`: Class representing a hexagon tile on the board.
    - `Intersection.hpp`: Class representing an intersection on the board.
    - `Path.hpp`: Class representing a path on the board.
    - `Player.hpp`: Class representing a player in the game.
    - `ResourceCard.hpp`: Derived class for resource cards.
    - `SpecialCard.hpp`: Derived class for special cards.

- **Source Files:**
    - `Card.cpp`: Implementation of the abstract Card class.
    - `DevelopmentCard.cpp`: Implementation of development cards.
    - `Dice.cpp`: Implementation of dice rolls.
    - `Hexagon.cpp`: Implementation of hexagon tiles.
    - `Intersection.cpp`: Implementation of intersections.
    - `Path.cpp`: Implementation of paths.
    - `Player.cpp`: Implementation of players.
    - `ResourceCard.cpp`: Implementation of resource cards.
    - `SpecialCard.cpp`: Implementation of special cards.

- **Game Logic:**
    - `board.hpp` and `board.cpp`: Implementation of the game board.
    - `catan.hpp` and `catan.cpp`: Implementation of the main game logic.
    - `Game.hpp` and `Game.cpp`: Implementation of game management.

- **Main and Demo Files:**
    - `Demo.cpp`: Main file for running a demonstration of the game.
    - `TestCounter.cpp` and `Tests.cpp`: Implementation of test cases.

- **Makefile**: File for compiling and running the project.

## Card Hierarchy
The card system in this project is organized into a hierarchy to manage different types of cards efficiently.

- **Card (Abstract Base Class):**
    - The `Card` class is an abstract base class representing a generic card. It includes a virtual destructor for polymorphic cleanup and a pure virtual method that derived classes must implement.
    - **Methods:**
        - `virtual ~Card() = default;`: Virtual destructor.
        - `virtual CardType getType() const = 0;`: Pure virtual method to get the type of the card.

- **ResourceCard (Derived from Card):**
    - Represents resource cards in the game (e.g., Lumber, Brick, Wool, Grain, Ore).
    - **Attributes:**
        - `CardType type`: The type of the resource card.
    - **Methods:**
        - `ResourceCard(CardType type);`: Constructor to initialize the resource card with a specific type.
        - `CardType getType() const override;`: Returns the type of the resource card.

- **DevelopmentCard (Derived from Card):**
    - Represents development cards in the game (e.g., Knight, Victory Point, Road Building, Year of Plenty, Monopoly).
    - **Attributes:**
        - `CardType type`: The type of the development card.
    - **Methods:**
        - `DevelopmentCard(CardType type);`: Constructor to initialize the development card with a specific type.
        - `CardType getType() const override;`: Returns the type of the development card.
    - **Derived Classes:**
        - `KnightCard`: Represents a Knight development card.
        - `VictoryPointCard`: Represents a Victory Point development card.
        - `RoadBuildingCard`: Represents a Road Building development card.
        - `YearOfPlentyCard`: Represents a Year of Plenty development card.
        - `MonopolyCard`: Represents a Monopoly development card.

- **SpecialCard (Derived from Card):**
    - Represents special cards in the game (e.g., Largest Army).
    - **Attributes:**
        - `CardType type`: The type of the special card.
    - **Methods:**
        - `SpecialCard(CardType type);`: Constructor to initialize the special card with a specific type.
        - `CardType getType() const override;`: Returns the type of the special card.
    - **Derived Classes:**
        - `LargestArmyCard`: Represents the Largest Army special card.

## Installation
1. **Clone the repository:**
    ```sh
    git clone https://github.com/your-repo/catan-game.git
    cd catan-game
    ```

2. **Build the project:**
   Use the provided Makefile to build the project.
    ```sh
    make
    ```

## Usage

This project uses a Makefile to handle the compilation and execution of different parts of the project. Below are the instructions for building and running the demo, game, and tests.

### Running the Demo

To build and run the demo:
```sh
make demo
./demo
```

The `make demo` command compiles the demo executable.
The `./demo` command runs the compiled demo executable.

### Running the Game

To build and run the game:
```sh
make catan
./catan
```

The `make catan` command compiles the main game executable.
The `./catan` command runs the compiled game executable.

## Compilation and Execution

Use the provided Makefile for compilation and execution.

### Targets:
- **run**: Builds and runs the demo.
- **demo**: Builds the demo executable.
- **catan**: Builds the main game executable.
- **test**: Builds the test executable.
- **cppcheck**: Runs static code analysis using cppcheck.
- **valgrind**: Runs memory leak detection using valgrind.
- **clean**: Cleans the build artifacts.

## Testing

The project includes a set of test cases to verify the functionality of the game. These tests are implemented in `TestCounter.cpp` and `Tests.cpp`.

### Running Tests:
```sh
make test
./test
```

The `make test` command compiles the test executable.
The `./test` command runs the compiled test executable.

## Memory Management

The project uses Valgrind to check for memory leaks.

### Running Valgrind:
```sh
make valgrind
```

The `make valgrind` command runs Valgrind on both the demo and test executables to check for memory leaks.

## Static Code Analysis

Static code analysis is performed using cppcheck.

### Running Cppcheck:
```sh
make cppcheck
```

The `make cppcheck` command runs cppcheck on all source files for static code analysis.

## Cleaning Up

To clean up the build artifacts:
```sh
make clean
```

The `make clean` command removes all compiled object files and executables.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

Feel free to contribute to this project by forking the repository and submitting pull requests.

Happy coding!
