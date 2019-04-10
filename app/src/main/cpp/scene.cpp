#include "scene.h"
GLuint vbo;
void Init(){
    glClearColor(0.1f,0.4f,0.6f,1.0f);
    float data[] = {
            -0.2f,-0.2f,-0.6f,1.0f,
            0.2f,-0.2f,-0.6f,1.0f,
            0.0f,0.2f,-0.6f,1.0f
    };
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    //传递到显卡
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12,data,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void SetViewPortSize(float width,float height){
    glViewport(0,0,width,height);
}
void Draw(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}