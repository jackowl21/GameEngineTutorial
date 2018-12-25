//#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/GLU.h>

#include "camera.h"
#include "matrix.h"
#include "vector.h"


#include "Application.h"

//#define WINDOW_WIDTH 640
//#define WINDOW_HEIGHT 480

float prevTime = glfwGetTime();
float startTime = glfwGetTime();
int frameRate = 0;
float deltaTime = 0;
double mouseX = 0;
double mouseY = 0;
int mouseClicked = 0;

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(0.0, width, 0.0, height);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

//! DeltaTime updates.
void DeltaTime()
{
	glfwSwapInterval(1);

	float curTime = glfwGetTime();
	deltaTime = curTime - prevTime;

	frameRate++;

	if (curTime - startTime >= 1.0)
	{
		//std::cout << "Delta Time: " << deltaTime << std::endl;
		//std::cout << "Framerate: " << frameRate << std::endl;
		startTime += 1;
		frameRate = 0;
	}

	prevTime = curTime;

	glfwSwapInterval(0);
}

void gameUpdate(void)
{
	DeltaTime();
}

void mouseInput(GLFWwindow* window, Application &app)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		mouseClicked++;
		glfwGetCursorPos(window, &mouseX, &mouseY);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		mouseClicked = 0;
	}

	if (mouseClicked == 1)
	{
		app.mouseX = mouseX;

		mouseY = WINDOW_HEIGHT - mouseY;
		app.mouseY = mouseY;

		app.isClicked = true;
	}

}


int main()
{
	int running = GL_TRUE;

	GLFWwindow* window;

	float timer = 0;
	/* Initialize the GLFW library */
	if (!glfwInit())
		return -1;

	// Open an OpenGL window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwMakeContextCurrent(window);
	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	Application app;
	Application app2;

	app.start();
	//app2.start();

	//app.appMode = APP_PARTICLE_DISPLAY_1;
	app.appMode = APP_PARTICLE_DISPLAY_3;
	//app.appMode = APP_PARTICLE_SPAWN;
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		timer++;
		gameUpdate();
		
		app.ReceiveKey(window);
		app.ReceiveMouseInput(window);
		app.update(deltaTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
}



