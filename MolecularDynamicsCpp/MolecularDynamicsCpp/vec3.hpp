#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

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

	friend Vec3 operator*(double scalar, const Vec3& vector) 
	{
		return Vec3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
	}

	Vec3 operator*(const Vec3& other) const {
		return Vec3(x * other.x, y * other.y, z * other.z);
	}

	Vec3 pow(double scalar) const {
		return Vec3(std::pow(x, scalar), std::pow(y, scalar), std::pow(z, scalar));
	}

	Vec3 operator/(double scalar) const {
		return Vec3(x / scalar, y / scalar, z / scalar);
	}

	friend Vec3 operator/(double scalar, const Vec3& vector)
	{
		return Vec3(vector.x / scalar, vector.y / scalar, vector.z / scalar);
	}

	Vec3 operator/(const Vec3& other) const {
		return Vec3(x / other.x, y / other.y, z / other.z);
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

	double magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	double magnitudeSquared() const {
		return x * x + y * y + z * z;
	}

	Vec3 normalized() const {
		double len = magnitude();
		return Vec3(x / len, y / len, z / len);
	}

	std::string toString() const {
		std::stringstream ss;
		ss << "(" << x << "," << y << "," << z << ")";
		return ss.str();
	}

	void print() {
		std::cout << "(" << x << "," << y << "," << z << ")";
	}
};

#endif