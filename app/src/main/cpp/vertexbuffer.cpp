//
// Created by renzhenming on 2019/4/17.
//

#include "vertexbuffer.h"
#include "utils.h"

void VertexBuffer::SetSize(int vertexCount) {
    this->vertexCount = vertexCount;
    vertex = new Vertex[vertexCount];
    memset(vertex, 0, sizeof(Vertex) * vertexCount);
}

void VertexBuffer::SetPosition(int index, float x, float y, float z, float w) {
    vertex[index].Position[0] = x;
    vertex[index].Position[1] = y;
    vertex[index].Position[2] = z;
    vertex[index].Position[3] = w;
}

void VertexBuffer::SetColor(int index, float r, float g, float b, float a) {
    vertex[index].Color[0] = r;
    vertex[index].Color[1] = g;
    vertex[index].Color[2] = b;
    vertex[index].Color[3] = a;
}

void VertexBuffer::SetTexcoord(int index, float x, float y) {
    vertex[index].Texcoord[0] = x;
    vertex[index].Texcoord[1] = y;
}

void VertexBuffer::SetNormal(int index, float x, float y, float z) {
    vertex[index].Normal[0] = x;
    vertex[index].Normal[1] = y;
    vertex[index].Normal[2] = z;
    vertex[index].Normal[3] = 1.0;
}