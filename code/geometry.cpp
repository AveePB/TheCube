#include <iostream>
#include "geometry.h"

namespace rotations {

    float getX(const float Xr, const float Yr, const float Zr, int x, int y, int z) {
        return y * sin(Xr) * sin(Yr) * cos(Zr) - z * cos(Xr) * sin(Yr) * cos(Zr) +
            y * cos(Xr) * sin(Zr) + z * sin(Xr) * sin(Zr) + x * cos(Yr) * cos(Zr);
    }

    float getY(const float Xr, const float Yr, const float Zr, int x, int y, int z) {
        return y * cos(Xr) * cos(Zr) + z * sin(Xr) * cos(Zr) -
            y * sin(Xr) * sin(Yr) * sin(Zr) + z * cos(Xr) * sin(Yr) * sin(Zr) -
            x * cos(Yr) * sin(Zr);
    }

    float getZ(const float Xr, const float Yr, const float Zr, int x, int y, int z) {
        return z * cos(Xr) * cos(Yr) - y * sin(Xr) * cos(Yr) + x * sin(Yr);
    }
};

