# 3D Rotating Cube Rendering Project

## Overview
This project implements a 3D rotating cube rendered using ASCII characters. It uses rotation transformations, depth buffering, and perspective projection to create a dynamic and visually engaging 3D effect within a terminal environment. The program is written in C++ and demonstrates concepts such as matrix transformations, z-buffering, and interactive graphics rendering.

## Features
- **3D Rotation:** The cube rotates dynamically around the X, Y, and Z axes.
- **Perspective Projection:** Projects 3D points onto a 2D screen for realistic rendering.
- **Z-Buffering:** Ensures proper visibility of surfaces based on depth.
- **Multi-Cube Rendering:** Supports rendering multiple cubes with different sizes and positions.
- **ASCII Art:** Displays the cube using customizable ASCII characters.

## Prerequisites
- C++ Compiler (GCC, Clang, or MSVC recommended)
- Terminal or console capable of displaying ASCII characters

## How It Works
The program uses mathematical transformations to rotate and project 3D points onto a 2D plane. The steps involved include:

1. **Rotation:**
   - Each vertex of the cube is rotated around the X, Y, and Z axes using trigonometric functions.
   - Functions such as `getX`, `getY`, and `getZ` compute the rotated coordinates.

2. **Projection:**
   - The rotated 3D points are projected onto a 2D screen using a perspective projection formula.
   - The formula accounts for depth to create a realistic 3D effect.

3. **Z-Buffering:**
   - A z-buffer is used to determine the visibility of surfaces by comparing the depth of points.
   - Only the closest points to the camera are displayed.

4. **Rendering:**
   - The projected points are mapped to a character buffer that represents the 2D screen.
   - ASCII characters are used to represent the surfaces of the cube.

## Code Structure
### Key Functions
- **`getX`, `getY`, `getZ`:** Compute the rotated coordinates of a point.
- **`rotateSurfacePoint`:** Rotates a point, projects it to 2D, and updates the z-buffer and character buffer.
- **`main`:** The entry point of the program, handles rendering multiple cubes and updating the screen.

### Constants
- `SCREEN_WIDTH`: Width of the terminal screen in characters.
- `SCREEN_HEIGHT`: Height of the terminal screen in characters.
- `DEPTH`: Distance from the camera to the cube.
- `CUBE_WIDTH`: Size of the cube in 3D space.
- `SCALE`: Scaling factor for perspective projection.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments
Inspired by various ASCII art and 3D rendering tutorials. Special thanks to the open-source community for providing resources on 3D graphics and mathematical transformations.
