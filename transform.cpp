#include "transform.h"

Matrix<float> Rx(float phi)
{
	return Matrix<float>({{1.0f,       0.0f,            0.0f,       0.0f},
						  {0.0f,  (float)cos(phi), (float)sin(phi), 0.0f},
						  {0.0f, -(float)sin(phi), (float)cos(phi), 0.0f},
						  {0.0f,       0.0f,            0.0f,       1.0f}});
}

Matrix<float> Ry(float theta)
{
	return Matrix<float>({{(float)cos(theta), 0.0f, -(float)sin(theta), 0.0f},
						  {      0.0f       , 1.0f,        0.0f       , 0.0f},
						  {(float)sin(theta), 0.0f,  (float)cos(theta), 0.0f},
						  {      0.0f       , 0.0f,        0.0f       , 1.0f}});
}

Matrix<float> Rz(float psi)
{
	return Matrix<float>({{ (float)cos(psi), (float)sin(psi), 0.0f, 0.0f},
						  {-(float)sin(psi), (float)cos(psi), 0.0f, 0.0f},
						  {      0.0f      ,       0.0f     , 1.0f, 0.0f},
						  {      0.0f      ,       0.0f     , 0.0f, 1.0f}});
}

float angle(const Matrix<float>& v1, const Matrix<float>& v2)
{
    return acos(dot(v1, v2) / (norm(v1) * norm(v2)));
}

Matrix<float> rotation(const Matrix<float>& v1, const Matrix<float>& v2)
{
    Matrix<float> c = cross(v1, v2);
    if(norm(c)>=1E-6)
        return rotation(c, angle(v1, v2));
    else
        return eye(4);
}

Matrix<float> rotation(float phi, float theta, float psi)
{
	return Rz(-psi) * Ry(-theta) * Rx(-phi);
}

Matrix<float> rotation(Matrix<float> axis, float theta)
{
	normalize(axis);
    Matrix<float> temp = (1-cos(theta)) * (axis * axis.t()) + cos(theta) * eye(3) + sin(theta) * crossmat(axis);
    Matrix<float> R(4, 4, 0.0f);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			R(i, j) = temp(i, j);
		}
	}
	R(3, 3) = 1.0f;

	return R;
}

Matrix<float> translation(const Matrix<float>& delta)
{
	Matrix<float> T = eye(4);
	T(0, 3) = delta(0);
	T(1, 3) = delta(1);
	T(2, 3) = delta(2);

	return T;
}

void translate(Matrix<float>& mat, const Matrix<float>& vec)
{
	mat(0, 3) += vec(0);
	mat(1, 3) += vec(1);
	mat(2, 3) += vec(2);
}

Matrix<float> scale(float s)
{
	Matrix<float> S = eye(4);
	S(0, 0) = s;
	S(1, 1) = s;
	S(2, 2) = s;

	return S;
}

void scale(Matrix<float>& mat, float s)
{
	mat(0, 0) *= s;
	mat(1, 1) *= s;
	mat(2, 2) *= s;
}

Matrix<float> scale(float sx, float sy, float sz)
{
	Matrix<float> S = eye(4);
	S(0, 0) = sx;
	S(1, 1) = sy;
	S(2, 2) = sz;

	return S;
}

Matrix<float> sphere2xyz(const Matrix<float>& sphere_coord)
{
	float r = sphere_coord(0);
	float theta = sphere_coord(1);
	float phi = sphere_coord(2);

	Matrix<float> xyz_coord(3, 1);
	float rxy = r * cos(phi);
	xyz_coord(0) = rxy * cos(theta);
	xyz_coord(1) = rxy * sin(theta);
	xyz_coord(2) = r * sin(phi);

	return xyz_coord;
}

Matrix<float> view(float AZ, float EL, float r)
{
	AZ = deg2rad(AZ);
	EL = deg2rad(EL);
	float psi = 0.5f * PI + AZ;
	float phi = 0.5f * PI - EL;

	return Rx(phi) * Rz(psi) * translation(-sphere2xyz({r, AZ, EL}));
}

Matrix<float> view(const Matrix<float>& sphere_position)
{
    float psi = 0.5f * PI + sphere_position(1);
    float phi = 0.5f * PI - sphere_position(2);

	Matrix<float> R = Rx(phi) * Rz(psi);

	return R * translation(-sphere2xyz(sphere_position));
}

Matrix<float> view(const Matrix<float>& position, const Matrix<float>& point, float psi0)
{
	Matrix<float> direction = point - position;

	float rx = direction(0);
	float ry = direction(1);
	float rz = direction(2);

	float r2 = rx*rx+ry*ry;
	float psi = r2 > 1E-6 ? -Matrix<float>::sign(rx) * acos(ry/sqrt(r2)) : 0.0f;
	r2 = rx*rx + ry*ry + rz*rz;
	float phi = r2 > 1E-6 ? 0.5f * PI + asin(rz/sqrt(r2)) : 0.0f;

	Matrix<float> R = Rz(-psi0) * Rx(phi) * Rz(psi);

	return R * translation(-position);
}

Matrix<float> projection(float alpha, float s, float z1, float z2)
{
	float t = 1.0f / tan(0.5f * alpha);
	float l = z2 - z1;
	return Matrix<float>({{t/s ,   0.0f,      0.0f   ,        0.0f    },
						  {0.0f,     t ,      0.0f   ,        0.0f    },
						  {0.0f,   0.0f,   -(z1+z2)/l,   -2.0f*z1*z2/l},
						  {0.0f,   0.0f,     -1.0f   ,        0.0f    }});
}