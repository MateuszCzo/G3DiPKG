#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Shader.h"

/// <summary>
/// Stores information about where to display objects on the screen
/// </summary>
class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 up;
	glm::mat4 cameraMatrix;
	bool firstClick;
	int width;
	int height;
	float speed;
	float sensitivity;

	/// <summary>
	/// Camera constructor to set up initial values
	/// </summary>
	/// <param name="width">width of the window</param>
	/// <param name="height">height of the window</param>
	/// <param name="position">position of the camera in world</param>
	Camera(int width, int height, glm::vec3 position);

	/// <summary>
	/// Updates the camera matrix to the Vertex Shader
	/// </summary>
	/// <param name="FOVdeg">field of view degree</param>
	/// <param name="nearPlane">near render distance</param>
	/// <param name="farPlane">far render distance</param>
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	/// <summary>
	/// Exports the camera matrix to a shader
	/// </summary>
	/// <param name="shader">shader object</param>
	/// <param name="uniform">name of the uniform in shader</param>
	void matrix(Shader& shader, const char* uniform);

	/// <summary>
	/// Handles camera inputs
	/// </summary>
	/// <param name="window">window object in which we are handling mouse inputs</param>
	void inputs(GLFWwindow* window);

	/// <summary>
	/// Changing the size of the window
	/// </summary>
	/// <param name="width">new width of the window</param>
	/// <param name="height">new height of the window</param>
	void setScreenSize(int width, int height);
};
#endif