#include "scene.h"
#include "utils.h"
#include "ground.h"

glm::mat4 modelMatrix, viewMatrix, projectMatrix;
GLint texcoordLocation;
GLuint texture;
Ground ground;
Shader *shader;
VertexBuffer *vertexBuffer = NULL;

void Init() {
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
    vertexBuffer = new VertexBuffer;
    vertexBuffer->SetSize(3);
    vertexBuffer->SetPosition(0,-0.2f,-0.2f,-0.6f,1.0f);
    vertexBuffer->SetTexcoord(0,0.0f,0.0f);
    vertexBuffer->SetColor(0,1.0f,0.0f,0.0f,0.0f);//红色

    vertexBuffer->SetPosition(1,0.2f,-0.2f,-0.6f,1.0f);
    vertexBuffer->SetTexcoord(1,1.0f,0.0f);
    vertexBuffer->SetColor(1,0.0f,2.0f,0.0f,0.0f);//绿色

    vertexBuffer->SetPosition(2,0.0f,0.2f,-0.6f,1.0f);
    vertexBuffer->SetTexcoord(2,0.5f,1.0f);
    vertexBuffer->SetColor(2,0.0f,0.0f,1.0f,1.0f);//蓝色

    shader = new Shader;
    shader->Init("Res/test.vs","Res/test.fs");
    texcoordLocation=glGetUniformLocation(shader->program,"U_Texture");
    texture=CreateTexture2DFromBMP("Res/test2.bmp");

    ground.Init();
}

void SetViewPortSize(float width, float height) {
    glViewport(0, 0, width, height);
    projectMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ground.Draw(viewMatrix, projectMatrix);

    vertexBuffer->Bind();

    shader->Bind(glm::value_ptr(modelMatrix),glm::value_ptr(viewMatrix),glm::value_ptr(projectMatrix));
    glBindTexture(GL_TEXTURE_2D,texture);
    glUniform1i(GL_TEXTURE_2D,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    vertexBuffer->UnBind();
}