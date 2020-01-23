#pragma once
#include "main.hpp"

struct Vector;
Vector operator+(const Vector & lhs, const Vector & rhs);
Vector operator-(const Vector & lhs, const Vector & rhs);
Vector operator/(const Vector & lhs, const Vector & rhs);
Vector operator*(const Vector & lhs, const Vector & rhs);
Vector operator+(const Vector & lhs, const float & rhs);
Vector operator-(const Vector & lhs, const float & rhs);
Vector operator/(const Vector & lhs, const float & rhs);
Vector operator*(const Vector & lhs, const float & rhs);
Vector operator-(const Vector &lhs);
Vector operator+(const Vector &lhs);

double radianToAngle(double radian);

double angleToRadian(double angle);

struct Vector
{
	Vector();
	Vector(float x, float y);
	Vector(float angle, bool, bool);
	Vector(Vector const & rhs);
	virtual ~Vector();
	float	length() const;
	float	distanceTo(Vector const & rhs) const;
	float 	angleVector(Vector const & rhs) const;
	float	scalarProduct(Vector const & rhs) const;
	Vector &operator=(const Vector & rhs);
	Vector &operator+=(const Vector & rhs);
	Vector &operator-=(const Vector & rhs);
	Vector &operator/=(const Vector & rhs);
	Vector &operator*=(const Vector & rhs);
	Vector  normalization();
	
	static Vector	abs(Vector );
	
	float		x;
	float		y;
};

std::ostream &operator<<(std::ostream &os, Vector const &v);