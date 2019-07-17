#ifndef MATRIX_H
#define MATRIX_H

#define PI 3.1415926535f
#define AUTO -1

#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

template<class DataType = float>
class Matrix
{
public:
	class Shadow
	{
    private:
		int n_rows;
		int n_cols;
		DataType* _data;
		int i;

	public:
		Shadow(int rows, int cols, DataType* init_data, int _i) :
        n_rows(rows), n_cols(cols), _data(init_data), i(_i) {}

		DataType& operator [](int j)
		{
			if(j < 0 || j >= n_cols)
			{
				cout << "Error using Matrix<DataType>[i][j]:" << endl
					 << "j is out of bande [0, cols-1]!" << endl;
				exit(-1);
			}
			return _data[i + j * n_rows];
		}
		DataType operator [](int j)const
		{
			if(j < 0 || j >= n_cols)
			{
				cout << "Error using Matrix<DataType>[i][j]:" << endl
					 << "j is out of bande [0, cols-1]!" << endl;
				exit(-1);
			}
			return _data[i + j * n_rows];
		}
	};

private:
	static string cout2string(const DataType& element);
	static string multi_space(int n);
	static bool isZero(double a, double epsilon = 1E-6);
	void swap_row(int row1, int row2);
	void divide_row(int row, const DataType& k);
	void add_row(int row1, const DataType& k, int row2);

public:
	static int sign(float a);

protected:
	int n_rows = 0;
	int n_cols = 0;
	int _size = 0;
	DataType *_data = NULL;

public:
	Matrix(){}
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, const DataType& value);
	Matrix(int rows, int cols, const DataType* values);
	Matrix(const Matrix<DataType>& A);

	template<class ElemType>
	Matrix(const Matrix<ElemType>& A);

	Matrix(Matrix<DataType>&& A);
	Matrix(const vector<DataType>& x);
	Matrix(const vector< vector<DataType> >& X);
	Matrix(const initializer_list<DataType>& x);
	Matrix(const initializer_list< initializer_list<DataType> >& X);
    Matrix(const initializer_list< Matrix<DataType> >& X);
//    Matrix(const initializer_list< initializer_list< Matrix<DataType> > >& X);
	Matrix(const DataType& x);
	~Matrix();

	void clear();
	bool empty()const;
	int rows()const;
	int cols()const;
	int size()const;
	DataType* data()const;

	int rank()const;
	DataType trace()const;
	DataType det()const;
	DataType max()const;
	DataType min()const;
    void print_size()const;

	Matrix<DataType> t()const;
	Matrix<DataType> inv()const;
	Matrix<DataType>& reshape(int m, int n);
	Matrix<DataType> repmat(int m, int n)const;
	Matrix<DataType> repelem(int m, int n)const;

	Matrix<DataType>& operator =(const Matrix<DataType>& A);
	Matrix<DataType>& operator =(Matrix<DataType>&& A);

	template<class ElemType>
    Matrix<DataType>& operator =(const Matrix<ElemType>& A);

	template<class ElemType>
	operator Matrix<ElemType>()const;

	Shadow operator [](int i);
	Shadow operator [](int i)const;
    DataType& operator ()(int i);
    DataType operator ()(int i)const;
    DataType& operator ()(int i, int j);
    DataType operator ()(int i, int j)const;

	Matrix<DataType>  operator -()const;

	Matrix<DataType>& operator +=(const Matrix<DataType>& A);
	Matrix<DataType>& operator -=(const Matrix<DataType>& A);
	Matrix<DataType>& operator *=(const Matrix<DataType>& A); // 右乘
	Matrix<DataType>& operator %=(const Matrix<DataType>& A);
	Matrix<DataType>& operator /=(const Matrix<DataType>& A);
	Matrix<DataType>& operator ^=(const Matrix<DataType>& A);

	Matrix<DataType>& operator +=(const DataType& a);
	Matrix<DataType>& operator -=(const DataType& a);
	Matrix<DataType>& operator *=(const DataType& a);
	Matrix<DataType>& operator /=(const DataType& a);
	Matrix<DataType>& operator ^=(const DataType& a);

	template<class ElemType>
	friend ostream& operator <<(ostream& o, Matrix<ElemType> A);

	template<class ElemType>
	Matrix<ElemType> friend operator +(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator -(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator *(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator %(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator /(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator ^(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator +(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator -(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator *(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator %(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator /(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator ^(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<ElemType> friend operator +(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator -(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator *(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator %(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator /(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<ElemType> friend operator ^(const ElemType& a, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator >(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator <(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator >=(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator <=(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator ==(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>
	Matrix<bool> friend operator !=(const Matrix<ElemType>& A, const Matrix<ElemType>& B);

	template<class ElemType>

	Matrix<bool> friend operator >(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator <(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator >=(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator <=(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator ==(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator !=(const Matrix<ElemType>& A, const ElemType& b);

	template<class ElemType>
	Matrix<bool> friend operator >(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator <(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator >=(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator <=(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator ==(const ElemType& b, const Matrix<ElemType>& A);

	template<class ElemType>
	Matrix<bool> friend operator !=(const ElemType& b, const Matrix<ElemType>& A);

	friend Matrix<float> to(float start, float step, float end);

    template<class ElemType>
    friend Matrix<float> ones(const Matrix<ElemType>& A);

    template<class ElemType>
    friend Matrix<float> eye(const Matrix<ElemType>& A);

	friend Matrix<float> eye(int rows, int cols);
	friend Matrix<float> rand(int rows, int cols);

    template<class ElemType>
    friend Matrix<float> rand(const Matrix<ElemType>& A);

	friend float norm(const Matrix<float>& v);
	friend float dot(const Matrix<float>& v1, const Matrix<float>& v2);
	friend Matrix<float> cross(const Matrix<float>& v1, const Matrix<float>& v2);
	friend Matrix<float>& normalize(Matrix<float>& A);
    friend Matrix<float> normalize(const Matrix<float>& A);
	friend Matrix<float> sin(const Matrix<float>& A);
	friend Matrix<float> cos(const Matrix<float>& A);
	friend Matrix<float> tan(const Matrix<float>& A);
	friend Matrix<float> asin(const Matrix<float>& A);
	friend Matrix<float> acos(const Matrix<float>& A);
	friend Matrix<float> atan(const Matrix<float>& A);
	friend Matrix<float> atan2(const Matrix<float>& Y, const Matrix<float>& X);
	friend Matrix<float> sinh(const Matrix<float>& A);
	friend Matrix<float> cosh(const Matrix<float>& A);
	friend Matrix<float> tanh(const Matrix<float>& A);
	friend Matrix<float> asinh(const Matrix<float>& A);
	friend Matrix<float> acosh(const Matrix<float>& A);
	friend Matrix<float> atanh(const Matrix<float>& A);
	friend Matrix<float> exp(const Matrix<float>& A);
	friend Matrix<float> log(const Matrix<float>& A);
	friend Matrix<float> log2(const Matrix<float>& A);
	friend Matrix<float> log10(const Matrix<float>& A);
	friend Matrix<float> abs(const Matrix<float>& A);
	friend Matrix<int> floor(const Matrix<float>& A);
	friend Matrix<int> ceil(const Matrix<float>& A);
	friend Matrix<int> round(const Matrix<float>& A);
	friend Matrix<float> linspace(float start, float end, int n);
	friend Matrix<float> inv(Matrix<float> A);
	friend Matrix<float> pow(const Matrix<float>& A, double n);

    template<class ElemData>
    friend void meshgrid(Matrix<ElemData>& x, Matrix<ElemData>& y);
};


Matrix<float> to(float start, float end);
Matrix<float> zeros(int rows, int cols);
Matrix<float> zeros(int n);

template<class DataType>
Matrix<float> zeros_like(const Matrix<DataType>& A)
{
    return Matrix<float>(A.rows(), A.cols(), 0.0f);
}

Matrix<float> ones(int rows, int cols);
Matrix<float> ones(int n);

template<class DataType>
Matrix<float> ones(const Matrix<DataType>& A);
Matrix<float> eye(int n);

template<class DataType>
Matrix<float> eye(const Matrix<DataType>& A);

Matrix<float> rand(int rows, int cols);
Matrix<float> rand(int n);

template<class DataType>
Matrix<float> rand(const Matrix<DataType>& A);
Matrix<float> randn(int n);

template<class DataType>
Matrix<float> randn(const Matrix<DataType>& A);

template<class DataType>
Matrix<DataType> reshape(const Matrix<DataType>& A, int m, int n);

template<class DataType>
Matrix<DataType> repmat(const Matrix<DataType>& A, int m, int n);

template<class DataType>
Matrix<DataType> repelem(const Matrix<DataType>& A, int m, int n);

template<class DataType>
bool same_size(const Matrix<DataType>& A, const Matrix<DataType>& B);

Matrix<float> linspace(float start, float end, int n = 100);
Matrix<float> sphere2xyz(const Matrix<float>& sphere_coord);

Matrix<float>& normalize(Matrix<float>& A);
float deg2rad(float alpha);

template<class DataType>
Matrix<DataType> interp1(const Matrix<float>& x, const Matrix<float>& v, const Matrix<float>& xi);

template<class DataType>
Matrix<DataType> interp2(const Matrix<float>& x, const Matrix<float>& y, const Matrix<DataType>& v,
						  const Matrix<float>& xi, const Matrix<float>& yi);

#ifndef MATRIX_TEMPLATE_IMPLEMENT
#define MATRIX_TEMPLATE_IMPLEMENT
#include "matrix.cpp"
#endif
#endif
