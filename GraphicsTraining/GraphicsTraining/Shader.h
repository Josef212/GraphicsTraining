#ifndef SHADER_H
#define SHADER_H

#include "Resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader : public Resource
{
public:
	Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	virtual ~Shader();

	void Free() override;

	void Use()const;

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetVec2(const char* name, const glm::vec2& value) const;
	void SetVec2(const char* name, const float* value) const;
	void SetVec2(const char* name, float x, float y) const;
	void SetVec3(const char* name, const glm::vec3& value) const;
	void SetVec3(const char* name, const float* value) const;
	void SetVec3(const char* name, float x, float y, float z) const;
	void SetVec4(const char* name, const glm::vec4& value) const;
	void SetVec4(const char* name, const float* value) const;
	void SetVec4(const char* name, float x, float y, float z, float w) const;
	void SetMat2(const char* name, const glm::mat2& value) const;
	void SetMat2(const char* name, const float* value) const;
	void SetMat3(const char* name, const glm::mat3& value) const;
	void SetMat3(const char* name, const float* value) const;
	void SetMat4(const char* name, const glm::mat4& value) const;
	void SetMat4(const char* name, const float* value) const;

private:
	std::string LoadCode(const char* path);
	int CreateShader(const char* code, GLenum type);
	void CheckCompileErrors(int sh, const char* type);

public:
	unsigned int ID;
	std::string vertPath, fragPath, geoPath;
};

#endif // SHADER_H
