#version 330 core

uniform mat4 mvp_mat;
uniform vec4 diffuse_color;

layout(location=0) in vec4 draw_vertex;
layout(location=1) in vec2 tex_pos;

out vec2 tex_coord;
out vec4 cover_color;
void main(){
    gl_Position = mvp_mat * vec4(draw_vertex.xy,0.0,1.0);
    tex_coord = tex_pos;
    cover_color = diffuse_color;
}