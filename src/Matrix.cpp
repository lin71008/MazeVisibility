#include <stdexcept>
#include <cstdarg>
#include <iostream>
#include <math.h> 

#include "Matrix.h"

Vector4f::
Vector4f(void)
{
    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 0.0f;
}

Vector4f::
Vector4f(const Vector4f &v0)
{
    data[0] = v0.data[0];
    data[1] = v0.data[1];
    data[2] = v0.data[2];
    data[3] = v0.data[3];
}

Vector4f::
Vector4f(const float f[])
{
	data[0] = f[0];
	data[1] = f[1];
	data[2] = f[2];
	data[3] = f[3];
}

Vector4f::
Vector4f(const float x, const float y, const float z)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = 0.0f;
}

Vector4f::
Vector4f(const float x, const float y, const float z, const float w)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}

Vector4f& Vector4f::
operator=(const Vector4f &v0)
{
    data[0] = v0.data[0];
    data[1] = v0.data[1];
    data[2] = v0.data[2];
    data[3] = v0.data[3];
    return *this;
}


float& Vector4f::
operator[](const int i)
{
    if (0 <= i && i < 4)
        return data[i];
    else
        throw std::range_error("index out of range.");
}

bool Vector4f::
operator==(const Vector4f &v0)
{
    double x = data[0] - v0.data[0];
    if (x > 1.0e-8)
        return false;
    double y = data[1] - v0.data[1];
    if (y > 1.0e-8)
        return false;
    double z = data[2] - v0.data[2];
    if (z > 1.0e-8)
        return false;
    double w = data[3] - v0.data[3];
    if (w > 1.0e-8)
        return false;

    return x * x + y * y + z * z + w * w < 1.0e-15;
}
        
bool Vector4f::
operator!=(const Vector4f &v0)
{
    double x = data[0] - v0.data[0];
    if (x > 1.0e-8)
        return true;
    double y = data[1] - v0.data[1];
    if (y > 1.0e-8)
        return true;
    double z = data[2] - v0.data[2];
    if (z > 1.0e-8)
        return true;
    double w = data[3] - v0.data[3];
    if (w > 1.0e-8)
        return true;

    return x * x + y * y + z * z + w * w >= 1.0e-15;
}

std::ostream&
operator<<(std::ostream &os, const Vector4f &v0)
{
    os << "(" << v0.data[0] << ", " << v0.data[1] << ", " << v0.data[2] << ", " << v0.data[3] << ")";
    return os;
}

Vector4f Vector4f::
operator+(const Vector4f &v0)
{
    Vector4f v1(data[0] + v0.data[0],
                data[1] + v0.data[1],
                data[2] + v0.data[2],
                data[3]);
    return v1;
}

Vector4f Vector4f::
operator-(const Vector4f &v0)
{
    Vector4f v1(data[0] - v0.data[0],
                data[1] - v0.data[1],
                data[2] - v0.data[2],
                data[3]);
    return v1;
}

Vector4f Vector4f::
operator*(const float &f)
{
    Vector4f v1(data[0] * f,
                data[1] * f,
                data[2] * f,
                data[3]);
    return v1;   
}

Vector4f Vector4f::
operator/(const float &f)
{
    Vector4f v1(data[0] / f,
                data[1] / f,
                data[2] / f,
                data[3]);
    return v1;   
}

const Vector4f Vector4f::ZERO = {0.0f, 0.0f, 0.0f, 0.0f};

float Vector4f::
operator*(const Vector4f &v0)
{
	return ( data[0] * v0.data[0]
	  	   + data[1] * v0.data[1]
	  	   + data[2] * v0.data[2] );
}

float Vector4f::
norm(void)
{
	return ( data[0] * data[0]
		   + data[1] * data[1]
		   + data[2] * data[2] );
}

Vector4f Vector4f::
cross(const Vector4f &v0)
{
    Vector4f v1(data[1] * v0.data[2] - data[2] * v0.data[1],
                data[2] * v0.data[0] - data[0] * v0.data[2],
                data[0] * v0.data[1] - data[1] * v0.data[0],
                data[3]);
    return v1;
}

Matrix44f::
Matrix44f(void)
{
    for (int i = 0; i < 16; ++i)
    {
        data[i] = 0.0f;
    }
}

Matrix44f::
Matrix44f(const int amt, ...)
{
    if (amt < 0 || amt > 16)
        throw std::range_error("amount must in range (1, 16)\n");

    va_list vl;
    va_start(vl, amt);

    for (int i = 0; i < amt; ++i)
        data[i] = va_arg(vl, double);

    for (int i = amt; i < 16; ++i)
        data[i] = 0.0f;

    va_end(vl);
}

Matrix44f::
Matrix44f(const Matrix44f &m0)
{
    for (int i = 0; i < 16; ++i)
        data[i] = m0.data[i];
}

Matrix44f::
Matrix44f(const Vector4f &v0)
{
	for (int i = 0; i < 4; ++i)
	{
		data[4 * i + 0] = ((Vector4f) v0)[i];
		data[4 * i + 1] =  0.0f;
		data[4 * i + 2] =  0.0f;
		data[4 * i + 3] =  0.0f;
	}
}

Matrix44f::
Matrix44f(const Vector4f &v0, const Vector4f &v1)
{
	for (int i = 0; i < 4; ++i)
	{
		data[4 * i + 0] = ((Vector4f) v0)[i];
		data[4 * i + 1] = ((Vector4f) v1)[i];
		data[4 * i + 2] =  0.0f;
		data[4 * i + 3] =  0.0f;
	}
}

Matrix44f::
Matrix44f(const Vector4f &v0, const Vector4f &v1, const Vector4f &v2)
{
	for (int i = 0; i < 4; ++i)
	{
		data[4 * i + 0] = ((Vector4f) v0)[i];
		data[4 * i + 1] = ((Vector4f) v1)[i];
		data[4 * i + 2] = ((Vector4f) v2)[i];
		data[4 * i + 3] =  0.0f;
	}
}

Matrix44f::
Matrix44f(const Vector4f &v0, const Vector4f &v1, const Vector4f &v2, const Vector4f &v3)
{
	for (int i = 0; i < 4; ++i)
	{
		data[4 * i + 0] = ((Vector4f) v0)[i];
		data[4 * i + 1] = ((Vector4f) v1)[i];
		data[4 * i + 2] = ((Vector4f) v2)[i];
		data[4 * i + 3] = ((Vector4f) v3)[i];
	}
}

Matrix44f& Matrix44f::
operator=(const Matrix44f &m0)
{
    for (int i = 0; i < 16; ++i)
        data[i] = m0.data[i];
    return *this;
}

float* Matrix44f::
operator[](const int i)
{
    if (0 <= i && i < 4)
        return &data[4 * i];
    else
        throw std::range_error("index out of range.");
}

bool Matrix44f::
operator==(const Matrix44f &m0)
{
	double de, e = 0.0;
	for (int i = 0; i < 16; ++i)
	{
		de = data[0] - m0.data[0];
		if (de > 1.0e-8)
			return false;
		e += de * de;
	}
	return e < 1.0e-15;
}
        
bool Matrix44f::
operator!=(const Matrix44f &m0)
{
	double de, e = 0.0;
	for (int i = 0; i < 16; ++i)
	{
		de = data[0] - m0.data[0];
		if (de > 1.0e-8)
			return true;
		e += de * de;
	}
	return e >= 1.0e-15;
}

std::ostream&
operator<<(std::ostream &os, const Matrix44f &m0)
{
    os << "[[" << m0.data[ 0] << ", " << m0.data[ 1] << ", " << m0.data[ 2] << ", " << m0.data[ 3] << "], ";
    os <<  "[" << m0.data[ 4] << ", " << m0.data[ 5] << ", " << m0.data[ 6] << ", " << m0.data[ 7] << "], ";
    os <<  "[" << m0.data[ 8] << ", " << m0.data[ 9] << ", " << m0.data[10] << ", " << m0.data[11] << "], ";
    os <<  "[" << m0.data[12] << ", " << m0.data[13] << ", " << m0.data[14] << ", " << m0.data[15] << "]]";
    return os;
}

Matrix44f Matrix44f::
operator+(const Matrix44f &m0)
{
	Matrix44f m1(Matrix44f::ZERO);
	for (int i = 0; i < 16; ++i)
	{
		m1.data[i] = data[i] + m0.data[i];
	}
	return m1;
}

Matrix44f Matrix44f::
operator-(const Matrix44f &m0)
{
	Matrix44f m1(Matrix44f::ZERO);
	for (int i = 0; i < 16; ++i)
	{
		m1.data[i] = data[i] - m0.data[i];
	}
	return m1;
}

Matrix44f Matrix44f::
operator*(const Matrix44f &m0)
{
	Matrix44f m1(Matrix44f::ZERO);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				m1[i][j] += data[4 * i + k] * m0.data[4 * k + j];
			}
		}
	}
	return m1;
}

Matrix44f Matrix44f::
operator*(const float &f)
{
	Matrix44f m0(Matrix44f::ZERO);
	for (int i = 0; i < 16; ++i)
	{
		m0.data[i] = data[i] * f;
	}
	return m0;
}

const Matrix44f Matrix44f::ZERO(0);

Matrix44f Matrix44f::
transpose(void)
{
	Matrix44f m0(*this);
	std::swap(m0.data[ 1], m0.data[ 4]);
	std::swap(m0.data[ 2], m0.data[ 8]);
	std::swap(m0.data[ 3], m0.data[12]);
	std::swap(m0.data[ 6], m0.data[ 9]);
	std::swap(m0.data[ 7], m0.data[13]);
	std::swap(m0.data[11], m0.data[14]);
	return m0;
}

float Matrix44f::
determinant(void)
{
	return ( data[0] * data[5] * data[10] * data[15]
		   - data[0] * data[5] * data[11] * data[14]
		   - data[0] * data[6] * data[ 9] * data[15]
		   + data[0] * data[6] * data[11] * data[13]
		   + data[0] * data[7] * data[ 9] * data[14]
		   - data[0] * data[7] * data[10] * data[13]
		   - data[1] * data[4] * data[10] * data[15]
		   + data[1] * data[4] * data[11] * data[14]
		   + data[1] * data[6] * data[ 8] * data[15]
		   - data[1] * data[6] * data[11] * data[12]
		   - data[1] * data[7] * data[ 8] * data[14]
		   + data[1] * data[7] * data[10] * data[12]
		   + data[2] * data[4] * data[ 9] * data[15]
		   - data[2] * data[4] * data[11] * data[13]
		   - data[2] * data[5] * data[ 8] * data[15]
		   + data[2] * data[5] * data[11] * data[12]
		   + data[2] * data[7] * data[ 8] * data[13]
		   - data[2] * data[7] * data[ 9] * data[12]
		   - data[3] * data[4] * data[ 9] * data[14]
		   + data[3] * data[4] * data[10] * data[13]
		   + data[3] * data[5] * data[ 8] * data[14]
		   - data[3] * data[5] * data[10] * data[12]
		   - data[3] * data[6] * data[ 8] * data[13]
		   + data[3] * data[6] * data[ 9] * data[12] );
}

Vector4f Matrix44f::
operator*(const Vector4f &v0)
{
	Matrix44f m0(v0);
	return ((*this) * m0).vec(0);
}

Vector4f Matrix44f::
vec(const int i)
{
    if (0 <= i && i < 4)
    {
		Vector4f v0(data[i + 0], data[i + 4], data[i + 8], data[i + 12]);
		return v0;
    }
    else
        throw std::range_error("index out of range.");
}
