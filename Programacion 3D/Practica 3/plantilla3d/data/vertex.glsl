uniform mat4 mvp;
attribute vec3 vpos;
attribute vec2 vtex;
varying vec2 ftex;
void main() 
{
gl_Position = mvp * vec4(vpos, 1);
ftex = vtex;
}