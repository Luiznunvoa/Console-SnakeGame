# Snake Game (Made by Luiz Gabriel)

## Description

This is a classic Snake game developed in C++ with the goal of exploring programming concepts, console manipulation, and simple game development. The intention behind this project was to enhance my coding skills, especially in creating text-based games, understanding real-time user input handling, and studying the use of standard C++ libraries and the Windows API to create a simple yet functional interface.

## Requirements

To run the game, you will need the following libraries and tools:

- **C++ Compiler**: The game was developed and tested using **GCC** (GNU Compiler Collection) and **Clang**, but any modern C++ compiler should work.
- **Windows Library**: Since the game uses the Windows API for console manipulation, it is only compatible with Windows systems.
- **IDE (Optional)**: The game was developed using **CLion**, but it can be compiled and run from the command line.

## Compilation

To compile the game, follow the instructions below:

1. Clone this repository to your development environment.
2. Open the terminal or command prompt.
3. Navigate to the project directory.
4. Run the compilation command:
   ```bash
   g++ -o SnakeGame main.cpp -lwinmm# Console-SnakeGame
5. Run the generated executable:
   ```bash
   SnakeGame.exe
## Gameplay
How to Play

  Start: When the game starts, you will be asked if you want to play. Press Yes to begin.
  Controls: Use the W, A, S, D keys to move the snake up, left, down, and right, respectively.
  Objective: The goal is to collect as many fruits as possible to increase your score and the length of the snake.
  Game Over: The game ends if the snake collides with the field's borders or itself. You will be asked if you want to play again.

## Scoring

  For each fruit collected, you earn 1 point.
  The maximum score required to win the game is 322 points.

## Tips

  Avoid colliding with the borders and the snake's own body(:

## Intention

The main intention behind developing this game was to improve my C++ programming skills, including practicing console manipulation and real-time input flow control. This project also allowed me to experiment with creating a simple game and better understand how interactions in the console work using the Windows API.
