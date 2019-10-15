#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include <iostream>
#include <string>
std::map<std::string, xc_ogl::ImageStruct> xc_ogl::ImageLoader::textureGroup;
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
	std::map<std::string, ImageStruct>::iterator item = textureGroup.find(path);
	if (item != textureGroup.end()) {
		tbo = item->second.tbo;
		width = item->second.width;
		height = item->second.height;
		channel = item->second.channel;
	}
	else {
		stbi_set_flip_vertically_on_load(true);
		void* texture_ptr = stbi_load(path, &width, &height, &channel, STBI_rgb_alpha);
		glBindTexture(texture_type, tbo);
		if (texture_ptr) {
			if (channel == 3) {//RGB -> jpeg
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//latter parameter is RGBA
				std::cout << "[INFO] Load image from " << path << " format:RGB" << std::endl;
			}
			else if (channel == 4) {//rgba -> png
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//both parameter are RGBA
				std::cout << "[INFO] Load image from " << path << " format:RGBA" << std::endl;
			}
			glGenerateMipmap(texture_type);
			have_release = false;
		}
		else {
			std::cout << "[ERROR] Can\'t load image " << path << " !" << std::endl;
		}
		glBindTexture(texture_type, 0);//Bind nothing.
		stbi_image_free(texture_ptr);

		ImageStruct newImage;
		newImage.channel = channel;
		newImage.height = height;
		newImage.width = width;
		newImage.tbo = tbo;
		textureGroup.insert(std::make_pair(path, newImage));
	}
}

int xc_ogl::ImageLoader::getTextureWidth()
{
	return width;
}

int xc_ogl::ImageLoader::getTextureHeight()
{
	return height;
}

void * xc_ogl::ImageLoader::getTexturePointer(const char* tex, int &width, int &height, int &channels)
{
	stbi_set_flip_vertically_on_load(true);
	void* texture_ptr = stbi_load(tex, &width, &height, &channels, STBI_rgb_alpha);
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

