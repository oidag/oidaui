#include <GLFW/glfw3.h>
#include "../liboidaui/canvas.hpp"
#include "../liboidaui/elements/label.hpp"
#include <cstdio>

int main(void)
{
	Canvas c = Canvas();
	Font f = Font();
	Label l = Label("Hello World!");
	oui_err err = f.load("/usr/share/fonts/truetype/dejavu/DejaVuSerif-Italic.ttf");
	if(err) {
		printf("failed with error: %d\n", err);
		return -1;
	}
	l.setFont(&f);
	c.addElement(&l);

	// everything below this is typical glfw stuff.

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		c.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}