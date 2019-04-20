//
// Created by renzhenming on 2019/4/17.
//

#ifndef OPENGLES_VERTEXBUFFER_H
#define OPENGLES_VERTEXBUFFER_H

#include "ggl.h"

struct Vertex {
    float Position[4];
    float Color[4];
    float Texcoord[4];
    //法线
    float Normal[4];
};

class VertexBuffer {
public:
    Vertex *vertex;
    int vertexCount;
    GLuint vbo;
    void SetSize(int vertexCount);

    void SetPosition(int index, float x, float y, float z, float w = 1.0f);

    void SetColor(int index, float r, float g, float b, float a = 1.0f);

    void SetTexcoord(int index, float x, float y);

    void SetNormal(int index, float x, float y, float z);

    void Bind();

    void UnBind();

    Vertex& Get(int index);
};

#endif //OPENGLES_VERTEXBUFFER_H
