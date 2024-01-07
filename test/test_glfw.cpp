#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

#include <GLFW/glfw3.h>

#include "../liboidaui/font/font.hpp"
#include <glm/glm.hpp>
#include <cstdio>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	Font::Orthographic(width, height, 1);
}

int main(void)
{


	// everything below this is typical glfw stuff.

	GLFWwindow* window;


	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	unsigned int width = 800;
	unsigned int height = 600;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	util::Shader *glyphShader = new util::Shader("shaders/glyph.vert","shaders/glyph.frag");
	Font::Initialize(glyphShader);
	Font::Orthographic(width, height, 1);
	Font::TypeFace f = Font::TypeFace();
	oui_err err = f.load("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", {
			.pixelHeight = 48,
			.pixelWidth = 0,
			.charCodeStart = 0,
			.charCodeLen = 0x0400, // end of greek/coptic block of freeserif
	});
	if(err) {
		printf("failed with error: %d\n", err);
		return -1;
	}

	/* Loop until the user closes the window */
	unsigned int frame = 0;
	unsigned int x = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		const wchar_t *text = L"abcdefghijklmnop\u039e\u03be";

		auto size = f.size(text);
		f.render(text, 0.0f, size.baselineAbove, glm::vec3(0.5, 0.8f, 0.2f));
		f.render(text, 0.0f, height - size.baselineBelow, glm::vec3(0.5, 0.8f, 0.2f));
		f.render(text, size.width, size.baselineAbove, glm::vec3(0.5, 0.8f, 0.2f));
		unsigned int gerr = glGetError();
		if(gerr) {
			printf("gl had error: %d\n", gerr);
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		frame++;
	}

	glfwTerminate();
	return 0;
}