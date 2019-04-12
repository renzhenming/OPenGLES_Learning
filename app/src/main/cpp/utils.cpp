//
// Created by renzhenming on 2019/4/10.
//

#include "utils.h"

GLuint CompileShader(GLenum shaderType, const char *shaderCode) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE) {
        char log[1024] = {0};
        GLsizei logLen = 0;
        glGetShaderInfoLog(shader, 1024, &logLen, log);
        printf("compile shader failed log:%s", log);
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}


GLuint CreateProgram(GLuint vsShader, GLuint fsShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vsShader);
    glAttachShader(program, fsShader);
    glLinkProgram(program);
    glDetachShader(program, vsShader);
    glDetachShader(program, fsShader);
    GLint nResult;
    glGetProgramiv(program, GL_LINK_STATUS, &nResult);
    if (nResult == GL_FALSE) {
        GLsizei writed = 0;
        char log[1024] = {0};
        glGetProgramInfoLog(program, 1024, &writed, log);
        printf("create gpu program failed,error:%s", log);
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}

unsigned char *DecodeBMP(unsigned char *bmpFileData, int &width, int &height) {
    if (0x4D42 == *((unsigned short *) bmpFileData)) {
        //表示这是一个位图
        int pixelDataOffset = *((int *) (bmpFileData + 10));
        width = *((int *) (bmpFileData + 18));
        height = *((int *) (bmpFileData + 22));
        unsigned char *pixelData = bmpFileData + pixelDataOffset;
        for (int i = 0; i < width * height * 3; i += 3) {
            unsigned char temp = pixelData[i];
            pixelData[i] = pixelData[i + 2];
            pixelData[i + 2] = temp;
        }
        return pixelData;
    }
    return NULL;
}

















