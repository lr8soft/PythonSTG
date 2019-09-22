#version 330 core
uniform sampler2D tex;
in vec2 tex_coord;
out vec4 render_color;
void main(){
    render_color = texture(tex, tex_coord);
}
