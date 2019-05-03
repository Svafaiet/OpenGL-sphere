#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include<shader.h>
#include"stb_image.h"
#include<iostream>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>

using namespace std;

void framebuffer_callback_size(GLFWwindow* window, int width , int height);
void processInput(GLFWwindow* window);

/*float colors[] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f
}*/

float vertices[] = {
	//coordinates			//colors
	-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f, 1.0f,//red
	-0.5f,  0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 1.0f,//green
	 0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f, 1.0f,//blue
	-0.5f,  0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 1.0f,//green
	 0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f, 1.0f,//blue
	 0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 0.0f, 1.0f//black
};

glm::mat4 transform = glm::mat4(1.0f);
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Workshop", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD"<<endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_callback_size);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	//aColor
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (3*sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader myShader("shader.vert", "shader.frag");
	myShader.use();
	//Main Loop
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		
		//Drawing
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		transform = glm::rotate(transform, (float)glfwGetTime()/100, glm::vec3(0.0f, 0.0f, 1.0f));
		myShader.setMat4("trans", transform);
		myShader.setMat4("model", model);
		myShader.setMat4("view", view);
		myShader.setMat4("projection", projection);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_callback_size(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}