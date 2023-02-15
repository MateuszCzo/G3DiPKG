#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

/// <summary>
/// Structure to standardize the vertices used in the meshes
/// </summary>
/// contains position coordinates, normals, colors and texture coordinates
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

/// <summary>
/// Stores position coordinates, normals, colors and texture coordinates
/// </summary>
class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint id;

	/// <summary>
	/// Constructor that generates a Vertex Buffer Object and links it to vertices
	/// </summary>
	/// <param name="vertices">vertices data</param>
	VBO(std::vector<Vertex>& vertices);

	/// <summary>
	/// Binds the VBO
	/// </summary>
	void bind();

	/// <summary>
	/// Unbinds the VBO
	/// </summary>
	void unbind();

	/// <summary>
	/// Deletes the VBO
	/// </summary>
	void deleteVBO();
};

#endif