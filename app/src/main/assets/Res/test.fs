#ifdef GL_ES
precision mediump float;
#endif
varying vec4 V_Color;
varying vec2 V_Texcoord;
uniform sampler2D U_Texture;

void main(){
    //gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    //将顶点坐标传过来的颜色绘制出来
    //gl_FragColor = V_Color;
    gl_FragColor = V_Color*texture2D(U_Texture,V_Texcoord);
}