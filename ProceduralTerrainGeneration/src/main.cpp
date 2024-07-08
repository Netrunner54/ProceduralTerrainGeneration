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

CameraController3D c({ 0.0f, 300.0f, 0.0f }, glm::radians(45.0f));

int main()
{
	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	//window = glfwCreateWindow(2560, 1440, "Hello World", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	
	glfwSwapInterval(0);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{
			c.MouseMoveCallback(xpos, ypos);
			
	});

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	OpenGLErrors::Enable();

	int width = 4096, height = 4096;
	//int width = 8192, height = 8192;
	//int width = 1024, height = 1024;
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

	

	// programs
	std::string vs_src = read_file("assets/terrain_shader.vert");
	std::string fs_src = read_file("assets/terrain_shader.frag");
	std::string tcs_src = read_file("assets/terrain_shader.tesc");
	std::string tes_src = read_file("assets/terrain_shader.tese");
	OpenGLProgram terrain_rendering_program(vs_src, tcs_src, tes_src, fs_src);

	std::string cs_src = read_file("assets/terrain_generation_shader.comp");
	OpenGLProgram terrain_generation_program(cs_src);	

	std::string normal_map_from_hight_map_shader_src = read_file("assets/normal_map_from_hight_map_shader.comp");
	OpenGLProgram normal_map_from_hight_map_program(normal_map_from_hight_map_shader_src);

	std::string diffuse_map_from_height_map_src = read_file("assets/diffuse_texture_shader.comp");
	OpenGLProgram diffuse_map_from_height_map_program(diffuse_map_from_height_map_src);




	// normal texture
	// TODO: Find other solution than using RGBA32F
	OpenGLTexture2D normal_texture(width, height, OpenGLTexture2D::RGBA32F);


	OpenGLTexture2D diffuse_texture(width, height, OpenGLTexture2D::RGBA8);
	




	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_MULTISAMPLE);


	// binding textures and vertex buffer
	glBindTextureUnit(0, height_map.GetID());
	glBindImageTexture(0, height_map.GetID(), 0, 0, 0, GL_READ_WRITE, GL_R32F);
	glBindTextureUnit(1, normal_texture.GetID());
	glBindImageTexture(1, normal_texture.GetID(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindTextureUnit(2, diffuse_texture.GetID());
	glBindImageTexture(2, diffuse_texture.GetID(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glBindVertexArray(va.GetID());

	// should recalculate map variables
	bool recalculate_map = true;
	bool recalculated = false;

	// render mode variables
	bool wireframe_mode = false;
	bool wireframe_mode_changed = false;

	bool high_quality_mode = false;
	bool high_quality_mode_changed = false;

	bool normal_mode = false;
	bool normal_mode_changed = false;



	//bool normal_mode = false;

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

		// Press F to switch wireframe mode
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			if (!wireframe_mode_changed)
			{
				wireframe_mode = !wireframe_mode;
				wireframe_mode_changed = true;

				if (wireframe_mode)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
			wireframe_mode_changed = false;


		// Press N to switch normal mode
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		{
			if (!normal_mode_changed)
			{
				normal_mode = !normal_mode;
				normal_mode_changed = true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
			normal_mode_changed = false;

		// Press H to switch high quality mode
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{
			if (!high_quality_mode_changed)
			{
				high_quality_mode = !high_quality_mode;
				high_quality_mode_changed = true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
			high_quality_mode_changed = false;


		// Press R to generate new map
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			if (!recalculated)
				recalculate_map = true;
		if (recalculate_map)
		{
			recalculated = true;
			recalculate_map = false;

			// generate pseudo random terrain using perlin noise
			glUseProgram(terrain_generation_program.GetID());
			terrain_generation_program.SetInt("uImage", 0);
			terrain_generation_program.SetFloat("uSeed", (float)glfwGetTime());
			terrain_generation_program.SetInt("uPitch", 1024);
			terrain_generation_program.SetInt("uOctaves", 8);
			glDispatchCompute(width, height, 1);
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
			
			// generate normal map
			glUseProgram(normal_map_from_hight_map_program.GetID());
			normal_map_from_hight_map_program.SetInt("uHeightMap", 0);
			normal_map_from_hight_map_program.SetInt("uNormalMap", 1);
			normal_map_from_hight_map_program.SetInt2("uSize", { width, height });
			normal_map_from_hight_map_program.SetFloat("uC", 256.0f);
			glDispatchCompute(width, height, 1);
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);	

			// generate diffuse map
			glUseProgram(diffuse_map_from_height_map_program.GetID());
			diffuse_map_from_height_map_program.SetInt("uHeightMap", 0);
			diffuse_map_from_height_map_program.SetInt("uDiffuseMap", 2);
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
		glUseProgram(terrain_rendering_program.GetID());
		terrain_rendering_program.SetMat4("uVP", c.GetViewProjectionMatrix());
		terrain_rendering_program.SetMat4("uView", c.GetViewMatrix());
		terrain_rendering_program.SetFloat("uMaxHeight", 256.0f);
		terrain_rendering_program.SetBool("uHighQuality", high_quality_mode);
		terrain_rendering_program.SetBool("uNormalMode", normal_mode);
		terrain_rendering_program.SetInt("uHeightMap", 0);
		terrain_rendering_program.SetInt("uNormalMap", 1);
		terrain_rendering_program.SetInt("uDiffuseMap", 2);
		terrain_rendering_program.SetFloat3("uLightDir", { 0.3f, 1.0f, 0.5f });
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