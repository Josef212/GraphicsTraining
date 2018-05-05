#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath) : Resource(name, RES_SHADER)
{
	vertPath = vertexPath;
	fragPath = fragmentPath;
	geoPath = geometryPath ? geometryPath : "";

	LoadShader();
}

Shader::~Shader()
{

}

void Shader::LoadShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath)
{
	vertPath = vertexPath;
	fragPath = fragmentPath;
	geoPath = geometryPath;

	LoadShader();
}

void Shader::LoadShader()
{
	std::string vertexCode = LoadCode(vertPath.c_str());
	std::string fragmentCode = LoadCode(fragPath.c_str());
	std::string geometryCode;
	if (!geoPath.empty()) geometryCode = LoadCode(geoPath.c_str());

	unsigned int vertex, fragment, geometry;

	vertex = CreateShader(vertexCode.c_str(), GL_VERTEX_SHADER);
	fragment = CreateShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
	if (!geoPath.empty()) geometry = CreateShader(geometryCode.c_str(), GL_GEOMETRY_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (!geoPath.empty()) glAttachShader(ID, geometry);

	glLinkProgram(ID);
	CheckCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (!geoPath.empty()) glDeleteShader(geometry);
}

void Shader::ReloadShader()
{
	glDeleteProgram(ID);
	LoadShader();
}

void Shader::Free()
{
	glDeleteProgram(ID);
	vertPath = fragPath = geoPath = "";
	status = SH_PENDING;
}

void Shader::Use()const
{
	glUseProgram(ID);
}

// -----

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::SetVec2(const char* name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::SetVec2(const char* name, const float* value) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, value);
}
void Shader::SetVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}
void Shader::SetVec3(const char* name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::SetVec3(const char* name, const float* value) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, value);
}
void Shader::SetVec3(const char* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
void Shader::SetVec4(const char* name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::SetVec4(const char* name, const float* value) const
{
	glUniform4fv(glGetUniformLocation(ID, name), 1, value);
}
void Shader::SetVec4(const char* name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
void Shader::SetMat2(const char* name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]);
}
void Shader::SetMat2(const char* name, const float* value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value);
}
void Shader::SetMat3(const char* name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]);
}
void Shader::SetMat3(const char* name, const float* value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value);
}
void Shader::SetMat4(const char* name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]);
}
void Shader::SetMat4(const char* name, const float* value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, value);
}

void Shader::LogCode()
{
	std::string vertexCode = LoadCode(vertPath.c_str());
	std::string fragmentCode = LoadCode(fragPath.c_str());
	std::string geometryCode;
	if (!geoPath.empty()) geometryCode = LoadCode(geoPath.c_str());

	std::cout << "==========================" << std::endl;

	std::cout << "SHADER CODE: " << GetName() << std::endl;
	std::cout << "STATUS: ";
	switch (status)
	{
	case SH_COMPILED: std::cout << "COMPILED"; break;
	case SH_ERROR: std::cout << "ERROR"; break;
	case SH_PENDING: std::cout << "PENDING"; break;
	}
	std::cout << std::endl;

	std::cout << "\tVertex: " << std::endl;
	std::cout << vertexCode << std::endl << std::endl;
	std::cout << "\tFragment: " << std::endl;
	std::cout << fragmentCode << std::endl << std::endl;
	std::cout << "\tGeometry: " << std::endl;
	std::cout << geometryCode << std::endl << std::endl;

	std::cout << "==========================" << std::endl;
}

Shader_Status Shader::GetStatus() const
{
	return status;
}

// ---------------------------------------------------------------------

std::string Shader::LoadCode(const char* path)
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

int Shader::CreateShader(const char* code, GLenum type)
{
	int ret = 0;

	ret = glCreateShader(type);
	glShaderSource(ret, 1, &code, NULL);
	glCompileShader(ret);
	CheckCompileErrors(ret, "SHADER");

	return ret;
}

void Shader::CheckCompileErrors(int sh, const char* type)
{
	int success;
	char infoLog[1024];
	if (strcmp(type, "PROGRAM") != 0)
	{
		glGetShaderiv(sh, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(sh, 1024, NULL, infoLog);
			std::cout << GetName() << "->" << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(sh, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(sh, 1024, NULL, infoLog);
			std::cout << GetName() << "->" << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			status = SH_ERROR;
		}
		else
		{
			status = SH_COMPILED;
			std::cout << GetName() << " just compiled." << std::endl;
		}
	}
}