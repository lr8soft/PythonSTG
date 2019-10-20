#include<iostream>
#include "ShaderReader.h"
#include<string>
#include<fstream>
#include<sstream>
#include <glfw/glfw3.h>
using namespace std;
void xc_ogl::ShaderReader::show_failed_info(GLuint temp_shader,string sre,int type)
{
	GLsizei len;
	GLchar* log = nullptr;
	switch (type) {
	case GL_COMPILE_STATUS:
		glGetShaderiv(temp_shader, GL_INFO_LOG_LENGTH, &len);
		log = new GLchar[len + 1];
		glGetShaderInfoLog(temp_shader, len, &len, log);
		MessageBox(NULL, log, "ERROR", MB_ICONERROR);
		delete[] log;
		break;
	case GL_LINK_STATUS:
		glGetProgramiv(temp_shader, GL_INFO_LOG_LENGTH, &len);
		log = new GLchar[1024];
		glGetProgramInfoLog(temp_shader, 1024, &len, log);
		MessageBox(NULL, log, "ERROR", MB_ICONERROR);
		delete[] log;
		break;
	}
}
const GLchar * xc_ogl::ShaderReader::read_from_file(const char* path)
{
	GLchar *ret = nullptr;
	ifstream io(path);
	if (!io) {
		char *log = new char[256];
		sprintf_s(log,256,"[ERROR]Unable to open file %s",path);
		MessageBox(NULL, log, "ERROR", MB_OKCANCEL | MB_ICONERROR);
		delete[] log;
	}
	else {
		string info, temp_info;
		bool is_first =true;
		while (std::getline(io, temp_info)) {
			if (is_first)
				is_first = false;
			else
				info += '\n';
			info += temp_info;
		}
		io.close();

		ret =new GLchar[info.length()+1];
		memcpy_s(ret,info.length(),info.c_str(),info.length());
		ret[info.length()] = '\0';
	}
	return const_cast<GLchar*>(ret);
}
xc_ogl::ShaderReader::ShaderReader()
{
	temp_program = glCreateProgram();
}

xc_ogl::ShaderReader::ShaderReader(GLuint program)
{
	temp_program = program;
}

GLboolean xc_ogl::ShaderReader::loadFromFile(const char *path, GLenum type)
{
	auto *source_ptr = read_from_file(path);
	GLuint temp_shader = glCreateShader(type);
	glShaderSource(temp_shader,1,&source_ptr,0);
	glCompileShader(temp_shader);

	GLint success;
	glGetShaderiv(temp_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char error_log[512] = {'\0'};
		sprintf_s(error_log,"Shader \"%s\" compilation", path);
		show_failed_info(temp_shader,error_log, GL_COMPILE_STATUS);
	}
	else {
		glAttachShader(temp_program, temp_shader);
		shader_count++;
	}
	delete[]source_ptr;
	return success;
}

GLboolean xc_ogl::ShaderReader::loadFromInfo(const char *info,GLenum type)
{
	GLuint temp_shader=glCreateShader(type);//Create shader object
	auto source = const_cast<const GLchar*>(info);
	glShaderSource(temp_shader,1, &source,0);
	glCompileShader(temp_shader);

	GLint success;
	glGetShaderiv(temp_shader,GL_COMPILE_STATUS, &success);
	if (!success) {
		show_failed_info(temp_shader,"Shader compilation", GL_COMPILE_STATUS);
	}
	else {
		glAttachShader(temp_program, temp_shader);
		shader_count++;	
	}
	
	return success;
}

GLboolean xc_ogl::ShaderReader::addNewShader(GLuint shader, GLenum type)
{
	GLint success=GL_FALSE;
	if (glIsShader(shader)) {
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			show_failed_info(shader,"Shader compilation", GL_COMPILE_STATUS);
		}
		else {
			glAttachShader(temp_program, shader);
			shader_count++;
		}
	}
	return success;
}

GLboolean xc_ogl::ShaderReader::linkAllShader()
{
	if (shader_count>0) {
		glLinkProgram(temp_program);
		GLint success;
		glGetProgramiv(temp_program, GL_LINK_STATUS, &success);
		if (!success) {
			show_failed_info(temp_program,"Shader linking",GL_LINK_STATUS);
			return GL_FALSE;
		}
		else {
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}

GLuint xc_ogl::ShaderReader::getProgramHandle()
{
	return temp_program;
}
