#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

/// <summary>
/// Provides communication with shaders
/// </summary>
class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint id;
	/// <summary>
	/// Constructor that build the Shader Program from 2 different shaders
	/// </summary>
	/// <param name="vertexFile">file path to the vertex shader</param>
	/// <param name="fragmentFile">file path to the fragment shader</param>
	Shader(const char* vertexFile, const char* fragmentFile);

	/// <summary>
	/// Activates the Shader Program
	/// </summary>
	void activate();

	/// <summary>
	/// Deletes the Shader Program
	/// </summary>
	void deleteS();

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setBool(const std::string& name, bool value) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setInt(const std::string& name, int value) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setFloat(const std::string& name, float value) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setVec2(const std::string& name, const glm::vec2& value) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setVec2(const std::string& name, float x, float y) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setVec3(const std::string& name, const glm::vec3& value) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setVec3(const std::string& name, float x, float y, float z) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setVec4(const std::string& name, const glm::vec4& value) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setVec4(const std::string& name, float x, float y, float z, float w);

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setMat2(const std::string& name, const glm::mat2& mat) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setMat3(const std::string& name, const glm::mat3& mat) const;

    /// <summary>
    /// Inserts uniform into the shader
    /// </summary>
    /// <param name="name">name of the uniform in the shader</param>
    /// <param name="value">value that will be stored in the shader</param>
    void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	/// <summary>
	/// Checks if the different Shaders have compiled properly
	/// </summary>
	/// <param name="shader">shader id</param>
	/// <param name="type">type of problem</param>
	void compileErrors(unsigned int shader, const char* type);
};


#endif