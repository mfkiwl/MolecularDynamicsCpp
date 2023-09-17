#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>

class Vec3
{
public:
	double x, y, z;

	Vec3() : x(0.0), y(0.0), z(0.0) {}

	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

	Vec3& operator=(const Vec3& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	bool operator==(const Vec3& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator!=(const Vec3& other) const {
		return !(*this == other);
	}

	Vec3 operator+(const Vec3& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	Vec3 operator-(const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	Vec3 operator*(double scalar) const {
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

	Vec3 operator/(double scalar) const {
		return Vec3(x / scalar, y / scalar, z / scalar);
	}

	Vec3& operator+=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& operator-=(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& operator*=(double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vec3& operator/=(double scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	double dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	Vec3 cross(const Vec3& other) const {
		return Vec3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	double length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vec3 normalized() const {
		double len = length();
		return Vec3(x / len, y / len, z / len);
	}

	friend Vec3 operator*(double scalar, const Vec3& vec)
	{
		return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	friend Vec3 operator/(double scalar, const Vec3& vec) {
		return Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
	}
};

#endif // !VEC3_HPP