#pragma once
#include "vector2.hpp"

struct Vector3D {
    float x, y, z;

    Vector3D() : x(0), y(0), z(0) {}

    Vector3D(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

    Vector3D Subtract(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D Add(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    float DotProduct(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float Magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float Magnitude2D() const {
        return std::sqrt(x * x + y * y);
    }

    float Distance(const Vector3D& other) const {
        Vector3D diff = Subtract(other);
        return diff.Magnitude();
    }

    bool IsZeroVector() {
        return x == 0 && y == 0 && z == 0;
    }

    bool IsValid() {
        if (std::isnan(x) || std::isinf(x) || std::isnan(y) || std::isinf(y) || std::isnan(z) || std::isinf(z)) {
            return false;
        }
        return true;
    }

    Vector3D& Normalize() {
        float len = Magnitude();
        if (len > 0) {
            x /= len;
            y /= len;
            z /= len;
        }
        return *this;
    }

    Vector3D Multiply(float scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector2D To2D() const {
        return Vector2D(x, y);
    }

    float Distance2D(const Vector3D& other) const {
        return (other.Subtract(*this)).Magnitude2D();
    };

    Vector3D& operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    bool operator==(const Vector3D& other) const {
        float epsilon = 1e-5;
        return (std::abs(x - other.x) < epsilon)
            && (std::abs(y - other.y) < epsilon)
            && (std::abs(z - other.z) < epsilon);
    }

    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }

    Vector3D ModifyZ(float zOffset) const {
        return Vector3D{ x, y, z + zOffset };
    }


    static Vector3D Transform(const Vector3D vector, const float matrix[4][4]) {
        Vector3D transformed;

        transformed.x = vector.y * matrix[0][1] + vector.x * matrix[0][0] + vector.z * matrix[0][2] + matrix[0][3];
        transformed.y = vector.y * matrix[1][1] + vector.x * matrix[1][0] + vector.z * matrix[1][2] + matrix[1][3];
        transformed.z = vector.y * matrix[3][1] + vector.x * matrix[3][0] + vector.z * matrix[3][2] + matrix[3][3];

        return transformed;
    }
};