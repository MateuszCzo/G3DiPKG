#include "Main.h"
#include <iostream>

int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ships 3D", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// Player and Computer fields
	Array* arrayP = new Array();
	Array* arrayC = new Array();
	setShips(arrayC);


	// Control variables
	int numOfShip = 0;
	bool playerSetShips = true;
	bool playerTurn = true;
	int shipOrientation = 0;
	bool firstRightClick = true;
	bool firstLeftClick = true;
	bool firstRClick = true;
	bool reset = false;
	int shipsRotations[4] = {0,0,0,0};


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Light
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	shaderProgram.activate();
	shaderProgram.setVec4("lightColor", lightColor);
	shaderProgram.setVec3("lightPos", lightPos);


	// Loading textures from files
	Model emptyModel("objects/square-empty/scene.gltf");
	Model shipModel("objects/square-ship/scene.gltf");
	Model missModel("objects/square-miss/scene.gltf");
	Model hitModel("objects/square-hit/scene.gltf");

	// Rotating textures (in blender z and y axes are switched)
	emptyModel.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	shipModel.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	missModel.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	hitModel.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));

	// Loading ships
	Model ship2("objects/ship2/scene.gltf");
	Model ship3("objects/ship3/scene.gltf");
	Model ship4("objects/ship4/scene.gltf");
	Model ship5("objects/ship5/scene.gltf");

	// Rotating ships (nie wiem czemu nie musze tego obracac)
	ship2.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	ship2.newOrientation(90, glm::vec3(0.0f, 1.0f, 0.0f));
	ship3.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	ship3.newOrientation(90, glm::vec3(0.0f, 1.0f, 0.0f));
	ship4.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	ship4.newOrientation(90, glm::vec3(0.0f, 1.0f, 0.0f));
	ship5.newOrientation(-90, glm::vec3(0.0f, 0.0f, 1.0f));
	ship5.newOrientation(90, glm::vec3(0.0f, 1.0f, 0.0f));


	// Saving ships in array
	Model** ships = new Model*[4];
	ships[0] = &ship5;
	ships[1] = &ship4;
	ships[2] = &ship3;
	ships[3] = &ship2;


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);


	// Hides mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, (SCR_WIDTH / 2), (SCR_HEIGHT / 2));


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		
		// Draws player board
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (arrayP->getFieldInfo(i, j).isShip && arrayP->getFieldInfo(i, j).isShot)
				{
					hitModel.newPosition(-glm::vec3(1.0f * i, 0.0f, 1.0f * j));
					hitModel.draw(shaderProgram, camera);
				}
				else if (arrayP->getFieldInfo(i, j).isShip)
				{
					shipModel.newPosition(-glm::vec3(1.0f * i, 0.0f, 1.0f * j));
					shipModel.draw(shaderProgram, camera);
				}
				else if (arrayP->getFieldInfo(i, j).isShot)
				{
					missModel.newPosition(-glm::vec3(1.0f * i, 0.0f, 1.0f * j));
					missModel.draw(shaderProgram, camera);
				}
				else
				{
					emptyModel.newPosition(-glm::vec3(1.0f*i, 0.0f, 1.0f*j));
					emptyModel.draw(shaderProgram, camera);
				}
			}
		}
		// Drawing computer board
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (arrayC->getFieldInfo(i, j).isShip && arrayC->getFieldInfo(i, j).isShot)
				{
					hitModel.newPosition(-glm::vec3(1.0f * i + 11.0f, 0.0f, 1.0f * j));
					hitModel.draw(shaderProgram, camera);
				}
				else if (arrayC->getFieldInfo(i, j).isShot)
				{
					missModel.newPosition(-glm::vec3(1.0f * i + 11.0f, 0.0f, 1.0f * j));
					missModel.draw(shaderProgram, camera);
				}
				else
				{
					emptyModel.newPosition(-glm::vec3(1.0f * i + 11.0f, 0.0f, 1.0f * j));
					emptyModel.draw(shaderProgram, camera);
				}
			}
		}
		// Drawing ships
		for (int i = 0; i < numOfShip; i++)
		{
			ships[i]->draw(shaderProgram, camera);
		}
		// Putting ships
		if (playerSetShips)
		{
			// new ship position
			glm::vec3 position(0.0f, 0.0f, 0.0f);
			for (int i = 0; i < 50; i++)
			{
				// calculate new ship position
				position = camera.position + glm::vec3(camera.orientation.x * i, camera.orientation.y * i, camera.orientation.z * i);
				position = round(position);
				if ((position.x >= 0 && position.x < 10) && (position.y == -1) && (position.z >= 0 && position.z < 10))
				{
					ships[numOfShip]->newPosition(-glm::vec3(position.x, 1.0f, position.z));
					ships[numOfShip]->draw(shaderProgram, camera);
					break;
				}
			}
			// player placing ships
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			{
				if (firstRightClick)
				{
					firstRightClick = false;
					if (arrayP->setShip(position.x, position.z, shipOrientation, 5-numOfShip))
					{
						numOfShip++;
						shipOrientation = 0;

						if (numOfShip==4)
						{
							playerSetShips = false;
						}
					}
				}
			}
			else
			{
				if (!firstRightClick)
				{
					firstRightClick = true;
				}
			}
			// rotating ship
			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			{
				if (firstRClick)
				{
					firstRClick = false;
					shipOrientation++;
					ships[numOfShip]->newOrientation(90, glm::vec3(0.0f, 1.0f, 0.0f));
					if (shipOrientation == 4)
					{
						shipOrientation = 0;
					}
					shipsRotations[numOfShip] = shipOrientation;
				}
			}
			else
			{
				if (!firstRClick)
				{
					firstRClick = true;
				}
			}
		}
		// Shooting
		else
		{
			if (playerTurn)
			{
				// Show where player shoot
				glm::vec3 position(0.0f, 0.0f, 0.0f);
				for (int i = 0; i < 50; i++)
				{
					position = camera.position + glm::vec3(camera.orientation.x * i, camera.orientation.y * i, camera.orientation.z * i);
					position = round(position);
					if ((position.x >= 11 && position.x <= 20) && (position.y == 0) && (position.z >= 0 && position.z < 10))
					{
						hitModel.newPosition(-glm::vec3(position.x, 1.0f, position.z));
						hitModel.draw(shaderProgram, camera);
						break;
					}
				}
				// Player shooting
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					if (firstLeftClick)
					{
						firstLeftClick = false;
						if (arrayC->shoot(position.x - 11, position.z))
						{
							// Check if computer lost
							if (arrayC->ifLose())
							{
								if (restartWindow(window, shaderProgram, 1))
								{
									reset = true;
								}
								else
								{
									glfwSetWindowShouldClose(window, true);
								}
							}
							else
							{
								playerTurn = false;
							}
						}
					}
				}
				else
				{
					if (!firstLeftClick)
					{
						firstLeftClick = true;
					}
				}
			}
			else
			{
				shootP(arrayP);
				// Check if player lost
				if (arrayP->ifLose())
				{
					if (restartWindow(window, shaderProgram, 2))
					{
						reset = true;
					}
					else
					{
						glfwSetWindowShouldClose(window, true);
					}
				}
				else
				{
					playerTurn = true;
				}
			}
		}

		if (reset)
		{
			// reset control vacriables
			numOfShip = 0;
			playerSetShips = true;
			playerTurn = true;
			shipOrientation = 0;
			firstRightClick = true;
			firstLeftClick = true;
			firstRClick = true;
			reset = false;
			// reset fields
			arrayC->reset();
			arrayP->reset();
			// reset camera
			camera.orientation = glm::vec3(0.0f, -0.707106781187f, -0.707106781187f);
			camera.position = glm::vec3(10.0f, 20.0f, 20.0f);
			// new computer ships positions
			setShips(arrayC);
			// reset ships orientations
			for (int i = 0; i < 4; i++)
			{
				ships[i]->newOrientation(90 * -shipsRotations[i], glm::vec3(0.0f, 1.0f, 0.0f));
			}
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete shader
	shaderProgram.deleteS();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	camera.setScreenSize(width, height);
	SCR_HEIGHT = height;
	SCR_WIDTH = width;
	glViewport(0, 0, width, height);
}

void setShips(Array* arrayC)
{
	srand(time(NULL));
	int x;
	int y;
	int orientation;
	// Ships length = 2 - 5
	for (int i = 5; i >= 2; i--)
	{
		do
		{
			x = rand() % 10;
			y = rand() % 10;
			orientation = rand() % 4;
		} while (!arrayC->setShip(x, y, orientation, i));
	}
}

void shootP(Array* arrayP)
{
	int x;
	int y;
	do
	{
		x = rand() % 10;
		y = rand() % 10;
	} while (!arrayP->shoot(x, y));
}

bool restartWindow(GLFWwindow* window, Shader shader, int whoWin)
{
	// Textures
	Texture close[]
	{
		Texture("messages/close.png", "diffuse", 0),
		Texture("messages/close.png", "specular", 1)
	};
	Texture gameOver[]
	{
		Texture("messages/game_over.png", "diffuse", 0),
		Texture("messages/game_over.png", "specular", 1)
	};
	Texture startOver[]
	{
		Texture("messages/start_over.png", "diffuse", 0),
		Texture("messages/start_over.png", "specular", 1)
	};
	Texture youWon[]
	{
		Texture("messages/you_won.png", "diffuse", 0),
		Texture("messages/you_won.png", "specular", 1)
	};
	// Store mesh data in vectors for the mesh
	std::vector <Texture> closeTex(close, close + sizeof(close) / sizeof(Texture));
	std::vector <Texture> gameOverTex(gameOver, gameOver + sizeof(gameOver) / sizeof(Texture));
	std::vector <Texture> startOverTex(startOver, startOver + sizeof(startOver) / sizeof(Texture));
	std::vector <Texture> youWonTex(youWon, youWon + sizeof(youWon) / sizeof(Texture));


	// Vertices coordinates
	Vertex vertices[] =
	{ //               COORDINATES           /            COLORS          /           NORMALS          /       TexCoord       //
		Vertex{glm::vec3(-0.5f, -0.125f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // left bottom
		Vertex{glm::vec3(-0.5f,  0.125f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // left top
		Vertex{glm::vec3( 0.5f,  0.125f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // right top
		Vertex{glm::vec3( 0.5f, -0.125f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}  // right bottom
	};
	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2, 
		0, 2, 3
	};
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));



	// Reset camera
	camera.position = glm::vec3(0.0f, 0.0f, 2.0f);
	camera.orientation = glm::vec3(0.0f, 0.0f, -1.0f);

	// Reset mouse coursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPos(window, (SCR_WIDTH / 2), (SCR_HEIGHT / 2));


	// Position of mesages
	glm::mat4 position1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
	glm::mat4 position2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f));


	Mesh* message;
	if (whoWin == 1)
	{
		message = new Mesh(verts, ind, youWonTex);
	}
	else
	{
		message = new Mesh(verts, ind, gameOverTex);
	}
	Mesh continueMessage(verts, ind, startOverTex);
	Mesh closeMessage(verts, ind, closeTex);


	bool firstLClick = false;


	// Draw loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Drawing messages
		message->draw(shader, camera, position1);
		continueMessage.draw(shader, camera);
		closeMessage.draw(shader, camera, position2);

		if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			firstLClick = true;
		}

		if (firstLClick)
		{
			// Checking if player click button
			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			if (mouseX > (SCR_WIDTH * 0.5 - SCR_WIDTH * 0.3) && mouseX < (SCR_WIDTH * 0.5 + SCR_WIDTH * 0.3))
			{
				// close buttion
				if (mouseY > SCR_HEIGHT / 1.37 && mouseY < SCR_HEIGHT / 1.14)
				{
					if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
					{
						return false;
					}
				}
				// continue button
				else if (mouseY > SCR_HEIGHT / 2.35 && mouseY < SCR_HEIGHT / 1.75)
				{
					if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
					{
						return true;
					}
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
}