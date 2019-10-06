#version 330 core
in vec2 tex_coord;
in vec4 cover_color;
out vec4 render_color;
void main(){
    render_color =  cover_color;
}
