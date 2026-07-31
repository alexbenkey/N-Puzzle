# N-Puzzle
Using the A* algorithm to solve n N-Puzzle

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

## Heuristics

### Misplaced Tiles
[implemented]()
_"Counts the number of tiles not in their goal position. It is simple and admissible but often inefficient as it ignores tile distance."_

Counts the number of tiles (excluding the empty tile) which are in the wrong position.

An extremely cheap heuristic allowing for fast calculations. However, its heuristic value is of little value and its computational gain is negligible compared to the Manhattan Distance, which should be preferred in practically all cases.


### Manhattan Distance
[implemented]()
_"Sums the horizontal and vertical distances each tile must move to reach its goal. It is more accurate than misplaced tiles and is sufficient to solve the 8-puzzle efficiently."_

Also known as the Taxicab distance, this heuristic is created as a sum of the horizontal and vertical distance between each tile and their target positions.

An extremely cheap heuristic, which has almost the same computational requirements as Misplaced Tiles. However it provides a significantly more valueable heuristic.

### Linear Conflict
[not implemented]()
_"Adds to the Manhattan distance when two tiles are in the same row or column but in the wrong order, requiring additional moves to resolve."_

Expansion to the Manhattan Distance.

### Walking Distance
[not implemented]()
_"Calculates the minimum moves required for tiles to reach their goals in separate 1D projections (rows and columns), accounting for tile conflicts."_

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

Build raylib and N-Puzzle with:

```sh
make
```

The Makefile builds `assets/raylib/src/libraylib.a` automatically before
linking the `npuzzle` executable.

---

# Usage


---

# References

[A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)

[Heuristic](https://en.wikipedia.org/wiki/Heuristic_(computer_science))

[Admissible heuristic](https://en.wikipedia.org/wiki/Admissible_heuristic)

[Raylib](https://github.com/raysan5/raylib)

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

# Note

```sh
# See branches
git branch
git branch -r
# Create branches
git switch -c [name]
# Create upstream branch and push
git push -u origin [name]
# Add other repo's to project as children
git submodule add [link] [dest]
# merge

# Clean after merge
git branch -d [name]
git fetch --prune

# Restore file after push
git fetch origin
git restore --source=origin/main path/to/file
git add path/to/file
git commit -m "Restore path/to/file to main"
git push

# Add to previous commit without new log entry
git add <files>
git commit --amend --no-edit
```

# TODO
- more heuristics
   - Misplaced Tiles: Counts the number of tiles not in their goal position. It is simple and admissible but often inefficient as it ignores tile distance. 
   - Manhattan Distance (MD): Sums the horizontal and vertical distances each tile must move to reach its goal. It is more accurate than misplaced tiles and is sufficient to solve the 8-puzzle efficiently. 
   - Linear Conflict: Adds to the Manhattan distance when two tiles are in the same row or column but in the wrong order, requiring additional moves to resolve. 
   - Walking Distance (WD): Calculates the minimum moves required for tiles to reach their goals in separate 1D projections (rows and columns), accounting for tile conflicts. 
   - Inversion Distance: Uses the number of inversions in the tile sequence to estimate the minimum vertical and horizontal moves required. 
- comparison operators upgrade
