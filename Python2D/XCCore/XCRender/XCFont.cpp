#include "XCFont.h"
#include "../../util/ImageLoader.h"
#include "../../util/ShaderReader.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
std::map<GLchar, XCCharacter> XCFont::XCCharacterGroup;
float XCFont::render_height = 730.0f;
float XCFont::render_width = 720.0f;
bool XCFont::have_resource_init = false;
bool XCFont::have_buffer_init = false;
bool XCFont::have_program_init = false;
GLuint XCFont::program;
GLuint XCFont::vao;
GLuint XCFont::vbo;
using namespace xc_ogl;
void XCFont::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader FontShader;
		FontShader.loadFromFile("assets/Shader/Font/defaultFont.vert", GL_VERTEX_SHADER);
		FontShader.loadFromFile("assets/Shader/Font/defaultFont.frag", GL_FRAGMENT_SHADER);
		FontShader.linkAllShader();
		program = FontShader.getProgramHandle();
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		have_program_init = true;
	}
}
void XCFont::ResourceInit(int end)
{
	if (!have_resource_init) {
		////////////////////////字符纹理加载Start/////////////////////////////////////////
		FT_Library freetype;
		FT_Face fontFace;
		if (FT_Init_FreeType(&freetype)) {
			MessageBox(0, "FreeType加载失败！", "ERROR", MB_ICONERROR); return;
		}
		if (FT_New_Face(freetype, "assets/Font/SourceHanSansCN-Normal.otf", 0, &fontFace)) {
			MessageBox(0, "无法加载字体/assets/Font/SourceHanSansCN-Normal.otf！", "ERROR", MB_ICONERROR); return;
		}
		FT_Set_Pixel_Sizes(fontFace, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//像素之间紧密对齐
		for (GLubyte c = 0; c < end; c++)
		{
			if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
			{
#ifdef _DEBUG
				char* log = new char[end];
				sprintf_s(log, 64, "无法加载字体 %c!", c);
				MessageBox(0, log, "ERROR", MB_ICONERROR);
				delete[] log;
#endif
				continue;
			}
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				fontFace->glyph->bitmap.width,
				fontFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				fontFace->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			XCCharacter character = {
				texture,
				glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
				glm::ivec2(fontFace->glyph->bitmap_left,  fontFace->glyph->bitmap_top),
				fontFace->glyph->advance.x
			};
			XCCharacterGroup.insert(std::pair<GLchar, XCCharacter>(c, character));
		}
		FT_Done_Face(fontFace);
		FT_Done_FreeType(freetype);
		////////////////////////字符纹理加载Finish/////////////////////////////////////////
		have_resource_init = true;
	}
}
void XCFont::BufferInit()
{
	if (!have_buffer_init)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		////////////////////Char start////////////
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		/*绘制两三角形六个顶点，每个顶点有vec2 tex_pos与vec2 draw_pos*/
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
		auto draw_vertex_loc = glGetAttribLocation(program, "draw_vertex");
		glVertexAttribPointer(draw_vertex_loc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(draw_vertex_loc);
		glBindVertexArray(0);
		have_buffer_init = true;
	}

}
void XCFont::FontSetWidthAndHeight(float h, float w)
{
	render_width = w;
	render_height = h;
}
void XCFont::FontASCIIInit(int endchar)
{
	ShaderInit();
	ResourceInit(endchar);
	BufferInit();
}

void XCFont::FontASCIIRender(std::string text, float x, float y, float scale, glm::vec4 color)
{
	x *= render_width;
	y *= render_height;
	glUseProgram(program);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (auto iter = text.begin(); iter != text.end(); iter++) {
		XCCharacter CharacterTemp = XCCharacterGroup[*iter];
		float xpos = x + CharacterTemp.offset.x * scale;
		float ypos = y - (CharacterTemp.size.y - CharacterTemp.offset.y) * scale;

		float w = CharacterTemp.size.x * scale;
		float h = CharacterTemp.size.y * scale;
		GLfloat draw_vertex[6][4] = {//似乎进行了上下翻转
		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos,     ypos,       0.0, 1.0 },
		   { xpos + w, ypos,       1.0, 1.0 },

		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos + w, ypos,       1.0, 1.0 },
		   { xpos + w, ypos + h,   1.0, 0.0 }
		};
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, CharacterTemp.tbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(draw_vertex), draw_vertex);
		glm::mat4 projection = glm::ortho(0.0f, render_width, 0.0f, render_height);
		auto convert_mat_loc = glGetUniformLocation(program, "convert_mat");
		auto font_color_loc = glGetUniformLocation(program, "font_color");
		glUniform4fv(font_color_loc, 1, glm::value_ptr(color));
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (CharacterTemp.advance >> 6) * scale;
	}
	glUseProgram(0);
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void XCFont::FontUnicodeInit(std::wstring text)
{
	if (XCRenderStringGroup.find(text) != XCRenderStringGroup.end()) return;//wstring existed.
	ShaderInit();
	BufferInit();

	FT_Library freetype;
	FT_Face fontFace;
	if (FT_Init_FreeType(&freetype)) {
		MessageBox(0, "FreeType加载失败！", "ERROR", MB_ICONERROR); return;
	}
	if (FT_New_Face(freetype, "assets/Font/SourceHanSansCN-Normal.otf", 0, &fontFace)) {
		MessageBox(0, "无法加载字体/assets/Font/SourceHanSansCN-Normal.otf！", "ERROR", MB_ICONERROR); return;
	}
	FT_Set_Pixel_Sizes(fontFace, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	XCUniformChar *tempChar = new XCUniformChar;
	for (int i = 0; i < text.length(); i++) {
		if (FT_Load_Glyph(fontFace, FT_Get_Char_Index(fontFace, text[i]), FT_LOAD_DEFAULT))//FT_Load_Char(fontFace, load_char, FT_LOAD_RENDER)
		{
#ifdef _DEBUG
			char* log = new char[128];
			sprintf_s(log, 64, "无法加载字体%wc!", text[i]);
			MessageBox(0, log, "ERROR", MB_ICONERROR);
			delete[] log;
#endif
			continue;
		}
		if (FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL)) {
#ifdef _DEBUG
			char* log = new char[128];
			sprintf_s(log, 64, "无法加载字体!");
			MessageBox(0, log, "ERROR", MB_ICONERROR);
			delete[] log;
#endif
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			fontFace->glyph->bitmap.width,
			fontFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			fontFace->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		tempChar->tboGroup.push_back(texture);
		tempChar->sizeGroup.push_back(glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows));
		tempChar->offsetGroup.push_back(glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top));
		tempChar->advanceGroup.push_back(fontFace->glyph->advance.x);
	}
	FT_Done_Face(fontFace);
	FT_Done_FreeType(freetype);
	XCRenderStringGroup.insert(std::pair<std::wstring, XCUniformChar*>(text, tempChar));
}

void XCFont::FontUnicodeRender(std::wstring text, float x, float y, float scale, glm::vec4 color)
{
	x *= render_width;
	y *= render_height;
	glUseProgram(program);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	XCUniformChar *CharacterTemp = XCRenderStringGroup[text];
	if (CharacterTemp == nullptr) return;
	for (int i = 0; i < CharacterTemp->tboGroup.size(); i++) {
		float xpos = x + CharacterTemp->offsetGroup[i].x * scale;
		float ypos = y - (CharacterTemp->sizeGroup[i].y - CharacterTemp->offsetGroup[i].y) * scale;

		float w = CharacterTemp->sizeGroup[i].x * scale;
		float h = CharacterTemp->sizeGroup[i].y * scale;
		GLfloat draw_vertex[6][4] = {
		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos,     ypos,       0.0, 1.0 },
		   { xpos + w, ypos,       1.0, 1.0 },

		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos + w, ypos,       1.0, 1.0 },
		   { xpos + w, ypos + h,   1.0, 0.0 }
		};
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, CharacterTemp->tboGroup[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(draw_vertex), draw_vertex);
		glm::mat4 projection = glm::ortho(0.0f, render_width, 0.0f, render_height);
		auto convert_mat_loc = glGetUniformLocation(program, "convert_mat");
		auto font_color_loc = glGetUniformLocation(program, "font_color");
		glUniform4fv(font_color_loc, 1, glm::value_ptr(color));
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (CharacterTemp->advanceGroup[i] >> 6) * scale;
	}
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void XCFont::FontUnicodeDirectRender(std::wstring text, float x, float y, float scale, glm::vec4 color)
{
	FontUnicodeInit(text);
	FontUnicodeRender(text, x, y, scale, color);
}
