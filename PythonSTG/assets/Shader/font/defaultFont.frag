#version 330 core
in vec2 tex_coord;
out vec4 draw_vec4;
uniform sampler2D tex;
uniform vec4 font_color;
void main(){
    vec4 sampled =vec4(1.0, 1.0, 1.0, texture(tex, tex_coord).r);//texture(tex,tex_coord);
    draw_vec4 = font_color * sampled;
}