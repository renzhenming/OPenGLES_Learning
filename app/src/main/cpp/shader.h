//
// Created by renzhenming on 2019/4/18.
//

#ifndef OPENGLES_SHADER_H
#define OPENGLES_SHADER_H

#include "ggl.h"

class Shader{
public:
    GLuint program;
    GLint positionLocation,colorLocation,texcoordLocation,normalLocation;
    GLint modelMatrixLocation,viewMatrixLocation,projectMatrixLocation;

    void Init(const char* vs,const char* fs);
    void Bind(float *M,float *V,float *P);
};

#endif //OPENGLES_SHADER_H
