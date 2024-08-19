#ifndef GLFWWINDOW_H
#define GLGWWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// glfw: whenenver the window size changed (by OS or user resize) this callback function executes
// ----------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays
}

class GLFWWindow {

public:
	GLFWwindow* window;

	GLFWWindow() {
		// initialize glfw and configure
		// -----------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// create window object, width: 800, height: 600, title: "LearnOpenGL"
		// -------------------------------------------------------------------
		window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
		if (window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			// terminate GLFW
			glfwTerminate();
			// return -1;
			exit(1);
		}
		// 将窗口window设置为当前县城的主上下文，即捕获当前窗口，准备对当前窗口进行画图；
		// ---------------------------——------------------------------------
		glfwMakeContextCurrent(window);
		// register callback function
		// --------------------------
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			// 加载函数地址失败
			// 打印错误信息
			std::cout << "Failed to initialize GLAD" << std::endl;
			// return -1;
			exit(-1);
		}
	}

	void processInput() {
		// not press ESC: glfwGetKey(window, GLFW_KEY_EXCAPE) -> return GLFW_RELEASE
		// -------------------------------------------------------------------------
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
};

#endif