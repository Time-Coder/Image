#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"

float angle(const Matrix<float>& v1, const Matrix<float>& v2);

Matrix<float> Rx(float phi);
Matrix<float> Ry(float theta);
Matrix<float> Rz(float psi);
Matrix<float> rotation(const Matrix<float>& v1, const Matrix<float>& v2);
Matrix<float> rotation(float phi, float theta, float psi);
Matrix<float> rotation(Matrix<float> axis, float theta);
Matrix<float> translation(const Matrix<float>& delta);
void translate(Matrix<float>& mat, const Matrix<float>& vec);
Matrix<float> scale(float s);
void scale(Matrix<float>& mat, float s);
Matrix<float> view(float AZ, float EL, float r = 2*sqrt(3));
Matrix<float> view(const Matrix<float>& sphere_position);
Matrix<float> view(const Matrix<float>& position, const Matrix<float>& point, float psi0 = 0.0f);
Matrix<float> projection(float alpha, float s, float z1, float z2);

#endif