#version 330 core
uniform sampler2D tex;
uniform vec2 screen_info;
in vec2 tex_coord;
out vec4 render_color;
void main(){
    vec4 fragInfo = gl_FragCoord;
    float bigSize = float(screen_info.x > screen_info.y ? screen_info.x : screen_info.y);
    float heightAndWidth =  float(screen_info.x > screen_info.y ? screen_info.y : screen_info.x);
    if(fragInfo.x > (bigSize-heightAndWidth)/2.0 && fragInfo.x < (bigSize-heightAndWidth)/2.0+heightAndWidth ){
        discard;
    }
    render_color = texture(tex, tex_coord);
}
