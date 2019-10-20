#version 330 core
uniform mat4 view_mat;
uniform float particle_size;
layout (location=0) in vec4 display_coord;
void main(){
    vec4 render_pos=view_mat * display_coord;
    gl_Position = render_pos;
    gl_PointSize = particle_size;
}