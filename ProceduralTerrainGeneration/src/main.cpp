#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>

#include "OpenGLProgram.h"
#include "OpenGLVertexArray.h"
#include "OpenGLErrors.h"
#include "OpenGLTextures.h"
#include "CameraController.h"

std::string read_file(const std::string& file)
{
	std::fstream f;
	f.open(file);
	std::ostringstream src;
	src << f.rdbuf();
	std::string content = src.str();
	f.close();
	return content;
}


struct Vertex
{
	glm::vec3 position;
	glm::vec2 tex_coord;
};

CameraController3D c({ 0.0f, 100.0f, 0.0f }, 45.0f);

int main()
{
	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwSwapInterval(0);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{
			c.MouseMoveCallback(xpos, ypos);
			
	});

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	OpenGLErrors::Enable();

	int width = 4096, height = 4096;
	OpenGLTexture2D height_map(width, height, OpenGLTexture2D::ALPHA32F);

	unsigned int rez = 64;
	std::vector<Vertex> verticies;
	verticies.reserve(rez * rez * 4);
	for (unsigned int i = 0; i < rez; i++)
	{
		for (unsigned int j = 0; j < rez; j++)
		{	
			// 0, 0
			verticies.push_back(
				{ {
				(float)(-width) / 2.0f + (float)i * (float)width / (float)rez,		// x
				0.0f,																// y
				(float)(-height) / 2.0f + (float)j * (float)height / (float)rez},	// z
				{ (float)i / (float)rez,											// tex x
				(float)j / (float)rez} });											// tex y

			// 1, 0
			verticies.push_back(
				{ {
				(float)(-width) / 2.0f + (float)(i+1) * (float)width / (float)rez,		// x
				0.0f,																	// y
				(float)(-height) / 2.0f + (float)j * (float)height / (float)rez},		// z
				{ (float)(i+1) / (float)rez,											// tex x
				(float)j / (float)rez} });												// tex y

			// 0, 1
			verticies.push_back(
				{ {
				(float)(-width) / 2.0f + (float)i * (float)width / (float)rez,			// x
				0.0f,																	// y
				(float)(-height) / 2.0f + (float)(j+1) * (float)height / (float)rez},	// z
				{ (float)i / (float)rez,												// tex x
				(float)(j+1) / (float)rez} });											// tex y

			// 1, 1
			verticies.push_back(
				{ {
				(float)(-width) / 2.0f + (float)(i+1) * (float)width / (float)rez,		// x
				0.0f,																	// y
				(float)(-height) / 2.0f + (float)(j+1) * (float)height / (float)rez},	// z
				{ (float)(i+1) / (float)rez,											// tex x
				(float)(j+1) / (float)rez} });											// tex y
		}
	}



	// vertex buffer layout
	Layout layout;
	layout.AddAttribute({ Attribute::Type::VEC3 });
	layout.AddAttribute({ Attribute::Type::VEC2 });

	// vertex array
	OpenGLVertexArray va;
	va.AddLayout(layout);

	// vertex buffer
	OpenGLVertexBuffer vb(verticies.size() * sizeof(Vertex), &verticies[0], false);
	va.AddVertexBuffer(vb);

	

	// program
	std::string vs_src = read_file("assets/shader.vert");
	std::string fs_src = read_file("assets/shader.frag");
	std::string tcs_src = read_file("assets/shader.tesc");
	std::string tes_src = read_file("assets/shader.tese");
	OpenGLProgram p(vs_src, tcs_src, tes_src, fs_src);

	std::string cs_src = read_file("assets/shader.comp");
	OpenGLProgram cp(cs_src);
	



	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindTextureUnit(0, height_map.GetID());
	glBindImageTexture(1, height_map.GetID(), 0, 0, 0, GL_READ_WRITE, GL_R32F);
	glBindVertexArray(va.GetID());

	// should recalculate map variables
	bool recalculate_map = true;
	bool recalculated = false;

	// timestep variables
	float timestep = 0.0f;
	float last_time = 0.0f;
	unsigned int counter = 0;

	// movement variables
	float speed = 100.0f;

	while (!glfwWindowShouldClose(window))
	{
		// exit
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);


		// movement
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			c.MoveLeft(speed * timestep);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			c.MoveRight(speed * timestep);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			c.MoveForward(speed * timestep);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			c.MoveBackward(speed * timestep);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			c.MoveUp(speed * timestep);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			c.MoveDown(speed * timestep);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speed = 300.0f;
		else
			speed = 100.0f;


		// new map
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			if (!recalculated)
				recalculate_map = true;
		if (recalculate_map)
		{
			recalculated = true;
			recalculate_map = false;

			// runing compute shader to generate new pseudo random map
			glUseProgram(cp.GetID());
			cp.SetInt("uImage", 1);
			cp.SetFloat("uSeed", (float)glfwGetTime());
			glDispatchCompute(width, height, 1);
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
		{
			recalculate_map = false;
			recalculated = false;
		}


		// printing fps
		if (counter > 1000)
		{
			std::cout << "FPS: " << 1.0f / timestep << "\n";
			counter = 0;
		}

		// clearing framebuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// drawing terrain
		glUseProgram(p.GetID());
		p.SetMat4("uVP", c.GetViewProjectionMatrix());
		p.SetMat4("uView", c.GetViewMatrix());
		p.SetInt("uHighQuality", 1);
		p.SetInt("uHeightMap", 0);
		glDrawArrays(GL_PATCHES, 0, rez * rez * 4);

		// swapping buffers and polling events
		glfwSwapBuffers(window);
		glfwPollEvents();

		// timestep
		float current_time = glfwGetTime();
		timestep = current_time - last_time;
		last_time = glfwGetTime();
		counter++;
	}

	// terminating
	glfwTerminate();
	return 0;
}