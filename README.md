# N-Puzzle

N-Puzzle is a variation on the classic sliding tile puzzle, the goal of the game is to move tiles into the single empty space until the specified end result is achieved. Our version allows you to explore the puzzle manually or sit back and let the solver do the hard work for you. We combine a raylib based interactive interface with an A* search algorithm, while allowing for different heuristics and search strategies to explore different ways of solving the puzzle. 

---

# Table of Contents
- [Implementation](#implementation)
- [Setup](#setup)
  - [Build](#build)
- [Usage](#usage)
- [References](#references)
- [Credits](#credits)
- [License](#license)

---

# Implementation

- Describe graphics
- Describe search

### Uniform vs greedy searches

Given that A* search algorithms function on the basis of heuristics, there is an inherent component of uncertainty to how remaining routes are determined. The principle of A* is to strike a balance between costs (previous moves made), and heuristic values (an optimistic indication of future moves based on the currently selected heuristic). 
Selecting greedy or uniform vs A* search allows the user to skew more towards one of those versus the other. 

- __Uniform cost__ search sorts the array of states by path cost, or *g* value, while completely devalueing heuristic value, this acts as what is effectively a breadth first search, trading efficiency for accuracy. 

- __Greedy search__ does effectively the opposite, focussing only on the heuristic, or *h* value of whatever particular heuristic is selected, meaning it selects whatever route looks shortest from the current state, but ignoring the route that has been taken so far. given that heuristics can be inaccurate this does not necessarily leave you with the best option, but it goes down the route that seems the most promising. 

- __A*__ combines the two by, at any given point, prioritizing for the *g + h* selecting for the lowest combination of the two. Thereby being the most balanced of the two in theory. 


### Solvability checker

The solvability checker works through comparing the start and target boards, reverted to a 1D version of the respective boards. It subsequently counts the swaps needed to reach target state from start and compares its parity to that of the manhatten distance of the same difference. if the parity of these two routes match the puzzle is deemed solvable, otherwise it is not. given that the checker only compares the orders based on what is given as the solved state, it is effectively layout-agnostic. 
If the puzzle is deemed unsolvable it is skipped by the solver. 


## Heuristics

### Displaced Tiles
Counts the number of tiles (excluding the empty tile) which are in the wrong position.

An extremely cheap heuristic allowing for fast calculations. However, its heuristic value is of little value and its computational gain is negligible compared to the Manhattan Distance, which should be preferred in practically all cases.


### Manhattan Distance
Also known as the Taxicab distance, this heuristic is created as a sum of the horizontal and vertical distance between each tile and their target positions.

An extremely cheap heuristic, which has almost the same computational requirements as Misplaced Tiles. However it provides a significantly more valueable heuristic.

### Linear Conflict

Expansion to the Manhattan Distance. Starts with manhatten distance, but adds 2 for each *linear conflict* found. Linear conflicts are defined by numbers that are in their correct rows or cullumns, but in the wrong order. the heuristic adds two because the nPuzzle does not allow swaps, meaning that the relocation will require at least two moves to correct the conflict. 

### Walking Distance

Walking Distance converts a puzzle board into two abstract states. One representing the tile distribution across the rows, and the other respresenting the tile distribution across the columns. These abstract states only track how many tiles in each row/column belong in each row/column respectively. Instead of calculating the minimum steps required to solve the puzzle, these are used to BFS the minimum amount of steps required to get all tiles in their correct row/column.

The following puzzle is used in the examples below:
```
Puzzle:
[1, 2, 3]
[4, 5, 6]
[7, 8, _]

Solution:
[1, 2, 3]
[8, _, 4]
[7, 6, 5]
```

First the puzzle boards are converted into an abstract state by counting for each row/column how many of its tiles belong into each row/, where the empty tile is not counted. In the example: 
The puzzle on row 1 contains 4, 5, and 6. This row contains 0 tiles from solution row 0, 1 tile (4) from solution row 1, and 2 tiles (5 and 6) from solution row 2. This results in a abstract row 1 of [0, 1, 2] for the row abstract.
```
Rows:
[3, 0, 0]
[0, 1, 2]
[0, 1, 1]
```
The puzzle on column 1 contains 2, 5, and 8. This column conains 1 tile (8) from solution column 1, 1 tile (2) from solution column 1, and 1 tile (5) from solution column 2. This results in a abstract **row** 1 of [1, 1, 1] for the **column** abstract.
```
Columns:
[2, 0, 1]
[1, 1, 1]
[0, 1, 1]
```
The solution's abstract has a noticable diagonal form, where each tile is on its correct row/column.
```
Solution:
[3, 0, 0]
[0, 2, 0]
[0, 0, 3]
```
Starting from the solution's abstract, a BFS is performed while keeping track of which row contains the empty tile. Each iteration simulates moving the empty tile to an adjacent row by transferring the corresponding tile counts between the two affected rows in the abstract state. The BFS depth is tracked and stored alongside each unique generated abstract state.
```
Depth: 0 (solution)
Empty Tile Row: 1
[3, 0, 0]
[0, 2, 0]
[0, 0, 3]

Depth: 1 (empty tile moved up)
Empty Tile Row: 0
[2, 0, 0]
[1, 2, 0]
[0, 0, 3]

Depth: 1 (empty tile moved down)
Empty Tile Row: 3
[3, 0, 0]
[0, 2, 1]
[0, 0, 2]

And so on...
```

Additionally, the abstract functions as key for a lookup table, preventing the need for recalculation of abstracts. This is especially useful since many different puzzle boards can produce the same abstract (the empty position is not tracked for this). This lookup table stores the BFS depths by which the abstract is reached from the solution's abstract.

To calculate the Walking Distance heuristic, the BFS depth for both rows and columns are retrieved from their respective lookup tables and added together.

### Inversion Distance
[not implemented]()
_"Uses the number of inversions in the tile sequence to estimate the minimum vertical and horizontal moves required. "_

---

# Setup

This project uses [raylib](https://github.com/raysan5/raylib) as a Git
submodule, when cloning include the command to include submodules:

```sh
git clone --recurse-submodules https://github.com/alexbenkey/N-Puzzle.git
cd N-Puzzle
```

## Raylib submodule

If the repository was cloned without `--recurse-submodules`, initialize
raylib from the project root:

```sh
git submodule sync --recursive
git submodule update --init --recursive
```

To update raylib later to the commit recorded by this repository, run:

```sh
git submodule update --init --recursive
```

---

## Build

Before building ensure the submodules are included in the repository by using either of the following commands
```sh
# During cloning
git clone --recurse-submodules [target]
# After cloning
git submodule update --init --recursive
```

Build raylib and N-Puzzle with:

```sh
make
```

The Makefile builds `assets/raylib/src/libraylib.a` automatically before
linking the `npuzzle` executable.

---

# Usage

After the build is complete you can run npuzzle with one of the included puzzle foramtions:

```bash
./npuzzle < assets/pregens/solvable.3.3.puzzle
```

or use the included run script to generate a puzzle through the npuzzle generator: 

```bash
./run.sh -s 4
```

---

# References

[A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)

[Heuristic](https://en.wikipedia.org/wiki/Heuristic_(computer_science))
 - [Manhattan Distance](https://en.wikipedia.org/wiki/Taxicab_geometry)
 - [Walking Distance & Invert Distance](https://web.archive.org/web/20141224035932/http://juropollo.xe0.ru:80/stp_wd_translation_en.htm)
 - [Pattern Database](https://www.zabkat.com/blog/15-puzzle-pattern-database.htm)

[Admissible heuristic](https://en.wikipedia.org/wiki/Admissible_heuristic)

[Raylib](https://github.com/raysan5/raylib)

https://slidepuzzle.app/15-puzzle-solver/
https://www.zabkat.com/blog/15-puzzle-pattern-database.htm

---

# Credits
Othello<br>
[<img alt="LinkedIn" height="32px" src="https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png" target="_blank" />](https://github.com/OthelloPlusPlus)
[<img alt="LinkedIn" height="32px" src="https://upload.wikimedia.org/wikipedia/commons/c/ca/LinkedIn_logo_initials.png" target="_blank" />](https://nl.linkedin.com/in/orlando-hengelmolen)

# License
Copyright (c) 2026 Othello & ...

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

2. Any use of the Software in a public project, website, application, or
   distributed product must include clear attribution to the author (Othello),
   such as in a credits file, documentation, or an “About” section.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
