#pragma once
#ifndef _GLWRAPPER_H_
#define _GLWRAPPER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



class Model {
public:
	Model();
	~Model();
	void loadVertexData(float* vertices, int length);
	void loadElementData(unsigned int* indices, int length);
	void load(float* vertices, int L1, unsigned int* indices, int L2);
	GLuint getVAO();

private:
	GLuint vao;
	std::vector<GLuint> vbos;
	GLuint ebo;
};

class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void use();
	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

GLFWwindow* GLInit(unsigned int width, unsigned int height, std::string name);

void GLTerminate();

void processInput(GLFWwindow* window);


#endif // !_GLWRAPPER_H_
