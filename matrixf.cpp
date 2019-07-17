#include "matrix.h"

Matrix<float> to(float start, float step, float end)
{
    int n = int((end-start)/step);
	Matrix<float> x(1, n+1);
	
	x._data[0] = start;
	for(int i = 1; i < n; i++)
	{
		x._data[i] = x._data[i-1] + step;
	}
	x._data[n] = end;

	return x;
}

Matrix<float> to(float start, float end)
{
	return to(start, 1.0f, end);
}

Matrix<float> zeros(int rows, int cols)
{
	return Matrix<float>(rows, cols, 0.0f);
}

Matrix<float> zeros(int n)
{
	return Matrix<float>(n, n, 0.0f);
}

Matrix<float> ones(int rows, int cols)
{
	return Matrix<float>(rows, cols, 1.0f);
}

Matrix<float> ones(int n)
{
	return Matrix<float>(n, n, 1.0f);
}

Matrix<float> eye(int rows, int cols)
{
	Matrix<float> In(rows, cols, 0.0f);
    int n = rows < cols ? rows : cols;
    int k = rows + 1;
	for(int i = 0; i < n; i++)
	{
		In._data[i*k] = 1.0f;
	}

	return In;
}

Matrix<float> eye(int n)
{
	return eye(n, n);
}

Matrix<float> rand(int rows, int cols)
{
	Matrix<float> A(rows, cols);
	srand((unsigned)time(NULL));
	for(int i = 0; i < A._size; i++)
	{
		A._data[i] = rand() / float(RAND_MAX);
	}

	return A;
}

Matrix<float> rand(int n)
{
	return rand(n, n);
}

float norm(const Matrix<float>& v)
{
    return sqrt((v.t() * v)._data[0]);
}

float dot(const Matrix<float>& v1, const Matrix<float>& v2)
{
    return (v1.t() * v2)._data[0];
}

Matrix<float> cross(const Matrix<float>& v1, const Matrix<float>& v2)
{
    return Matrix<float>({v1._data[1]*v2._data[2]-v1._data[2]*v2._data[1],
                          v1._data[2]*v2._data[0]-v1._data[0]*v2._data[2],
                          v1._data[0]*v2._data[1]-v1._data[1]*v2._data[0]});
}

Matrix<float>& normalize(Matrix<float>& A)
{
	return A /= sqrt((A.t() * A)._data[0]);
}

Matrix<float> normalize(const Matrix<float>& A)
{
    return A/sqrt((A.t() * A)._data[0]);
}

Matrix<float> sin(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = sin(A._data[i]);
	}

	return B;
}

Matrix<float> cos(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = cos(A._data[i]);
	}

	return B;
}

Matrix<float> tan(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = tan(A._data[i]);
	}

	return B;
}

Matrix<float> asin(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = asin(A._data[i]);
	}

	return B;
}

Matrix<float> acos(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = acos(A._data[i]);
	}

	return B;
}

Matrix<float> atan(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = atan(A._data[i]);
	}

	return B;
}

Matrix<float> atan2(const Matrix<float>& Y, const Matrix<float>& X)
{
    if(!same_size(Y, X))
    {
        cout << "Error using atan2(Y, X)!" << endl
             << "Y and X must have the same size!" << endl;
        exit(-1);
    }

    Matrix<float> Z(Y.n_rows, Y.n_cols);
    for(int i = 0; i < Z._size; i++)
	{
        Z._data[i] = atan2(Y._data[i], X._data[i]);
	}

	return Z;
}

Matrix<float> sinh(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = sinh(A._data[i]);
	}

	return B;
}

Matrix<float> cosh(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = cosh(A._data[i]);
	}

	return B;
}

Matrix<float> tanh(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = tanh(A._data[i]);
	}

	return B;
}

Matrix<float> asinh(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = asinh(A._data[i]);
	}

	return B;
}

Matrix<float> acosh(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = acosh(A._data[i]);
	}

	return B;
}

Matrix<float> atanh(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = atanh(A._data[i]);
	}

	return B;
}

Matrix<float> exp(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = exp(A._data[i]);
	}

	return B;
}

Matrix<float> log(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = log(A._data[i]);
	}

	return B;
}

Matrix<float> log2(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = log2(A._data[i]);
	}

	return B;
}

Matrix<float> log10(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = log10(A._data[i]);
	}

	return B;
}

Matrix<float> abs(const Matrix<float>& A)
{
    Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = fabs(A._data[i]);
	}

	return B;
}

Matrix<int> floor(const Matrix<float>& A)
{
    Matrix<int> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = (int)floor(A._data[i]);
	}

	return B;
}

Matrix<int> ceil(const Matrix<float>& A)
{
    Matrix<int> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = (int)ceil(A._data[i]);
	}

	return B;
}

Matrix<int> round(const Matrix<float>& A)
{
    Matrix<int> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = (int)round(A._data[i]);
	}

	return B;
}

Matrix<float> pow(const Matrix<float>& A, double n)
{
	Matrix<float> B(A.n_rows, A.n_cols);
    for(int i = 0; i < B._size; i++)
	{
        B._data[i] = (float)pow(A._data[i], n);
	}

	return B;
}

Matrix<float> linspace(float start, float end, int n)
{
	Matrix<float> x(1, n);
	x._data[0] = start;
	x._data[n-1] = end;

	float delta = (end-start)/(n-1);
	for(int i = 1; i < n-1; i++)
	{
		x._data[i] = x._data[i-1] + delta;
	}

	return x;
}

float deg2rad(float alpha)
{
	return alpha / 180 * PI;
}

Matrix<float> inv(Matrix<float> A)
{
	if(A.rows() != A.cols())
	{
		cout << "Error using inv(A)!" << endl
			 << "A must be a square matrix!" << endl;
		exit(-1);
	}

	Matrix<float> B = eye(A);
	int n = A.rows();
	for(int i = 0; i < n; i++)
	{
		float main_value = A(i, i);
		int main_row = i;
		for(int subi = i+1; subi < n; subi++)
		{
			if(fabs(A(subi, i)) > fabs(main_value))
			{
				main_value = A(subi, i);
				main_row = subi;
			}
		}
		if(Matrix<float>::isZero(main_value))
		{
			cout << "Error in inv(A)!" << endl
				 << "Matrix A is cannot be inversed!" << endl;
			exit(-1);
		}

		A.swap_row(i, main_row);
		B.swap_row(i, main_row);

		A.divide_row(i, main_value);
		B.divide_row(i, main_value);

		A(i, i) = 1.0f; // float correction

		for(int subi = 0; subi < n; subi++)
		{
			if(subi != i)
			{
				B.add_row(i, -A(subi, i), subi);
				A.add_row(i, -A(subi, i), subi);
				A(subi, i) = 0.0f; // float correction
			}
		}
	}

	return B;
}