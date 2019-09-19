#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include <iostream>
#include <windows.h>
xc_ogl::ImageLoader::ImageLoader()
{
	texture_type = GL_TEXTURE_2D;
	have_release = true;

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
}

xc_ogl::ImageLoader::ImageLoader(GLenum type,GLuint itbo)
{
	texture_type = type;
	have_release = true;
	tbo = itbo;
	glBindTexture(texture_type, tbo);
}


xc_ogl::ImageLoader::~ImageLoader()
{
	if (!have_release)
		Release();
}

void xc_ogl::ImageLoader::Release()
{
	if (!have_release) {
		//stbi_image_free(texture_ptr);
		have_release = true;
	}		
}

void xc_ogl::ImageLoader::loadTextureFromFile(const char * path)
{
	stbi_set_flip_vertically_on_load(true);
	void* texture_ptr = stbi_load(path, &width, &height, &channel, STBI_rgb_alpha);
	glBindTexture(texture_type, tbo);
	if (texture_ptr) {
		if (channel == 3){//三通道rgb 适用于jpg图像
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//后面一个是RGBA
			std::cout << path<< " RGB" << std::endl;
		}
		else if (channel == 4){//四通道rgba 适用于png图像
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//注意，两个都是RGBA
			std::cout << path << " RGBA" << std::endl;
		}
		glGenerateMipmap(texture_type);
		have_release = false;
	}
	else {
		char *str = new char[256];
		sprintf_s(str, 256, "[ERROR]无法加载图像 %s",path);
		MessageBox(NULL, str,"XCSTG ERROR", MB_OKCANCEL|MB_ICONERROR);
		delete[] str;
	}
	glBindTexture(texture_type, 0);//Bind nothing.
	stbi_image_free(texture_ptr);
}

void * xc_ogl::ImageLoader::getTexturePointer(const char* tex, int &width, int &height, int &channels)
{
	stbi_set_flip_vertically_on_load(true);
	void* texture_ptr = stbi_load(tex, &width, &height, &channels, 0);
	if (texture_ptr) {
		return texture_ptr;
	}
	else {
		return nullptr;
	}
}

GLuint xc_ogl::ImageLoader::getTextureBufferObjectHandle()
{
	return tbo;
}
