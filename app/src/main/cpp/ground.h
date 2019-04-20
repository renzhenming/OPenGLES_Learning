//
// Created by renzhenming on 2019/4/17.
//

#ifndef OPENGLES_GROUND_H
#define OPENGLES_GROUND_H

#include "vertexbuffer.h"
#include "utils.h"
#include "shader.h"

class Ground{
    VertexBuffer *vertexBuffer;
    GLuint  vbo;
    Shader *shader;
    glm::mat4 modelMatrix;
public:
    void Init();
    void Draw(glm::mat4 &viewMatrix,glm::mat4 &projectMatrix);
};

#endif //OPENGLES_GROUND_H
