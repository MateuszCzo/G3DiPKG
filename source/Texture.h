#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"Shader.h"

/// <summary>
/// Class that handles textures
/// </summary>
class Texture
{
public:
	GLuint id;
	const char* type;
	GLuint unit;

	/// <summary>
	/// Texture constructor assigns the texture to a texture unit, checks what type of color channels the texture has and generates mipMaps
	/// </summary>
	/// <param name="image">file path</param>
	/// <param name="texType">type of the texture diffuse or specular</param>
	/// <param name="slot">slot of the texture</param>
	Texture(const char* image, const char* texType, GLuint slot);

	/// <summary>
	/// Assigns a texture unit to a texture
	/// </summary>
	/// <param name="shader">shader object</param>
	/// <param name="uniform">uniform name</param>
	/// <param name="unit">value of the uniform</param>
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	/// <summary>
	/// Binds a texture
	/// </summary>
	void bind();

	/// <summary>
	/// Unbinds a texture
	/// </summary>
	void unbind();

	/// <summary>
	/// Deletes a texture
	/// </summary>
	void deleteT();
};
#endif