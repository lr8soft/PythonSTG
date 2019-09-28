#version 330 core
uniform vec4 color;
out vec4 render_color;
void main(){
    render_color = color;
}
