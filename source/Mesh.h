#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"


/// <summary>
/// Combines VAO, VBO and EBO into one class
/// </summary>
class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO vao;

	/// <summary>
	/// Initializes the mesh
	/// </summary>
	/// <param name="vertices">vertices of the object</param>
	/// <param name="indices">indices of the object</param>
	/// <param name="textures">textures of the object</param>
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	/// <summary>
	/// Draws the mesh
	/// </summary>
	/// <param name="shader">shader object</param>
	/// <param name="camera">camera object</param>
	/// <param name="matrix">matrix of the object</param>
	/// <param name="translation">position of the object</param>
	/// <param name="rotation">rotation of the object</param>
	/// <param name="scale">scale of the object</param>
	void draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};
#endif