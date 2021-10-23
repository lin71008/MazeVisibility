#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <cstdarg>


/* Matrix 4 x 4, float
 * v -> 0  1  2  3
 *   +------------
 * 0 |  0  1  2  3
 * 1 |  4  5  6  7
 * 2 |  8  9 10 11
 * 3 | 12 13 14 15
*/

class Vector4f
{
    public:        

        Vector4f(void);
        Vector4f(const Vector4f &v0);

    public:

        Vector4f(const float[]);
        Vector4f(const float, const float, const float);
        Vector4f(const float, const float, const float, const float);
        Vector4f& operator=(const Vector4f &v0);

    public:

        float& operator[](const int i);
        bool operator==(const Vector4f &v0);
        bool operator!=(const Vector4f &v0);

        friend std::ostream& operator<<(std::ostream &os, const Vector4f &v0);

    public:

        Vector4f operator+(const Vector4f &v0);
        Vector4f operator-(const Vector4f &v0);
        Vector4f operator*(const float &f);
        Vector4f operator/(const float &f);

        static const Vector4f ZERO;

    public:

        float operator*(const Vector4f &v0);
        float norm(void);

        Vector4f cross(const Vector4f &v0);

    private:

        float data[4];
};


class Matrix44f
{
    public:

        Matrix44f(void);
        Matrix44f(const int amt, ...);
        Matrix44f(const Matrix44f &m0);
    
    public:

        Matrix44f(const Vector4f &v0);
        Matrix44f(const Vector4f &v0, const Vector4f &v1);
        Matrix44f(const Vector4f &v0, const Vector4f &v1, const Vector4f &v2);
        Matrix44f(const Vector4f &v0, const Vector4f &v1, const Vector4f &v2, const Vector4f &v3);
        Matrix44f& operator=(const Matrix44f &m0);
   
    public:

        float* operator[](const int i);
        bool operator==(const Matrix44f &m0);
        bool operator!=(const Matrix44f &m0);

        friend std::ostream& operator<<(std::ostream &os, const Matrix44f &m0);

    public:

        Matrix44f operator+(const Matrix44f &m0);
        Matrix44f operator-(const Matrix44f &m0);
        Matrix44f operator*(const Matrix44f &m0);
        Matrix44f operator*(const float &f);

        static const Matrix44f ZERO;

    public:

        Matrix44f transpose(void);
        float determinant(void);

    public:

        Vector4f operator*(const Vector4f &v0);
        Vector4f vec(const int i);

    public:

        Matrix44f tr(void) { return this->transpose(); }
        float det(void) { return this->determinant(); }

    private:

        float data[16];
};

#endif
