
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "../liboidaui/canvas.hpp"
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	canvas::Initialize();
	canvas::Canvas *c = new canvas::Canvas();

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		c->draw({
			0
		});

		/*
		glPushMatrix();

		glBegin(GL_QUADS);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0, 0, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(1, 0, 0.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1,1, 0.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0, 1, 0.f);

		glEnd();

		glPopMatrix();
		 */

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	canvas::Free();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
