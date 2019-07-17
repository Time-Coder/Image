#ifndef PLOT_H
#define PLOT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "color.h"
#include "util.h"
#include "image.h"
#include "matrix.h"
#include "transform.h"

using namespace std;

class Shader
{
private:
	unsigned int _program = 0;

public:
	Shader(){}
	Shader(const char* vertex_source_filename, const char* fragment_source_filename);
	void load(const char* vertex_source_filename, const char* fragment_source_filename);
	void use();
	unsigned int program();

	void set(const string& name, int value);
	void set(const string& name, bool value);
	void set(const string& name, float value);
	void set(const string& name, unsigned int value);
	void set(const string& name, const Matrix<float>& mat);
};
class Image;
class ImageFrame
{
private:
	Image* image;
	Matrix<float> vertices;
	Matrix<unsigned int> indices;

private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;

private:
	int index(int i, int j);
	void set_vertices();
	void set_indices();

public:
	ImageFrame(){};
	virtual ~ImageFrame(){};
	void load(Image* image);
	void show();
	int width();
	int height();
	void free_gl();
};

class Window
{
private:
	thread th;

private:
	class Callbacks
	{
	public:
	    Callbacks() = delete;
        Callbacks(const Callbacks&) = delete;
        Callbacks(Callbacks&&) = delete;
        ~Callbacks() = delete;

        static void set_father(Window* fig);
        static void change_size_callback(GLFWwindow* window, int width, int height);
        static void cursor_position_callback(GLFWwindow* window, double x_current, double y_current);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double x, double y);
		static void focus_callback(GLFWwindow* window, int focused);

    private:
        static Window* father;
	};

private:
	GLFWwindow* _window = nullptr;
	int _width;
	int _height;
	int screen_width;
	int screen_height;
	string _name;
	Color _color;

	Shader shader;
	ImageFrame frame;

private:
	Matrix<float> projection_mat;
	Matrix<float> screen_mat;

	Matrix<float> transformation_mat;
	bool transformation_changed = true;

	enum MouseButton {NOTHING, LEFT, RIGHT, MIDDLE};
	MouseButton mouse_button = NOTHING;
	clock_t middle_click_time = -400;

	bool first_click = true;

	float x_last = 0.0;
	float y_last = 0.0;

	float drag_sensitive = 1.0f;
	float scroll_sensitive = 1.0f;

	Image* father_image;

private:
	void change_size_callback(int width, int height);
    void cursor_position_callback(double x_current, double y_current);
	void mouse_button_callback(int button, int action);
	void scroll_callback(double distance);
	void set_callbacks();
	void update();
	void update_transformation();
	void set_projection();

public:
	Window(Image* image);
	virtual ~Window(){}

	GLFWwindow* window();

	void load(Image* image);
	void wait();
	void show();
};

#endif