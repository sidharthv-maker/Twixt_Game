# Twixt_Game
Twixt Game – C Implementation

This project implements a console-based version of the Twixt board game using the C programming language. Two players, Red and Black, take turns placing pegs on a grid while following Twixt rules. Red attempts to connect the top edge to the bottom edge, while Black tries to connect the left edge to the right edge.

When two pegs of the same player are placed in a knight-move distance (like in chess), a link is automatically created if it does not cross any existing links. The program checks for link validity, prevents intersections, and determines the winner using a recursive path search.

Features

Turn-based two-player gameplay

Automatic knight-move link detection

Link intersection prevention

Board visualization in the terminal

Recursive win detection

Move validation for Twixt placement rules

Game Rules (Simplified)

Players alternate turns placing pegs.

Red connects Top → Bottom

Black connects Left → Right

Links form automatically between same-colored pegs if:

They are a knight's move apart

The link does not cross another link

Red cannot place pegs in the first or last column.

Black cannot place pegs in the first or last row.

Corners cannot be used.

The first player to connect their two sides wins the game.

Project Structure
.
├── main.c          # Main game loop and player interaction
├── functions.c     # Game logic and helper functions
├── functions.h     # Data structures and function declarations
└── README.md
How to Compile and Run
Compile
gcc main.c functions.c -o twixt
Run
./twixt
How to Play

Run the program.

The board will be displayed.

Enter the row and column where you want to place your peg.

Example input:

Enter row col: 4 5

To exit the game:

-1 -1
