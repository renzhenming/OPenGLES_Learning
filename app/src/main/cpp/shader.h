//
// Created by renzhenming on 2019/4/18.
//

#ifndef OPENGLES_SHADER_H
#define OPENGLES_SHADER_H

#include "ggl.h"

struct UniformTexture {
    GLint location;
    GLuint texture;

    UniformTexture() {
        location = -1;
        texture = 0;
    }
};

class Shader {
public:
    GLuint program;
    UniformTexture uniformTexture;
    GLint positionLocation, colorLocation, texcoordLocation, normalLocation;
    GLint modelMatrixLocation, viewMatrixLocation, projectMatrixLocation;

    void Init(const char *vs, const char *fs);

    void Bind(float *M, float *V, float *P);

    void SetTexture(const char *name, const char *path);
};

#endif //OPENGLES_SHADER_H
