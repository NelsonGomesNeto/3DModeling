#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
public:
    double x, y, z;

    Vector(double xx, double yy, double zz);

    void set(double xx, double yy, double zz);

    double magSquared();

    Vector* limit(int max);

    Vector* mult(double n);

    Vector* div(double n);

    void print();

    void rotateX(double angle);

    void rotateY(double angle);

    void operator+=(const Vector &a);

    void operator-=(const Vector &a);

    Vector* operator-(const Vector &a);

    Vector* operator+(const Vector &a);

    Vector *copy();

    Vector *cross(Vector *pVector);

    Vector *unit();
};

#endif
