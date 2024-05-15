# CS161-KleeSweeper
Author: hiukaochan

This is a Genshin Impact fangame based on the famous game Minesweeper from Microsoft using C++ and Raylib GUI Library for CS161's solo project at HCMUS. All the graphics were drawn by the author - Thanh Hieu. The main character in KleeSweeper is called Klee who in the original game’s story is well known for the danger she presents because of the bombs she put around Mondstadt (a region in Genshin’s world). Therefore, her story is suitable for the Minesweeper remade game. 

User have to find all Klee’s bombs in the field, if you win, Kaeya from The Knights of Favonius will send you a thank-you letter, otherwise, he will tell you how hard The Knights of Favonius clearing the mess that caused from the unfigured bombs.

## Features
- The GUI of this program is drawn using Raylib.
- Every clickable button will change to darker color when user places mouse onto it for easier usage.

- Main menu
  - “NEW GAME” button allows user to start a new game with new board configurations (number of rows, columns and mines)
  - If there is a saved game, “LOAD SAVED GAME” button will appear for user to continue their saved game with saved properties.

- Difficulty Screen
  - The program offer three default board configurations Easy (9 x 9, 10 mines), Medium (16 x 16, 40 mines) and Hard (16 x 30, 99 mines).
  - Besides, this program allows user to customize board configuration by clicking “backward arrow” and “forward arrow” buttons. The number of mines will be automatically updated to smaller value if it reaches the number that larger than Current Rows times Current Columns minus 1.

- Gameplay Screen
  - User can open a cell by left-click, place a flag by right-click (a cell contains flag can not be opened by left-click)
    - Once user open the first cell, the game begins and timer starts to count.
    - The mines are not placed until the player opens the first cell. When opened, the mechanism guarantees the first cell is safe and will try to avoid mining on the first cell’s neighbors so the player could have a smooth start.
  - Keep track of time spent on the current game and the number of flags remaining.
      - The time spent on completing this game is used as the score.
      - The player cannot flag cells if the number of flags used reaches the number of mines on the board.
  - “Pause” button contains 4 features: Reset (Play again with unchanged board configurations), Resume (Return back to game from Pause screen), Save (Save current game into the file “savegame.txt” in build folder), Quit (Return to Main Menu)
  - When the game is over, a game over screen is displayed and informs the player how much time they spent on playing the game and the fastest time spent on winning a game with the same configuration.
  - All records will be stored in “highscore.txt” in build folder for future playing sessions.

## Unfinised Features
- This program cannot be run directly from .exe file, user must use terminal (which is inconvenient for user who is not used to working with terminal, but I hope the instructions I give below will be useful). That is because I cannot figure out how to link my resources (including images) to the direct executable file.
- This program can only be run on MacOS (because I build it on XCode, and Visual Studio does not support C++ on MacOS)

## Demo video
[![Watch video here](https://img.youtube.com/vi/fcC4k5uw0iw/0.jpg)](https://www.youtube.com/watch?v=fcC4k5uw0iw)


