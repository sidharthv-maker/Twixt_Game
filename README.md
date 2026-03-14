# Twixt Game – C Implementation

This project implements a **console-based version of the Twixt board game** using the C programming language. Two players, **Red and Black**, take turns placing pegs on a grid while following Twixt rules. Red attempts to connect the **top edge to the bottom edge**, while Black tries to connect the **left edge to the right edge**.

When two pegs of the same player are placed in a **knight-move distance (like in chess)**, a link is automatically created if it does not cross any existing links. The program checks for link validity, prevents intersections, and determines the winner using a recursive path search.

---

## Features

- Turn-based **two-player gameplay**
- Automatic **knight-move link detection**
- **Link intersection prevention**
- **Board visualization in the terminal**
- **Recursive win detection**
- Move validation for **Twixt placement rules**

---

## Game Rules (Simplified)

- Players alternate turns placing pegs.
- **Red connects Top → Bottom**
- **Black connects Left → Right**
- Links form automatically between same-colored pegs if:
  - They are a **knight's move apart**
  - The link does **not cross another link**
- Red **cannot place pegs in the first or last column**.
- Black **cannot place pegs in the first or last row**.
- Corner cells cannot be used.
- The first player to connect their two sides **wins the game**.

---

## Project Structure
├── main.c # Handles game loop, player input, and turn management
├── functions.c # Contains core game logic (links, intersections, win detection)
├── functions.h # Structure definitions, constants, and function declarations
└── README.md # Project documentation

---

## How to Compile

Use GCC to compile the program:
gcc main.c functions.c -o twixt
## How to Run
./twixt

---

## How to Play

1. Run the program.
2. The board will be displayed in the terminal.
3. Enter the **row and column** where you want to place your peg.

Example:
Enter row col: 4 5
---
To exit the game:
-1 -1
---
