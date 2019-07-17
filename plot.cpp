#include "plot.h"
#include "util.h"

Window* Window::Callbacks::father = nullptr;

void Window::Callbacks::set_father(Window* fig)
{
	father = fig;
}

void Window::Callbacks::change_size_callback(GLFWwindow* window, int width, int height)
{
	father->change_size_callback(width, height);
}

void Window::Callbacks::cursor_position_callback(GLFWwindow* window, double x_current, double y_current)
{
	father->cursor_position_callback(x_current, y_current);
}

void Window::Callbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	father->mouse_button_callback(button, action);
}

void Window::Callbacks::scroll_callback(GLFWwindow* window, double x, double y)
{
	father->scroll_callback(y);
}

void Window::Callbacks::focus_callback(GLFWwindow* window, int focused)
{
	if(focused)
	{
		for(auto it = __window_array.begin(); it != __window_array.end(); it++)
		{
			if((*it)->window() == window)
			{
				Window::Callbacks::set_father((*it).get());
				break;
			}
		}
	}
}

GLFWwindow* Window::window()
{
	return _window;
}

void Window::set_callbacks()
{
	Window::Callbacks::set_father(this);
	glfwSetFramebufferSizeCallback(_window, Window::Callbacks::change_size_callback);
	glfwSetCursorPosCallback(_window, Window::Callbacks::cursor_position_callback);
    glfwSetMouseButtonCallback(_window, Window::Callbacks::mouse_button_callback);
    glfwSetScrollCallback(_window, Window::Callbacks::scroll_callback);
    glfwSetWindowFocusCallback(_window, Window::Callbacks::focus_callback);
}

void Window::change_size_callback(int width, int height)
{
	_width = width;
	_height = height;
	set_projection();
	transformation_changed = true;
	glViewport(0, 0, width, height);
}

void Window::cursor_position_callback(double x_current, double y_current)
{
	if(mouse_button == LEFT)
	{
		if(first_click)
		{
			first_click = false;
		}
		else
		{
			float dx = 2.0f*(x_current - x_last)/_width;
			float dy = 2.0f*(y_last - y_current)/_height;
			screen_mat = Matrix<float>({{1.0f, 0.0f, 0.0f, dx},
										{0.0f, 1.0f, 0.0f, dy},
										{0.0f, 0.0f, 0.0f, 0.0f},
										{0.0f, 0.0f, 0.0f, 1.0f}}) * screen_mat;
			transformation_changed = true;
		}
	}
	x_last = x_current;
	y_last = y_current;
}

void Window::mouse_button_callback(int button, int action)
{
	if(action == GLFW_PRESS)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouse_button = LEFT;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
        {
        	clock_t now = clock();
        	if(now-middle_click_time <= 500)
        	{
        		screen_mat = eye(4);
        		transformation_changed = true;
        	}
        	middle_click_time = now;
            mouse_button = MIDDLE;
            break;
        }
        default:
            break;
        }
    }
    else if(action ==  GLFW_RELEASE)
    {
        mouse_button = NOTHING;
        first_click = true;
    }
}

void Window::scroll_callback(double distance)
{
	float k = 1 + distance * scroll_sensitive * 0.1;
	float x0 = 2.0f*(x_last/_width)-1.0f;
	float y0 = 1.0f-2.0f*(y_last/_height);
	screen_mat = Matrix<float>({{k, 0.0f, 0.0f, (1.0f-k)*x0},
							    {0.0f, k, 0.0f, (1.0f-k)*y0},
							    {0.0f, 0.0f, 0.0f, 0.0f},
							    {0.0f, 0.0f, 0.0f, 1.0f}}) * screen_mat;
	transformation_changed = true;
}

void Window::set_projection()
{
	float s_image = 1.0f * frame.width() / frame.height();
	float s_window = 1.0f * _width / _height;
	if(s_image < s_window)
	{
		projection_mat = Matrix<float>({{2.0f * s_image/s_window/(frame.width()-1), 0.0f,                  0.0f, -s_image/s_window},
									    {0.0f,                                -2.0f/(frame.height()-1), 0.0f, 1.0f},
									    {0.0f,                                0.0f,                  0.0f, 0.0f},
									    {0.0f,                                0.0f,                  0.0f, 1.0f}});
	}
	else
	{
		projection_mat = Matrix<float>({{2.0f/(frame.width()-1), 0.0f,                               0.0f, -1.0f},
									    {0.0f,                   -2.0f*s_window/s_image/(frame.height()-1), 0.0f, s_window/s_image},
									    {0.0f,                   0.0f,                               0.0f, 0.0f},
									    {0.0f,                   0.0f,                               0.0f, 1.0f}});
	}
}

void Window::update_transformation()
{
	transformation_mat = screen_mat * projection_mat;
}

Window::Window(Image* image)
{
	_name = image->name();
	_color = Color(240, 240, 240);

	if(__window_array.empty())
	{
		atexit(__wait_rest_images);
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAC, GL_TRUE);
		#endif
	}

	int monitorCount;
	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode * mode = glfwGetVideoMode(pMonitor);
    screen_width = mode->width;
    screen_height = mode->height-90;

	_width = image->width();
	_height = image->height();
	float s = 1.0f * _width/_height;
	if(std::min(_width, _height) < 150)
	{
		if(_width < _height)
		{
			_width = 150;
			_height = (int)(150.0f / s);
		}
		else
		{
			_width = (int)(150.0f * s);
			_height = 150;
		}
	}
	if(_width > screen_width)
	{
		_width = screen_width;
		_height = (int)(_width/s);
	}
	if(_height > screen_height)
	{
		_width = (int)(screen_height * s);
		_height = screen_height;
	}

	_width = (_width >= 150 ? (_width <= screen_width ? _width : screen_width) : 150);
	_height = (_height >= 150 ? (_height <= screen_height ? _height : screen_height) : 150);

	father_image = image;
	th = thread(Window::show, this);
}

void Window::wait()
{
	if(th.joinable())
	{
		th.join();
	}
}

void Window::update()
{
	shader.use();
	if(transformation_changed)
	{
		update_transformation();
		shader.set("transformation", transformation_mat);
		transformation_changed = false;
	}
	frame.show();
}

void Window::load(Image* image)
{
	frame.load(image);
	set_projection();
	update_transformation();
}

void Window::show()
{
	_window = glfwCreateWindow(_width, _height, _name.data(), NULL, NULL);
	if(!_window)
	{
		cout << "Failed to create GLFW window!" << endl;
		exit(-1);
	}
	glfwMakeContextCurrent(_window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD!" << endl;
		exit(-1);
	}

	GLFWimage icons[2];
	icons[0] = Image("icons/icon.png");
	icons[1] = Image("icons/icon_small.png");
	glfwSetWindowIcon(_window, 2, icons);
	glfwSetWindowPos(_window, (int)(0.5f*(screen_width-_width)), (int)(0.5f*(screen_height+78-_height)));
	glfwShowWindow(_window);

	set_callbacks();
	glClearColor(_color.R, _color.G, _color.B, _color.A);

	shader.load("vertex.glsl", "fragment.glsl");

	projection_mat = eye(4);
	screen_mat = eye(4);

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 透明度
    // glEnable(GL_MULTISAMPLE); // 抗锯齿
	// glEnable(GL_DEPTH_TEST); // 深度测试
	// glEnable(GL_FRAMEBUFFER_SRGB); // Gamma 校正
	load(father_image);
	while(!glfwWindowShouldClose(_window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		update();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	frame.free_gl();
}

Shader::Shader(const char* vertex_source_filename, const char* fragment_source_filename)
{
	load(vertex_source_filename, fragment_source_filename);
}

void Shader::load(const char* vertex_source_filename, const char* fragment_source_filename)
{
	char* vertex_source = read_file(vertex_source_filename);
	char* fragment_source = read_file(fragment_source_filename);

	int  success;
	char infoLog[512];

	// 编译顶点着色器
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	delete vertex_source;
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		exit(-1);
	}

	// 编译片段着色器
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	delete fragment_source;
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		exit(-1);
	}

	// 链接着色器
	_program = glCreateProgram();
	glAttachShader(_program, vertex_shader);
	glAttachShader(_program, fragment_shader);
	glLinkProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if(!success)
	{
	    glGetProgramInfoLog(_program, 512, NULL, infoLog);
	    cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
	    exit(-1);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

unsigned int Shader::program()
{
	return _program;
}

void Shader::use()
{
	glUseProgram(_program);
}

void Shader::set(const string& name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::set(const string& name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
}

void Shader::set(const string& name, float value)
{
	use();
	glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::set(const string& name, unsigned int value)
{
	use();
	glUniform1ui(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::set(const string& name, const Matrix<float>& mat)
{
	use();
	int n_rows = mat.rows();
	int n_cols = mat.cols();
	int length = 0;
	if(n_rows == 1 || n_cols == 1)
	{
		length = (n_rows == 1 ? n_cols : n_rows);
	}
	if(length != 0)
	{
		switch(length)
		{
			case 2:
				glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, mat.data());
				break;
			case 3:
				glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, mat.data());
				break;
			case 4:
				glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, mat.data());
				break;
			default:
				break;
		}
		return;
	}

	if(n_rows == n_cols)
	{
		switch(n_rows)
		{
			case 2:
				glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, mat.data());
				break;
			case 3:
				glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, mat.data());
				break;
			case 4:
				glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, mat.data());
				break;
			default:
				break;
		}
	}
}

void ImageFrame::free_gl()
{
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void ImageFrame::show()
{
	glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

int ImageFrame::width()
{
	return image->width();
}

int ImageFrame::height()
{
	return image->height();
}

void ImageFrame::set_vertices()
{
	int n_rows = image->rows();
	int n_cols = image->cols();

	Matrix<float> R(n_rows, n_cols), G(n_rows, n_cols), B(n_rows, n_cols), A(n_rows, n_cols);
	image->splitRGBA(R, G, B, A);

	Matrix<float> X = to(0, n_cols-1);
	Matrix<float> Y = to(0, n_rows-1);
	meshgrid(X, Y);
	int N = X.size();
	Matrix<float> Xp(4*N, 1);
	Matrix<float> Yp(4*N, 1);
	for(int i = 0; i < N; i++)
	{
		Xp(4*i  ) = X(i)-0.5f;
		Xp(4*i+1) = X(i)-0.5f;
		Xp(4*i+2) = X(i)+0.5f;
		Xp(4*i+3) = X(i)+0.5f;

		Yp(4*i  ) = Y(i)-0.5f;
		Yp(4*i+1) = Y(i)+0.5f;
		Yp(4*i+2) = Y(i)+0.5f;
		Yp(4*i+3) = Y(i)-0.5f;
	}
	vertices = Matrix<float>({Xp,
							  Yp,
							  R.reshape(AUTO, 1).repelem(4, 1),
							  G.reshape(AUTO, 1).repelem(4, 1),
							  B.reshape(AUTO, 1).repelem(4, 1),
							  A.reshape(AUTO, 1).repelem(4, 1)}).t();
}

void ImageFrame::set_indices()
{
	int N = vertices.cols()/4;

	indices = Matrix<unsigned int>(6 * N, 1);

	int k = 0;
	for(int i = 0; i < N; i++)
	{
		int it = 4*i;
		indices(k  ) = it;
		indices(k+1) = it+1;
		indices(k+2) = it+2;

		indices(k+3) = it;
		indices(k+4) = it+3;
		indices(k+5) = it+2;

		k += 6;
	}
}

void ImageFrame::load(Image* image)
{
	this->image = image;
	set_vertices();
	set_indices();
	
	// 顶点位置
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertices.rows() * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertices.rows() * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}