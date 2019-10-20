#version 330 core
uniform sampler2D tex;
uniform vec4 particle_color;
out vec4 render_color;
void main(){
    vec2 tex_coord =gl_PointCoord;
    vec2 calc_coord=gl_PointCoord-vec2(0.5);
    float dist = dot(calc_coord,calc_coord);
    if(dist>=0.25)
         discard;
    else
        render_color=texture(tex,tex_coord) * particle_color;
}