# Maze Visibility


## Table of Contents

* [Requirement](#requirement)
* [Build](#build)
* [Run](#run)
   - [Load Map File](#load-map-file)
   - [Control](#control)
* [Develop Documentation](#develop-documentation)
   - [Maze File Structure](#maze-file-structure)
   - [Render Algorithm](#render-algorithm)
   - [Matrix Calculation](#matrix-calculation)


## Requirement

Please install the following programs before building. 

* [MinGW]
* [CMake]
* [FLTK]

Then, download the latest version header of [OpenGL] and add it to your compiler search path.

Then, install the following library and add it to your compiler search path.

* [FreeGLUT]
* [GLEW]

> Note: for the current version MinGW, when you are trying to build FreeGLUT, in some cases, it will throw `sub-scripted value is neither array nor pointer nor vector` error. If you accrue that issue, consider using the pre-build version of FreeGLUT. You can find the resource at [here](https://www.transmissionzero.co.uk/software/freeglut-devel/).

If you don't know how to set up your library, you can find a step-by-step tutorial at [here](https://medium.com/@bhargav.chippada/how-to-setup-opengl-on-mingw-w64-in-windows-10-64-bits-b77f350cea7e
).

[MinGW]: https://osdn.net/projects/mingw/
[CMake]: https://cmake.org/
[FLTK]: https://www.fltk.org/
[FreeGLUT]: http://freeglut.sourceforge.net/
[GLEW]: http://glew.sourceforge.net/


## Build

Run `cmake -G "MinGW Makefiles -B build ."` first,

and run `make all` in `build` folder.


## Run

All executable files can be run in console without argument.

### Load Map File

Just click the "Load Maze" button in the Map View form and enter your file path, then click the "OK" button.

![Load Map](./assets/Load-Map.png "Load Map")

### Control

In Maze View, you can use the mouse to control the camera direction (not including the z-axis) and position by
holding down the left button and dragging.

![Maze View](./assets/Maze-View.png "Maze View")

In Map View, you can use WASD key to control the camera position and use QE key to control camera direction.

![Map View](./assets/Map-View.png "Map View")

The two windows are synchronized with each other.

## Develop Documentation
### Maze file structure

> Note: line begin with `#` is the comment.

Following is a example mazes file of a two by two mazes, locate at `(0, 0)` to `(4, 4)`,

and contain an wall locate at `(0, 2)` to `(2, 2)`.

```
# how many vertices
# = W * H
9

# (x, y) coordinate of each vertices
0 0
2 0
4 0
0 2
2 2
4 2
0 4
2 4
4 4

# how many edges
# = 2 * W * H - (W + H)
12

# index of begin vertices of edges,
# index of end vertices of edges,
# index of cell of at the left-side of edges (-1 means out side of maze),
# index of cell of at the right-side of edges (-1 means out side of maze),
# edges is opaque or transparent,
# (r, g, b) triple of color in floating point format.

#  b  e   L   R   O/T  r       g       b
   0  1   0  -1    1   0.71765 0.55884 0.40663
   1  2   1  -1    1   0.21351 0.35721 0.62327
   2  5   1  -1    1   0.56432 0.98651 0.98751
   5  8   2  -1    1   0.13546 0.87591 0.75673
   8  7   2  -1    1   0.76121 0.61492 0.23121
   7  6   3  -1    1   0.64147 0.08607 0.48484
   6  3   3  -1    1   0.12515 0.12351 0.31511
   3  0   0  -1    1   0.31608 0.59933 0.60399
   4  3   0   3    1   0.00000 0.00000 0.00000
   4  1   1   0    0   0.00000 0.00000 0.00000
   4  5   2   1    0   0.00000 0.00000 0.00000
   4  7   3   2    0   0.00000 0.00000 0.00000

# how many cells
# = (W - 1) * (H - 1)
4

# index of edges surround each cell (clock-wise) 
 7  9  0  8
 2  1  9 10
 4  3 10 11
 8  6  5 11  

# (x, y, z) coordinate, initial position of viewer,
# viewer viewing direction,
# horizontal field of view.

#  x  y  z  v_deg  v_hf
   1  1  0   60    100

```


### Render Algorithm

1. Get Viewer Cell.

2. Check whether each surface at the cell boundary is in the view volume, and discard the surface that are not in the view volume.

3. Check whether each remaining surface is transparent, if not, add surface to render buffer.

4. Clipping view volume, go to adjacent cell, and then recursive step 2 to 4.

5. Render surface at render buffer using the first-in-last-out order.

### Matrix Calculation

Let $A={A_0, A_1, A_2, ...}$ be a set of points in three dimensions,
and $C={X_C, Y_C, Z_C}$, $D={X_D, Y_D, Z_D}$ be the points in three dimensions.

If we would to move $A$ coordinate such that $C$ become new Origin,
and rotate coordinate such that $D$ become new x-axis.

Instead of doing it one-by-one, step-by-step.

We can expand all points dimensions to four dimensions,
and let the new dimensions equal to $1$.

Then $A-C$ wound be equal to

$$\begin{pmatrix}1 & 0 & 0 & -X_C \\ 0 & 1 & 0 & -Y_C \\ 0 & 0 & 1 & -Z_C \\ 0 & 0 & 0 & 1\end{pmatrix} \begin{pmatrix}X_{A_0} \\ Y_{A_0} \\ Z_{A_0} \\ 1\end{pmatrix}$$

and we can calculate all point at once.

The same principle applies to rotation and scaling.

$$\begin{pmatrix} X_{Scaling} & 0 & 0 & 0 \\ 0 & Y_{Scaling} & 0 & 0 \\ 0 & 0 & Z_{Scaling} & 0 \\ 0 & 0 & 0 & 1\end{pmatrix} \begin{pmatrix} \cos(\theta) & \sin(\theta) & 0 & 0 \\ \sin(\theta) & \cos(\theta) & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1\end{pmatrix} \begin{pmatrix}1 & 0 & 0 & -X_C \\ 0 & 1 & 0 & -Y_C \\ 0 & 0 & 1 & -Z_C \\ 0 & 0 & 0 & 1\end{pmatrix} \begin{pmatrix}X_{A_0} \\ Y_{A_0} \\ Z_{A_0} \\ 1\end{pmatrix}$$

Furthermore, we can pre-calculate all transformation matrices, rotation matrices, and reflection matrices as a matrix,
and then calculate all points at once to get the final result.

$$ \begin{pmatrix}X'_{A_0} \\ Y'_{A_0} \\ Z'_{A_0} \\ 1\end{pmatrix} = T \begin{pmatrix}X_{A_0} \\ Y_{A_0} \\ Z_{A_0} \\ 1\end{pmatrix}$$
