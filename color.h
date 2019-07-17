#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "matrix.h"

struct Color
{
	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;
	float A = 1.0f;

private:
	void correct();

public:
	Color(){}
	Color(int r, int g, int b, float a = 1.0f);
	Color(float r, float g, float b, float a = 1.0f);
	Color(double r, double g, double b, double a = 1.0);
	Color(const char* name);
	Color(string name);
	Color(char name);

	Color friend operator +(const Color& c1, const Color& c2);
	Color friend operator -(const Color& c1, const Color& c2);
	Color friend operator *(const Color& c1, const Color& c2);
	Color friend operator /(const Color& c1, const Color& c2);
	
	Color friend operator +(float k, const Color& c2);
	Color friend operator -(float k, const Color& c2);
	Color friend operator *(float k, const Color& c2);
	Color friend operator /(float k, const Color& c2);

	Color friend operator +(const Color& c1, float k);
	Color friend operator -(const Color& c1, float k);
	Color friend operator *(const Color& c1, float k);
	Color friend operator /(const Color& c1, float k);

	Color operator -();
};

class ColorMap
{
private:
	float min_value = 0;
	float max_value = 0;

	int n_colors = 0;
	Color *colors = NULL;

	int n_colors_land = 0;
	Color *colors_land = NULL;

	int n_colors_sea = 0;
	Color *colors_sea = NULL;

	bool is_dem = false;

public:
	ColorMap(){}
	ColorMap(float min, float max) : min_value(min), max_value(max) {}
	~ColorMap(){}
	void jet(int n);
	void parula(int n);
	void sea(int n);
	void demcmap(int n);
	Color getColor(float value);
	Matrix<Color> getColor(const Matrix<float>& V);
	void set_min(float min);
	void set_max(float max);
	void set_minmax(float min, float max);
};

void splitRGBA(const Matrix<Color>& C, Matrix<float>& R, Matrix<float>& G, Matrix<float>& B, Matrix<float>& A);

#endif