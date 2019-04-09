# n_puzzle
Play and solve the [n-puzzle](https://en.wikipedia.org/wiki/15_puzzle) with [A* search](https://en.wikipedia.org/wiki/A*_search_algorithm) in C using [SDL2](https://www.libsdl.org/download-2.0.php). (42 Silicon Valley)

![animation](https://github.com/ashih42/n_puzzle/blob/master/Screenshots/anim.gif)

## Prerequisites

You are on macOS with `clang++`, `make`, and `brew` installed.

## Installing

```
./setup.sh
```

## Running

Generate a random puzzle of size `n`
```
./npuzzle -s n
```

Load a puzzle from `file`
```
./npuzzle -f file
```

## Controls

### Top-level Controls
* `P` Print log of moves.
* `R` Reset the puzzle.
* `Escape` Terminate the program.

### Graphics Controls
* `Tab` Select next background picture.
* `H` Toggle hint on/off.

### Player Controls 
* `Arrow Keys` Slide a tile toward empty position.
* `Backspace` Undo last move.

### Solver Controls
* `S` Solve the puzzle.
* `M` Select next search method.
* `K` Select next heuristic function.
* `D` Print diagnostics about current board state.
