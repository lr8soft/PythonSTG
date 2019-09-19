#pragma once
#ifndef _GLSL_reader_
#define _GLSL_reader_
#include<GL3/gl3w.h>
#include<iostream>
using std::string;
namespace xc_ogl {
	class ShaderReader {
	private:
		GLuint temp_program=0;
		size_t shader_count=0;
		void show_failed_info(GLuint temp_shader,string,int type);
		const GLchar* read_from_file(const char*);
	public:
		ShaderReader();
		ShaderReader(GLuint program);
		GLboolean loadFromFile(const char* path,GLenum type);
		GLboolean loadFromInfo(const char* info, GLenum type);
		GLboolean addNewShader(GLuint shader, GLenum type);
		GLboolean linkAllShader();
		GLuint getProgramHandle();
	};
}
#endif