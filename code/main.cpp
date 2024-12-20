#include <iostream>
#include <chrono>
#include <thread>
#include "geometry.h"

// Constants
const int SCREEN_WIDTH = 100, SCREEN_HEIGHT = 44;
const float INCREMENT_SPEED = 0.6;
const float CUBE_WIDTH = 15;
const float DEPTH = 60;
const float SCALE = 30;

/**
 * Rotates a 3D point and updates the z-buffer and character buffer for rendering.
 *
 * @param Xr Rotation angle around the X-axis (in radians).
 * @param Yr Rotation angle around the Y-axis (in radians).
 * @param Zr Rotation angle around the Z-axis (in radians).
 * @param zBuffer Pointer to the depth buffer (z-buffer) used to handle visibility of surfaces.
 * @param buffer Pointer to the character buffer representing the rendered image on the screen.
 * @param cubeX X-coordinate of the 3D point to rotate.
 * @param cubeY Y-coordinate of the 3D point to rotate.
 * @param cubeZ Z-coordinate of the 3D point to rotate.
 * @param ch Character to use for rendering this point in the buffer.
 */
void rotateSurfacePoint(const float Xr, const float Yr, const float Zr, float* zBuffer, char* buffer, float cubeX, float cubeY, float cubeZ, char ch);

int main() {
    // Cube XYZ rotations & buffer
    float Xr = 0, Yr = 0, Zr = 0;
    float zBuffer[160 * 44];
    char buffer[160 * 44];

    while (true) {
        system("cls");

        // Reset cube buffer
        memset(buffer, ' ', SCREEN_WIDTH * SCREEN_HEIGHT);
        memset(zBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

        // Compute point rotations of each surface
        for (float cubeX = -CUBE_WIDTH; cubeX < CUBE_WIDTH; cubeX += INCREMENT_SPEED) {
            for (float cubeY = -CUBE_WIDTH; cubeY < CUBE_WIDTH;
                cubeY += INCREMENT_SPEED) {
                rotateSurfacePoint(Xr, Yr, Zr, zBuffer, buffer, cubeX, cubeY, -CUBE_WIDTH, '@');
                rotateSurfacePoint(Xr, Yr, Zr, zBuffer, buffer, CUBE_WIDTH, cubeY, cubeX, '$');
                rotateSurfacePoint(Xr, Yr, Zr, zBuffer, buffer, -CUBE_WIDTH, cubeY, -cubeX, '~');
                rotateSurfacePoint(Xr, Yr, Zr, zBuffer, buffer, -cubeX, cubeY, CUBE_WIDTH, '#');
                rotateSurfacePoint(Xr, Yr, Zr, zBuffer, buffer, cubeX, -CUBE_WIDTH, -cubeY, ';');
                rotateSurfacePoint(Xr, Yr, Zr, zBuffer, buffer, cubeX, CUBE_WIDTH, cubeY, '+');
            }
        }

        // Display 3D ASCII cube
        for (int row = 0; row < SCREEN_HEIGHT; row++) {
            for (int col = 0; col < SCREEN_WIDTH; col++) 
                std::cout << buffer[row * SCREEN_WIDTH + col];
            std::cout << '\n';
        }

        // Afterwards rotate cube
        Xr += 0.05;
        Yr += 0.05;
        Zr += 0.01;

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    return 0;
}


void rotateSurfacePoint(const float Xr, const float Yr, const float Zr, float* zBuffer, char* buffer, float cubeX, float cubeY, float cubeZ, char ch) {
    // Compute rotated x, y, and z coordinates for 3D point.
    float x = rotations::getX(Xr, Yr, Zr, cubeX, cubeY, cubeZ);
    float y = rotations::getY(Xr, Yr, Zr, cubeX, cubeY, cubeZ);
    float z = rotations::getZ(Xr, Yr, Zr, cubeX, cubeY, cubeZ) + DEPTH;

    // Calculate perspective projection
    float ooz = 1 / z;

    // Get x, y screen-space coordinates
    float xp = (int)(SCREEN_WIDTH / 2 + CUBE_WIDTH + SCALE * ooz * x * 2);
    float yp = (int)(SCREEN_HEIGHT / 2 + SCALE * ooz * y);

    // Update buffer and z-buffer if visible
    int idx = xp + yp * SCREEN_WIDTH;
    if (idx >= 0 && idx < SCREEN_WIDTH * SCREEN_HEIGHT) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}
