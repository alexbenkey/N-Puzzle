
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

# Rebase
## Check the logs
git log --oneline
## Check all logs for current branch that are not on main | count them
git log --oneline main..HEAD | wc -l
## Start interactvie rebase
git rebase -i HEAD~<commit count>
## Push the result
git push --force-with-lease

# Remove files from last commit
## undo last commit
git reset --soft HEAD~1
## remove files from git add
git restore --staged path/to/file1 path/to/file2
## recommit
git commit -m "your original commit message"
## push again
git push --force-with-lease

```

# TODO
- more heuristics
   - Misplaced Tiles: Counts the number of tiles not in their goal position. It is simple and admissible but often inefficient as it ignores tile distance. 
   - Manhattan Distance (MD): Sums the horizontal and vertical distances each tile must move to reach its goal. It is more accurate than misplaced tiles and is sufficient to solve the 8-puzzle efficiently. 
   - Linear Conflict: Adds to the Manhattan distance when two tiles are in the same row or column but in the wrong order, requiring additional moves to resolve. 
   - Walking Distance (WD): Calculates the minimum moves required for tiles to reach their goals in separate 1D projections (rows and columns), accounting for tile conflicts. 
   - Inversion Distance: Uses the number of inversions in the tile sequence to estimate the minimum vertical and horizontal moves required.
- comparison operators upgrade
- README
	- [Implementation](README.md#implementation)
	- [Usage](README.md#usage)
	- [Credits](README.md#credits)
	- [Licence](README.md#license)
	- Adding linkings to codebase during [explanation](README.md#L165)
	- General rereview of content

solvability note:
```c
	// Idont know, something with inversion and extra on even numbers
	// Spiral sucks
```
