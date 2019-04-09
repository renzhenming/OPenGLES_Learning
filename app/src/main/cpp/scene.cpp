#include "scene.h"
void Init(){
    glClearColor(0.1f,0.4f,0.6f,1.0f);
}
void SetViewPortSize(float width,float height){
    glViewport(0,0,width,height);
}
void Draw(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}