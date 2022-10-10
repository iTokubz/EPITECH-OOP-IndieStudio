/*
** EPITECH PROJECT, 2022
** Game_test
** File description:
** Vector2D
*/

#include "Vector3D.hpp"

Vector3D::Vector3D()
{
    x = 0.0f;
    z = 0.0f;
    y = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
    this->x = x;
    this->z = z;
    this->y = y;
}

Vector3D &Vector3D::Add(const Vector3D &vec)
{
    this->x += vec.x;
    this->z += vec.z;

    return *this;
}

Vector3D &Vector3D::Substract(const Vector3D &vec)
{
    this->x -= vec.x;
    this->z -= vec.z;

    return *this;
}

Vector3D &Vector3D::Multiply(const Vector3D &vec)
{
    this->x *= vec.x;
    this->z *= vec.z;

    return *this;
}

Vector3D &Vector3D::Divide(const Vector3D &vec)
{
    this->x /= vec.x;
    this->z /= vec.z;

    return *this;
}

Vector3D &operator+(Vector3D &v1, const Vector3D &v2)
{
    return v1.Add(v2);
}

Vector3D &operator-(Vector3D &v1, const Vector3D &v2)
{
    return v1.Substract(v2);
}

Vector3D &operator*(Vector3D &v1, const Vector3D &v2)
{
    return v1.Multiply(v2);
}

Vector3D &operator/(Vector3D &v1, const Vector3D &v2)
{
    return v1.Divide(v2);
}

Vector3D &Vector3D::operator+=(const Vector3D &vec)
{
    return this->Add(vec);
}

Vector3D &Vector3D::operator-=(const Vector3D &vec)
{
    return this->Substract(vec);
}

Vector3D &Vector3D::operator*=(const Vector3D &vec)
{
    return this->Multiply(vec);
}

Vector3D &Vector3D::operator/=(const Vector3D &vec)
{
    return this->Divide(vec);
}

Vector3D &Vector3D::operator*(const int &i)
{
    this->x *= i;
    this->z *= i;

    return *this;
}

Vector3D &Vector3D::Zero()
{
    this->x = 0;
    this->z = 0;

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Vector3D &vec)
{
    stream << "(" << vec.x << "," << vec.z << ")";
    return stream;
}