#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace rotations {

    /**
     * Rotates a X coordinate of the 3D point .
     *
     * @param Xr Rotation angle around the X-axis (in radians).
     * @param Yr Rotation angle around the Y-axis (in radians).
     * @param Zr Rotation angle around the Z-axis (in radians).
     * @param X-coordinate of the 3D point.
     * @param Y-coordinate of the 3D point.
     * @param Z-coordinate of the 3D point.
     * @returns Rotated X coordinate of the 3D point.
     */
    float getX(const float Xr, const float Yr, const float Zr, int x, int y, int z);

    /**
     * Rotates a Y coordinate of the 3D point .
     *
     * @param Xr Rotation angle around the X-axis (in radians).
     * @param Yr Rotation angle around the Y-axis (in radians).
     * @param Zr Rotation angle around the Z-axis (in radians).
     * @param X-coordinate of the 3D point.
     * @param Y-coordinate of the 3D point.
     * @param Z-coordinate of the 3D point.
     * @returns Rotated Y coordinate of the 3D point.
     */
    float getY(const float Xr, const float Yr, const float Zr, int x, int y, int z);

    /**
     * Rotates a Z coordinate of the 3D point .
     *
     * @param Xr Rotation angle around the X-axis (in radians).
     * @param Yr Rotation angle around the Y-axis (in radians).
     * @param Zr Rotation angle around the Z-axis (in radians).
     * @param X-coordinate of the 3D point.
     * @param Y-coordinate of the 3D point.
     * @param Z-coordinate of the 3D point.
     * @returns Rotated Z coordinate of the 3D point.
     */
    float getZ(const float Xr, const float Yr, const float Zr, int x, int y, int z);
};

#endif // !GEOMETRY_H
