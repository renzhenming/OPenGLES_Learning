//
// Created by renzhenming on 2019/4/22.
//

#pragma once

#include "vertexbuffer.h"
#include "shader.h"

class Model {
public:
    VertexBuffer *vertexBuffer;
    Shader *shader;
    float *modelMatrix;

    Model();

    void Init(const char *modelPath);

    void Draw(float *viewMatrix, float *projectionMatrix);

    void SetPosition(float x, float y, float z);
};