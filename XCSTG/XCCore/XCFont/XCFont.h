#pragma once
#ifndef _XCFONT_H_
#define _XCFONT_H_
#include <GL/glcorearb.h>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct XCCharacter {
	GLuint tbo;
	glm::ivec2 size;
	glm::ivec2 offset;
	GLuint advance;
};
struct XCUniformChar {
	std::vector<GLuint> tboGroup;
	std::vector<glm::ivec2> sizeGroup;
	std::vector<glm::ivec2> offsetGroup;
	std::vector<GLuint> advanceGroup;
};
class XCFont {
private:
	static float render_width, render_height;
	static bool have_resource_init, have_program_init, have_buffer_init;
	static GLuint vao, vbo, program;
	static std::map<GLchar,XCCharacter> XCCharacterGroup;
	std::map<std::wstring,XCUniformChar*> XCRenderStringGroup;
	void ShaderInit();
	void ResourceInit(int end);
	void BufferInit();
public:
	void FontSetWidthAndHeight(float h,float w);
	void FontASCIIInit(int endchar=128);
	void FontASCIIRender(std::string text, float x, float y, float scale, glm::vec4 color);
	void FontUnicodeInit(std::wstring text);
	void FontUnicodeRender(std::wstring text, float x, float y, float scale, glm::vec4 color);
	void FontUnicodeDirectRender(std::wstring text, float x, float y, float scale, glm::vec4 color);
};
#endif