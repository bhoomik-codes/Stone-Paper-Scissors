# Rock-Paper-Scissors Game

A simple text-based Rock-Paper-Scissors game with multiple modes and a scoreboard. Players can compete against each other, face off against a computer, or participate in a tournament mode with a variety of players.

## Features

* **Player vs. Computer (PvC)**: Play against the computer with random moves.
* **Player vs. Player (PvP)**: Compete against a friend by entering your moves.
* **Tournament Mode**: Best of N rounds with human and computer players.
* **Scoreboard**: Tracks past games and tournaments, saving results with timestamps.
* **Recent Matches**: Displays the most recent game results.

## Game Modes

1. **Player vs Computer (PvC)**
   In this mode, you compete against the computer. The computer's moves are randomly selected. You can choose between Stone, Paper, or Scissors.

2. **Player vs Player (PvP)**
   Compete against another player by entering your choices of Stone, Paper, or Scissors.

3. **Tournament Mode**
   Play in a tournament format where you can compete against both human and computer players. The tournament progresses through rounds where winners advance.

## Installation

To run the game, simply compile and execute the C program. You will need a C compiler installed on your machine.

### Steps to Compile:

1. Download or clone this repository.
2. Open your terminal and navigate to the project directory.
3. Compile the code:

   ```
   gcc -o rps_game rps_game.c
   ```
4. Run the game:

   ```
   ./rps_game
   ```

## Gameplay

1. Upon starting the game, choose a game mode.
2. If you select **PvP** or **Tournament Mode**, players will be asked to enter their names.
3. In **PvP Mode**, players take turns selecting their moves.
4. In **Tournament Mode**, players can compete in a knockout style tournament.
5. After each round, the winner is announced and results are saved to a scoreboard file.

## Scoreboard

The results of the game are saved in a text file called `scoreboard.txt`. Each game entry includes:

* Date and time of the game.
* Game mode (PvC, PvP, or Tournament).
* Names of the players.
* The winner of the game.

You can view recent games by selecting the **Show Recent Games** option.

## Example Output

```
Choose Game Mode:
1. Player vs Computer (PvC)
2. Player vs Player (PvP)
3. Tournament Mode (Best of N rounds)
Enter your choice (1-3): 2

Enter Player 1 name: John
Enter Player 2 name: Jane
John - Enter s (STONE), p (PAPER), or z (SCISSOR): s
Jane - Enter s (STONE), p (PAPER), or z (SCISSOR): p
It's a draw!
```

## Requirements

* A C compiler (e.g., GCC).
* Basic understanding of C programming.

## Contributions

Feel free to contribute to this project by submitting pull requests or reporting issues. Suggestions for improvement are always welcome!

## License

This project is licensed under the MIT License.

---
