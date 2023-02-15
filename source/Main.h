#ifndef MAIN_H
#define MAIN_H

#include "Mesh.h"
#include "Array.h"
#include "Model.h"


// window size
unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 1000;

// Light
glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightPos = glm::vec3(10.0f, 20.0f, 5.5f);

// camera object
Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(10.0f, 20.0f, 20.0f));


/// <summary>
/// Saving the window size change
/// </summary>
/// <param name="window">window object in which we change the size</param>
/// <param name="width">new width of the window</param>
/// <param name="height">new height of the window</param>
/// function is called when the size of the window is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/// <summary>
/// Insert ships by computer
/// </summary>
/// <param name="arrayC">computer's board</param>
/// ships are inserting randomly
void setShips(Array* arrayC);

/// <summary>
/// Shooting player board by computer
/// </summary>
/// <param name="arrayP">players's board</param>
/// the computer shoots randomly
void shootP(Array* arrayP);

/// <summary>
/// Checking if player wonts to restart
/// </summary>
/// <param name="window">window object in which to display the message</param>
/// <param name="shader">shader object</param>
/// <param name="whoWin">informatin who win</param>
/// the information on who won is 1 if the player won, or 2 if the computer
/// <returns>true if player wonts to restart</returns>
bool restartWindow(GLFWwindow* window, Shader shader, int whoWin);

#endif // !MAIN_H