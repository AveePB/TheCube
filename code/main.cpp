#include <math.h>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <thread>

float Xr, Yr, Zr;

float cubeWidth = 20;
int width = 100, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 60;
float horizontalOffset;
float K1 = 40;

float incrementSpeed = 0.6;

float ooz;
int xp, yp;
int idx;

float calculateX(int x, int y, int z) {
    return y * sin(Xr) * sin(Yr) * cos(Zr) - z * cos(Xr) * sin(Yr) * cos(Zr) +
        y * cos(Xr) * sin(Zr) + z * sin(Xr) * sin(Zr) + x * cos(Yr) * cos(Zr);
}

float calculateY(int x, int y, int z) {
    return y * cos(Xr) * cos(Zr) + z * sin(Xr) * cos(Zr) -
        y * sin(Xr) * sin(Yr) * sin(Zr) + z * cos(Xr) * sin(Yr) * sin(Zr) -
        x * cos(Yr) * sin(Zr);
}

float calculateZ(int x, int y, int z) {
    return z * cos(Xr) * cos(Yr) - y * sin(Xr) * cos(Yr) + x * sin(Yr);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
    float x = calculateX(cubeX, cubeY, cubeZ);
    float y = calculateY(cubeX, cubeY, cubeZ);
    float z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

    ooz = 1 / z;

    xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
    yp = (int)(height / 2 + K1 * ooz * y);

    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    system("cls");

    while (1) {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);

        cubeWidth = 10;
        horizontalOffset = 1 * cubeWidth;
        // second cube
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth;
                cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }

        system("cls");

        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : 10);
        }

        Xr += 0.05;
        Yr += 0.05;
        Zr += 0.01;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    return 0;
}
