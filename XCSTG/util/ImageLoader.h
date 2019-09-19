#pragma once
#ifndef _image_loader_
#define _image_loader_
#include "stb_image.h"
#include <gl/glcorearb.h>
namespace xc_ogl {
	class ImageLoader
	{
	private:
		GLuint tbo=-1; GLenum texture_type;
		int width, height, channel;
		bool have_release;
	public:
		ImageLoader();
		ImageLoader(GLenum type, GLuint itbo);
		~ImageLoader();
		void Release();
		void loadTextureFromFile(const char* path);
		static void* getTexturePointer(const char* tex,int &width,int &height,int &channels);
		GLuint getTextureBufferObjectHandle();
	};
}

#endif 
