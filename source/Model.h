#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

/// <summary>
/// Allows to display 3D objects loaded from files
/// </summary>
class Model
{
public:
	/// <summary>
	///  Loads in a model from a file and stores tha information in 'data', 'JSON', and 'file'
	/// </summary>
	/// <param name="file">file name</param>
	Model(const char* file);

	/// <summary>
	/// Draws the object
	/// </summary>
	/// <param name="shader">shader object</param>
	/// <param name="camera">camera object</param>
	void draw(Shader& shader, Camera& camera);

	/// <summary>
	/// Changing the object position
	/// </summary>
	/// <param name="position">new position</param>
	void newPosition(glm::vec3 position);

	/// <summary>
	/// Changing the object orientation
	/// </summary>
	/// <param name="degrdes">the number of degrees we want to rotate the object</param>
	/// <param name="a">axes on which we want to rotate the object</param>
	void newOrientation(int degres, glm::vec3 a);
private:
	// Variables for easy access
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// All the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	/// <summary>
	/// Loads a single mesh by its index
	/// </summary>
	/// <param name="indMesh">number of mesh</param>
	/// loads indices, coordinates, normals, texture coordinates and textures of a single mesh
	void loadMesh(unsigned int indMesh);

	/// <summary>
	/// Traverses a node recursively, so it essentially traverses all connected nodes
	/// </summary>
	/// <param name="nextNode">number of the next node</param>
	/// <param name="matrix">matrix of the previous node</param>
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	/// <summary>
	/// Gets the binary data from a file
	/// </summary>
	/// <returns>binary data from a file</returns>
	std::vector<unsigned char> getData();

	/// <summary>
	/// Interprets the binary data into floats
	/// </summary>
	/// <param name="accessor">json object form with to extract the data</param>
	/// <returns>vector object with coordinates, normals or texture coordinates</returns>
	std::vector<float> getFloats(json accessor);

	/// <summary>
	/// Interprets the binary data into indices
	/// </summary>
	/// <param name="accessor">json object form with to extract the data</param>
	/// <returns>vector object with indices</returns>
	std::vector<GLuint> getIndices(json accessor);

	/// <summary>
	/// Interprets the binary data into textures
	/// </summary>
	/// <returns>diffuse and specular textures</returns>
	std::vector<Texture> getTextures();

	/// <summary>
	/// Assembles all the floats into vertices
	/// </summary>
	/// <param name="positions">coordinates of a single mesh</param>
	/// <param name="normals">normals of a single mesh</param>
	/// <param name="texUVs">texture coordinates of a single mesh</param>
	/// <returns>std:vector object so it can be interpreted by the Mesh class</returns>
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	/// <summary>
	/// Group floats in glm vector 2 object
	/// </summary>
	/// <param name="floatVec">vector object from std library</param>
	/// <returns>glm vector 2 object</returns>
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);

	/// <summary>
	/// Group floats in glm vector 3 object
	/// </summary>
	/// <param name="floatVec">vector object from std library</param>
	/// <returns>glm vector 3 object</returns>
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);

	/// <summary>
	/// Group floats in glm vector 4 object
	/// </summary>
	/// <param name="floatVec">vector object from std library</param>
	/// <returns>glm vector 4 object</returns>
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};
#endif