# Square Survivors

Square Survivors is an exciting action game where you control a player character, fend off incoming enemies, and try to survive as long as possible. The game features shooting mechanics, enemy AI, and a leaderboard to track your high scores.

## Features

- Move your character using keyboard controls (WASD or Arrow keys)
- Shoot in multiple directions to fend off enemies
- Enemies spawn at increasing rates and shoot back at you
- Leaderboard to track high scores

## Controls

- **W / Up Arrow**: Move Up
- **S / Down Arrow**: Move Down
- **A / Left Arrow**: Move Left
- **D / Right Arrow**: Move Right
- **Space**: Shoot

## How to Build

### Prerequisites

- [CMake](https://cmake.org/download/)
- [SFML](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library)
- C++17 compatible compiler (e.g., g++, clang++, Visual Studio)

### Linux

1. **Install Dependencies**

    ```sh
    sudo apt-get update
    sudo apt-get install cmake g++ libsfml-dev
    ```

2. **Clone the Repository**

    ```sh
    git clone <repository_url>
    cd square_survivors
    ```

3. **Generate Build Files using CMake**

    ```sh
    mkdir build
    cd build
    cmake ..
    ```

    This command will generate the required Makefiles in the `build` directory.

4. **Build the Project**

    ```sh
    make
    ```

    This command will compile the project and produce an executable.

5. **Run the Game**

    ```sh
    ./SquareSurvivors
    ```

### Windows

1. **Install Dependencies**

    - Install [CMake](https://cmake.org/download/)
    - Install [Visual Studio](https://visualstudio.microsoft.com/) with C++ development tools
    - Download and install [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) (ensure you get the version compatible with Visual Studio)

2. **Clone the Repository**

    Open PowerShell or Command Prompt and run:

    ```sh
    git clone <repository_url>
    cd square_survivors
    ```

3. **Generate Build Files using CMake**

    ```sh
    mkdir build
    cd build
    cmake -G "Visual Studio 16 2019" ..
    ```

    Replace `"Visual Studio 16 2019"` with your version of Visual Studio if different.

4. **Build the Project**

    Open the generated `.sln` file in Visual Studio and build the solution.

5. **Run the Game**

    Run the compiled executable from the build directory or from within Visual Studio.

### macOS

1. **Install Dependencies**

    ```sh
    brew install cmake sfml
    ```

2. **Clone the Repository**

    ```sh
    git clone <repository_url>
    cd square_survivors
    ```

3. **Generate Build Files using CMake**

    ```sh
    mkdir build
    cd build
    cmake ..
    ```

    This command will generate the required Makefiles in the `build` directory.

4. **Build the Project**

    ```sh
    make
    ```

    This command will compile the project and produce an executable.

5. **Run the Game**

    ```sh
    ./SquareSurvivors
    ```

## How to Play

Upon starting the game, you will see a screen with the controls. Press **Enter** to start the game.

### Gameplay

- Use the movement keys (WASD or Arrow keys) to navigate your player.
- Press the Spacebar to shoot bullets in multiple directions.
- Avoid enemies and their bullets, and shoot them to earn points.
- The game will end if you lose all your lives. Enter your name to save your score if it's a high score.

### Game Over

If you achieve a high score, you will be prompted to enter your name. Press **R** to restart the game after a game over.

## Additional Information

- The project uses SFML for graphics and input handling.
- High scores are saved in `highscores.txt`.

## Contributing

Feel free to submit pull requests or report issues if you find any bugs or have suggestions for improvements.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.