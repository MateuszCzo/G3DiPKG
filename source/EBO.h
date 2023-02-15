#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

/// <summary>
/// Stores indices
/// </summary>
class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint id;

	/// <summary>
	/// Constructor that generates a Elements Buffer Object and links it to indices
	/// </summary>
	/// <param name="indices">indices of the object</param>
	EBO(std::vector<GLuint>& indices);

	/// <summary>
	/// Binds the EBO
	/// </summary>
	/// binds the ebo using it's id
	void bind();

	/// <summary>
	/// Unbinds the EBO
	/// </summary>
	void unbind();

	/// <summary>
	/// Deletes the EBO
	/// </summary>
	void deleteEBO();
};

#endif