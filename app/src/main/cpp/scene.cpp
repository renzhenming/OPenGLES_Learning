#include "scene.h"
#include "utils.h"

GLuint vbo;
GLuint program;
GLint positionLocation,modelMatrixLocation,viewMatrixLocation,projectMatrixLocation;
glm::mat4 modelMatrix,viewMatrix,projectMatrix;

void Init(){
    //glClearColor(0.1f,0.4f,0.6f,1.0f);
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

    int filesize = 0;
    unsigned char*vShaderCode = LoadFileContent("Res/test.vs",filesize);
    GLuint vShader = CompileShader(GL_VERTEX_SHADER,(const char*)vShaderCode);
    delete vShaderCode;
    unsigned char* fShaderCode = LoadFileContent("Res/test.fs",filesize);
    GLuint fShader = CompileShader(GL_FRAGMENT_SHADER,(const char*)fShaderCode);
    delete fShaderCode;
    program = CreateProgram(vShader,fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    positionLocation = glGetAttribLocation(program,"position");
    modelMatrixLocation = glGetUniformLocation(program,"ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program,"ViewMatrix");
    projectMatrixLocation = glGetUniformLocation(program,"ProjectionMatrix");
}
void SetViewPortSize(float width,float height){
    projectMatrix = glm::perspective(60.0f,width/height,0.1f,1000.0f);
}
void Draw(){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectMatrixLocation,1,GL_FALSE,glm::value_ptr(projectMatrix));

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation,4,GL_FLOAT, GL_FALSE,sizeof(float)*4,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glUseProgram(0);
}