//
// Created by renzhenming on 2019/4/17.
//

#include "ground.h"

void Ground::init() {
    vertexBuffer = new VertexBuffer();
    vertexBuffer->SetSize(1600);

    for (int z = 0; z < 20; ++z) {
        float zStart=100.0f-z*10.0f;
        for (int x = 0; x < 20; ++x) {
            int offset=(x+z*20)*4;
            float xStart=x*10.0f-100.0f;
            vertexBuffer->SetPosition(offset,xStart,-1.0f,zStart,1.0f);
            vertexBuffer->SetPosition(offset+1,xStart+10.0f,-1.0f,zStart,1.0f);
            vertexBuffer->SetPosition(offset+2,xStart,-1.0f,zStart-10.0f,1.0f);
            vertexBuffer->SetPosition(offset+3,xStart+10.0f,-1.0f,zStart-10.0f,1.0f);
            float r=0.8f,g=0.8f,b=0.8f,a=1.0f;
            if((z%2)^(x%2)){
                r=0.1f;
                g=0.1f;
                b=0.1f;
                a=1.0f;
            }
            vertexBuffer->SetColor(offset,r,g,b,a);
            vertexBuffer->SetColor(offset+1,r,g,b,a);
            vertexBuffer->SetColor(offset+2,r,g,b,a);
            vertexBuffer->SetColor(offset+3,r,g,b,a);
        }
    }
    vbo=CreateBufferObject(GL_ARRAY_BUFFER,sizeof(Vertex)*vertexBuffer->vertexCount,GL_STATIC_DRAW,vertexBuffer->vertex);
}