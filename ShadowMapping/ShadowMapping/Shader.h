#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		vertPath = vertexPath;
		fragPath = fragmentPath;
		if (geometryPath) geoPath = geometryPath;
		this->name = name;

		std::string vertexCode = LoadCode(vertexPath);
		std::string fragmentCode = LoadCode(fragmentPath);
		std::string geometryCode;
		if (geometryPath) geometryCode = LoadCode(geometryPath);

		unsigned int vertex, fragment, geometry;

		vertex = CreateShader(vertexCode.c_str(), GL_VERTEX_SHADER);
		fragment = CreateShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
		if(geometryPath) geometry = CreateShader(geometryCode.c_str(), GL_GEOMETRY_SHADER);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if(geometryPath) glAttachShader(ID, geometry);

		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if(geometryPath) glDeleteShader(geometry);
	}

	virtual ~Shader()
	{
		glDeleteProgram(ID);
	}

	void Use()
	{
		glUseProgram(ID);
	}

	void SetBool(const char* name, bool value) const { glUniform1i(glGetUniformLocation(ID, name), (int)value); }
	void SetInt(const char* name, int value) const { glUniform1i(glGetUniformLocation(ID, name), value); }
	void SetFloat(const char* name, float value) const { glUniform1f(glGetUniformLocation(ID, name), value); }
	void SetVec2(const char* name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]); }
	void SetVec2(const char* name, const float* value) const { glUniform2fv(glGetUniformLocation(ID, name), 1, value); }
	void SetVec2(const char* name, float x, float y) const { glUniform2f(glGetUniformLocation(ID, name), x, y); }
	void SetVec3(const char* name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]); }
	void SetVec3(const char* name, const float* value) const { glUniform3fv(glGetUniformLocation(ID, name), 1, value); }
	void SetVec3(const char* name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ID, name), x, y, z); }
	void SetVec4(const char* name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]); }
	void SetVec4(const char* name, const float* value) const { glUniform4fv(glGetUniformLocation(ID, name), 1, value); }
	void SetVec4(const char* name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); }
	void SetMat2(const char* name, const glm::mat2& value) const { glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]); }
	void SetMat2(const char* name, const float* value) const { glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value); }
	void SetMat3(const char* name, const glm::mat3& value) const { glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]); }
	void SetMat3(const char* name, const float* value) const { glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value); }
	void SetMat4(const char* name, const glm::mat4& value) const { glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]); }
	void SetMat4(const char* name, const float* value) const { glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value); }

private:
	std::string LoadCode(const char* path)
	{
		std::string ret;
		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			file.open(path);
			std::stringstream stream;
			stream << file.rdbuf();
			file.close();
			ret = stream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ from [" << path << "]." << std::endl;
		}

		return ret;
	}

	int CreateShader(const char* code, GLenum type)
	{
		int ret = 0;

		ret = glCreateShader(type);
		glShaderSource(ret, 1, &code, NULL);
		glCompileShader(ret);
		CheckCompileErrors(ret, "SHADER");

		return ret;
	}

	void CheckCompileErrors(int sh, const char* type)
	{
		int success;
		char infoLog[1024];
		if(strcmp(type, "PROGRAM") != 0)
		{
			glGetShaderiv(sh, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog(sh, 1024, NULL, infoLog);
				std::cout << name << "->" << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(sh, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(sh, 1024, NULL, infoLog);
				std::cout << name << "->" << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

public:
	unsigned int ID;
	std::string name;
	std::string vertPath, fragPath, geoPath;
};

#endif // SHADER_H
