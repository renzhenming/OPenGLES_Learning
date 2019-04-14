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

unsigned char * DecodeBMP(unsigned char *bmpFileData,int &width,int &height);

GLuint CreateTexture2D(unsigned char* pixelData,int width,int height,GLenum type);

GLuint CreateTexture2DFromBMP(const char *bmpPath);

#endif //OPENGLES_UTILS_H
