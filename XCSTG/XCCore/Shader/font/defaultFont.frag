#version 330 core
in vec2 tex_coord;
out vec4 draw_vec4;
uniform sampler2D tex;
uniform vec4 font_color;
void main(){
    vec4 temp_frag=texture(tex,tex_coord);
    vec4 mix_frag=temp_frag*font_color;
    draw_vec4=vec4(font_color.r,font_color.g,font_color.b,temp_frag.r);
}