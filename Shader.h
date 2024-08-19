#ifndef SHARE_H
#define SHARE_H

#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
	// the program ID
	unsigned int ID;
	// vertex, fragment ID
	unsigned int vertex, fragment;

	// constructor reads and builds the shader
	// ---------------------------------------
	Shader(const char* vertexPath, const char* fragmentPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions;
		// failbit -> 文件打开失败；badbit -> 文件操作失败； ｜ -> 按位或处理； exceptions -> 有问题抛出异常
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHDER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2. compile vertex
		vertex = glCreateShader(GL_VERTEX_SHADER);
		compileOrLinkShader(vertex, vShaderCode, vType);

		// 3. compile fragment
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		compileOrLinkShader(fragment, fShaderCode, fType);

		// 4. shader program
		ID = glCreateProgram();
		compileOrLinkShader(ID, NULL, pType);

		// 5. delete shaders; they're linked into our program and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// use/activiate the shader
	// ------------------------
	void use() {
		glUseProgram(ID);
	}
	// utility uniform functions
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setMat4(const char* name, glm::mat4 matrix) {
		int targetLoc = glGetUniformLocation(this->ID, name);
		glUniformMatrix4fv(targetLoc, 1, GL_FALSE, glm::value_ptr(matrix));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	}
	void setVec3(const char* name, glm::vec3 vec) {
		int targetLoc = glGetUniformLocation(this->ID, name);
		glUniform3f(targetLoc, vec.x, vec.y, vec.z);
	}
private:
	const std::string vType = "VERTEX";
	const std::string fType = "FRAGMENT";
	const std::string pType = "PROGRAM";
	// utility function for compilation/linking and check shader compilation/linking errors.
	// -------------------------------------------------------------------------------------
	void compileOrLinkShader(unsigned int shaderId, const char* shaderCode, std::string type) {
		if (type != pType) {
			glShaderSource(shaderId, 1, &shaderCode, NULL);
			glCompileShader(shaderId);
		}
		else {
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
		}
		// print linking errors if any
		checkCompileOrLinkErrors(shaderId, type);
	}

	// utility function for checing shader compilation/linking errors.
	// ---------------------------------------------------------------
	void checkCompileOrLinkErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[512];

		bool boolType = (type != pType);

		boolType ? glGetShaderiv(shader, GL_COMPILE_STATUS, &success) : glGetProgramiv(ID, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type <<
				(boolType ? "::COMPILATION_FAILED\n" : "::PROGRAM::LINGKING_FAILED\n") << infoLog << std::endl;
		}
	}
};

#endif
