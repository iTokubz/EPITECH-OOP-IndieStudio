/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** Velocity3D
*/

#ifndef VELOCITY3D_HPP_
#define VELOCITY3D_HPP_

#include <iostream>

class Vector3D {
    public:
        float x;
        float z;
        float y;

        Vector3D();
        Vector3D(float x, float y, float z);

        Vector3D &Add(const Vector3D &vec);
        Vector3D &Substract(const Vector3D &vec);
        Vector3D &Multiply(const Vector3D &vec);
        Vector3D &Divide(const Vector3D &vec);

        friend Vector3D &operator+(Vector3D &v1, const Vector3D &v2);
        friend Vector3D &operator-(Vector3D &v1, const Vector3D &v2);
        friend Vector3D &operator*(Vector3D &v1, const Vector3D &v2);
        friend Vector3D &operator/(Vector3D &v1, const Vector3D &v2);

        Vector3D &operator+=(const Vector3D &vec);
        Vector3D &operator-=(const Vector3D &vec);
        Vector3D &operator*=(const Vector3D &vec);
        Vector3D &operator/=(const Vector3D &vec);

        Vector3D &operator*(const int &i);
        Vector3D &Zero();

        friend std::ostream &operator<<(std::ostream &stream, const Vector3D &vec);
};

#endif /* !VELOCITY3D_HPP_ */
