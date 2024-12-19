#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>

// Constants for cube rendering
const int WIDTH = 80;    // Width of the terminal
const int HEIGHT = 24;   // Height of the terminal
const float ASPECT_RATIO = 2.0; // Adjust for terminal character proportions
const float CUBE_SIZE = 1.0;    // Cube size
const float ROTATION_SPEED = 0.05; // Rotation speed

// Function to clear the screen
void clearScreen() {
    std::cout << "\033[2J\033[H"; // ANSI escape code to clear the terminal
}

// Function to render the ASCII cube
void renderCube(float angleX, float angleY) {
    // Cube vertices in 3D space
    std::vector<std::vector<float>> vertices = {
        {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        { CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        { CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},
        { CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},
        { CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},
        {-CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},
    };

    // Cube edges connecting vertices
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7},
    };

    // Screen buffer
    std::vector<std::string> screen(HEIGHT, std::string(WIDTH, ' '));

    // Rotation matrix calculations
    float cosX = cos(angleX), sinX = sin(angleX);
    float cosY = cos(angleY), sinY = sin(angleY);

    // Project and render each edge
    for (const auto& edge : edges) {
        int v1 = edge.first; int v2 = edge.second;

        // Rotate and project first vertex
        float x1 = vertices[v1][0], y1 = vertices[v1][1], z1 = vertices[v1][2];
        float tempY1 = y1 * cosX - z1 * sinX;
        z1 = y1 * sinX + z1 * cosX;
        y1 = tempY1;
        float tempX1 = x1 * cosY - z1 * sinY;
        z1 = x1 * sinY + z1 * cosY;
        x1 = tempX1;
        int screenX1 = (int)((x1 / (z1 + 3)) * ASPECT_RATIO * WIDTH / 4 + WIDTH / 2);
        int screenY1 = (int)((y1 / (z1 + 3)) * HEIGHT / 4 + HEIGHT / 2);

        // Rotate and project second vertex
        float x2 = vertices[v2][0], y2 = vertices[v2][1], z2 = vertices[v2][2];
        float tempY2 = y2 * cosX - z2 * sinX;
        z2 = y2 * sinX + z2 * cosX;
        y2 = tempY2;
        float tempX2 = x2 * cosY - z2 * sinY;
        z2 = x2 * sinY + z2 * cosY;
        x2 = tempX2;
        int screenX2 = (int)((x2 / (z2 + 3)) * ASPECT_RATIO * WIDTH / 4 + WIDTH / 2);
        int screenY2 = (int)((y2 / (z2 + 3)) * HEIGHT / 4 + HEIGHT / 2);

        // Draw the edge using Bresenham's line algorithm
        int dx = abs(screenX2 - screenX1), dy = abs(screenY2 - screenY1);
        int sx = screenX1 < screenX2 ? 1 : -1;
        int sy = screenY1 < screenY2 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;

        while (true) {
            if (screenX1 >= 0 && screenX1 < WIDTH && screenY1 >= 0 && screenY1 < HEIGHT) {
                screen[screenY1][screenX1] = '#';
            }
            if (screenX1 == screenX2 && screenY1 == screenY2) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; screenX1 += sx; }
            if (e2 < dy) { err += dx; screenY1 += sy; }
        }
    }

    // Print the screen buffer
    for (const auto& line : screen) {
        std::cout << line << '\n';
    }
}

int main() {
    float angleX = 0, angleY = 0;

    while (true) {
        clearScreen();
        renderCube(angleX, angleY);
        angleX += ROTATION_SPEED;
        angleY += ROTATION_SPEED / 2;

        // Control the frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}
