#include "Shader.h"

using namespace std;

Shader::Shader(const char* vertexfile, const char* fragmentfile)
{

	ReadFiles(vertexfile, fragmentfile);
	CreateShader();
	
	compile();
	shader_program = glCreateProgram();
	glAttachShader(shader_program,vertex_shader);
	glAttachShader(shader_program,fragment_shader);
	Link();
	//glBindAttribLocation(shader_program​, 0​,"position"​);
	
	//use
}

void Shader::ReadFiles(const char* vertexfile, const char* fragmentfile)
{
	ifstream v(vertexfile);
	if (v.is_open())
	{
		string str;
		ostringstream ss;
		ss << v.rdbuf(); // reading data
		vert_shader_source = ss.str();
	}
	v.close();

	ifstream f(fragmentfile);
	if (v.is_open())
	{
		string str;
		ostringstream ss;
		ss << v.rdbuf(); // reading data
		frag_shader_source = ss.str();
	}
	f.close();
}

void Shader::CreateShader()
{
	const char* ve = vert_shader_source.c_str();
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &ve, NULL);

	const char* fa = frag_shader_source.c_str();
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fa, NULL);

}

void Shader::compile()
{
	//vertex
	GLsizei log1Length;
	GLchar  log1[1024];
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &stats);
	if (!stats)
	{
		glGetShaderInfoLog(vertex_shader, sizeof(log1), &log1Length, log1);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log1 << std::endl;
	}
	//fragment
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &stats);
	if (!stats)
	{
		glGetShaderInfoLog(fragment_shader, sizeof(log1), &log1Length, log1);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log1 << std::endl;
	}
}

void Shader::Link()
{
	GLsizei log1Length;
	GLchar  log1[1024];
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &stats);
	if (!stats)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, log1);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log1 << std::endl;
	}
	else
	{
		std::cout << "Shader Program is linked" << std::endl;
	}
}

void Shader::Use()
{
	glUseProgram(shader_program);
}

void Shader::Delete()
 {
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
 }

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shader_program, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(shader_program, name.c_str()), x, y);
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(shader_program, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shader_program, name.c_str()), x, y, z, w);
}
void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::getLocations()
{
	auto loc1=  glGetAttribLocation(shader_program, "position");
	auto loc2 = glGetAttribLocation(shader_program, "normal");
	auto loc3 = glGetAttribLocation(shader_program, "textureCoordinates");

	auto loc4 = glGetUniformLocation(shader_program, "modelview_matrix");
	auto loc5 = glGetUniformLocation(shader_program, "projection_matrix");
	auto loc6 = glGetUniformLocation(shader_program, "view_matrix");
	if(loc1=-1)
	{
		cout << "position is not bound" << endl;
	}
	else
	{
		locations[loc1] = "position";
	}
	if (loc2 = -1)
	{
		cout << "normal is not bound" << endl;
	}
	else
	{
		locations[loc2] = "normal";
	}
	if (loc3 = -1)
	{
		cout << "texcoord is not bound" << endl;
	}
	else
	{
		locations[loc3] = "textureCoordinates";
	}
	if (loc4 = -1)
	{
		cout << "modelview matrix is not bound" << endl;
	}
	else
	{
		locations[loc4] = "modelview_matrix";
	}
	if (loc5 = -1)
	{
		cout << "projection matrix is not bound" << endl;
	}
	else
	{
		locations[loc5] = "projection_matrix";
	}
	if (loc6 = -1)
	{
		cout << "view matrix is not bound" << endl;
	}
	else
	{
		locations[loc6] = "view_matrix";
	}

}
