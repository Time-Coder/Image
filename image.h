#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <tiffio.h>
#include "plot.h"
#include "color.h"

using namespace std;
class Window;
class Image
{
public:
	class ColorRef
	{
	private:
		class Component
		{
			unsigned char* ptr = nullptr;
			bool first = true;
		public:
			Component(){}
			Component(unsigned char& value);
			unsigned char operator =(unsigned char& value);
			float operator =(const float& value);
			Component& operator =(const Component& component);
			operator float();
		};

	public:
		Component R;
		Component G;
		Component B;
		Component A;

		ColorRef(){}
		ColorRef(Color& color);
		ColorRef& operator =(const Color& color);
		ColorRef& operator =(const ColorRef& cr);
		operator Color();
	};

private:
	unsigned char* _data = nullptr;
	int n_rows = 0;
	int n_cols = 0;
	int n_channels = 0;

	unsigned char trash = 255;
	string _name;

	void read_tiff(const string& filename);

public:
	int window_array_index = -1;

public:
	Image() : _name("Memory Image") {}
	Image(int rows, int cols, int channels = 3, const string& Name = "Memory Image");
	Image(const string& filename);
	Image(const Image& image);
	Image(Image&& image);
	virtual ~Image();

	Image& operator =(const Image& image);
	Image& operator =(Image&& image);

	unsigned char& operator ()(int i, int j, int channel);
	unsigned char  operator ()(int i, int j, int channel)const;
	ColorRef operator ()(int i, int j);
	Color operator ()(int i, int j)const;
	operator GLFWimage ();

	void read(const string& filename);
	void write(const string& filename);
	void show();
	void wait();

	unsigned char* data();
	int width()const;
	int height()const;
	int rows()const;
	int cols()const;
	int channels()const;
	int size()const;
	string name()const;

	Image flip_y()const;
	Image flip_x()const;
	Image flip_xy()const;

	void splitRGBA(Matrix<float>& R, Matrix<float>& G, Matrix<float>& B, Matrix<float>& A);
};

extern vector< unique_ptr<Window> > __window_array;
void __wait_rest_images();

#endif