#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

/// <summary>
/// Stores VBOs
/// </summary>
class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint id;

	/// <summary>
	/// Constructor that generates a VAO id
	/// </summary>
	VAO();

	/// <summary>
	/// Links a VBO Attribute such as a position or color to the VAO
	/// </summary>
	/// <param name="VBO">VBO object</param>
	/// <param name="layout">layout location in shader</param>
	/// <param name="numComponents">number of values</param>
	/// <param name="type">type of values</param>
	/// <param name="stride">size of all values</param>
	/// <param name="offset">offset to the next values</param>
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	/// <summary>
	/// Binds the VAO
	/// </summary>
	void bind();

	/// <summary>
	/// Unbinds the VAO
	/// </summary>
	void unbind();

	/// <summary>
	/// Deletes the VAO
	/// </summary>
	void deleteVAO();
};

#endif