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

















