#include <iostream>
#include <math.h>

#include "Matrix.h"

using namespace std;

int main(int argc, char const *argv[])
{

// Vector4f
	Vector4f X(1.f, 0.f, 0.f, 1.f);
	Vector4f Y(0.f, 1.f, 0.f, 1.f);
	Vector4f Z(0.f, 0.f, 1.f, 1.f);
	Vector4f W(0.f, 0.f, 0.f, 1.f);

	cout << "X: " << X << endl;
	cout << "Y: " << Y << endl;
	cout << "Z: " << Z << endl;
	cout << "W: " << W << endl;

	cout << "X x Y: " << X.cross(Y) << endl;
	cout << "Y x Z: " << Y.cross(Z) << endl;
	cout << "Z x X: " << Z.cross(X) << endl;

	Vector4f A, B, C;
	cout << "A = X + 2Y: " << (A = X + Y * 2) << endl;
	cout << "B = Z - 2Y: " << (B = Z - Y * 2) << endl;
	cout << "C = (X + Z) / 2: " << (C = (X + Y) / 2) << endl;

	cout << "A * A: " << A * A << endl;
	cout << "A * B: " << A * B << endl;

	cout << "|C|^2: " << C.norm() << endl;

// Matrix44f
	Matrix44f N, M(A, B, Z, W);

	cout << "M = (A, B, Z, W): " << M << endl;
	cout << "N = transpose(M): " << (N = M.tr()) << endl;

	cout << "M + N: " << M + N << endl;
	cout << "M - N: " << M - N << endl;

	cout << "2 * M: " << M * 2 << endl;

	cout << "N * M: " << M * N << endl;
	cout << "determinant(M): " << M.det() << endl;

	return 0;
}
