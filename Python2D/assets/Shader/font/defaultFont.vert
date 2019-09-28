#version 330 core
uniform mat4 convert_mat;
layout (location=0) in vec4 draw_vertex;//position vec2,texture vec2
out vec2 tex_coord;
void main(){
    gl_Position=convert_mat*vec4(draw_vertex.xy,0.0,1.0);
    tex_coord=vec2(draw_vertex.zw);
}