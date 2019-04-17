//
// Created by renzhenming on 2019/4/17.
//

#ifndef OPENGLES_GROUND_H
#define OPENGLES_GROUND_H

#include "vertexbuffer.h"
#include "utils.h"

class Ground{
    VertexBuffer *vertexBuffer;
    GLuint  vbo;
public:
    void init();
};

#endif //OPENGLES_GROUND_H
