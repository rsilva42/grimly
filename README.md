# Grimly

Grimly is a maze solver.

## Installation & Usage

This project is compiled with a Makefile:
```bash
make grimly
./grimly file.map [file2.map ...]
```
The program can take multiple files at a time printing the solution for each before iterating to the next file.

## What are `.map` files?

The program supports `.map` files which have a header followed by the actual map.

The header is the first line of the file which has the dimensions of the map and the characters used in the following order: height (end denoted by an 'x'), width, wall character, empty character, path character, start character, end character.

For example, "`10x10* o12`" denotes a `10` by `10` grid where walls are `*`, empty spaces are `' '`, and the solution must be denoted with `o` starting from `1` and ending at `2`.

After the header is the map section which is the actual maze to be solved.

Full map file:
```
10x10* o12
**1*******
**  *    *
*    *  **
* *     **
* *     **
*        *
*  *   * *
**       *
**  *    *
******2***

```

Maps can be created with the included ruby file `maze_gen.rb`:
```bash
./maze_gen.rb height width characters
```
Making a 10 by 10 maze:
```bash
./maze_gen.rb 10 10 "* o12"
```

Additional rules as specified in [Grimly Instructions.pdf](https://github.com/rsilva42/grimly_rust/blob/master/Grimly%20Instructions.pdf) page 5 (adjusted for consistency):

* All lines must respect the sizes given in the first line (HeightxWidth).
* There can only be one start.
* There must be at least one end.
* There must be a solution to the maze.
* The maze will not be more than a billion squared.
* At the end of each line, there is a new line.
* The characters present in the maze must only be those shown in the first line.
* If there is an invalid maze, there must be an error message and then proceed to the next maze if any.


## Project specifications
The project is built to the specifications of the [Grimly Instructions.pdf](https://github.com/rsilva42/grimly_rust/blob/master/Grimly%20Instructions.pdf) document. I took some liberties, mainly using the standard library and more specific error messages.
