//
// Created by renzhenming on 2019/4/10.
//

#ifndef OPENGLES_UTILS_H
#define OPENGLES_UTILS_H

#include "ggl.h"

unsigned char* LoadFileContent(const char* path, int &fliesize);

GLuint CompileShader(GLenum shaderType,const char* shaderCode);

GLuint CreateProgram(GLuint vsShader,GLuint fsShader);

float GetFrameTime();

#endif //OPENGLES_UTILS_H
