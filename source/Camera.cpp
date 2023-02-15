#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	orientation = glm::vec3(0.0f, -0.707106781187f, -0.707106781187f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera::width = width;
	Camera::height = height;
	Camera::position = position;
	cameraMatrix = glm::mat4(1.0f);
	firstClick = true;
	speed = 0.1f;
	sensitivity = 100.0f;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(position, position + orientation, up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	shader.setMat4(uniform, cameraMatrix);
}



void Camera::inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * glm::normalize(-glm::cross(glm::normalize(glm::cross(orientation, up)), up));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(glm::normalize(glm::cross(orientation, up)), up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 0.2f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}


	//obracanie kamery

	// Stores the coordinates of the cursor
	double mouseX;
	double mouseY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 
	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

	// Calculates upcoming vertical change in the Orientation
	glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

	// Decides whether or not the next vertical Orientation is legal or not
	if (abs(glm::angle(newOrientation, up) - glm::radians(85.0f)) <= glm::radians(85.0f))
	{
		orientation = newOrientation;
	}

	// Rotates the Orientation left and right
	orientation = glm::rotate(orientation, glm::radians(-rotY), up);

	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
	glfwSetCursorPos(window, (width / 2), (height / 2));
}

void Camera::setScreenSize(int width, int height)
{
	this->width = width;
	this->height = height;
}