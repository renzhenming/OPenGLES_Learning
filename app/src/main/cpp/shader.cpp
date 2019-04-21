//
// Created by renzhenming on 2019/4/18.
//

#include "shader.h"
#include "utils.h"
#include "vertexbuffer.h"

void Shader::Init(const char *vs, const char *fs) {
    int filesize = 0;
    unsigned char *shaderCode = LoadFileContent(vs, filesize);
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (const char *) shaderCode);
    delete[]shaderCode;
    shaderCode = LoadFileContent(fs, filesize);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (const char *) shaderCode);
    delete[]shaderCode;
    program = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

    positionLocation = glGetAttribLocation(program, "position");
    colorLocation = glGetAttribLocation(program, "color");
    texcoordLocation = glGetAttribLocation(program, "texcoord");
    normalLocation = glGetAttribLocation(program, "normal");
    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
    projectMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
}

void Shader::SetTexture(const char *name, const char *path) {
    //使用find，返回的是被查找元素的位置，没有则返回map.end()
    auto iterator = uniformTextures.find(name);
    if(iterator == uniformTextures.end()){
        GLint location = glGetUniformLocation(program,name);
        if(location != -1){
            UniformTexture *texture = new UniformTexture;
            texture->location = location;
            texture->texture = CreateTexture2DFromBMP(path);
            uniformTextures.insert(std::pair<std::string,UniformTexture*>(name,texture));
        }
    }else{
        //first会得到key，
        //second会得到value。
        glDeleteTextures(1,&iterator->second->texture);
        iterator->second->texture = CreateTexture2DFromBMP(path);
    }
}

void Shader::Bind(float *M, float *V, float *P) {
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, M);
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, V);
    glUniformMatrix4fv(projectMatrixLocation, 1, GL_FALSE, P);

    int index = 0;
    for(auto i = uniformTextures.begin();i != uniformTextures.end();i++){
        glActiveTexture(GL_TEXTURE0+index);
        glBindTexture(GL_TEXTURE_2D,i->second->texture);
        glUniform1i(i->second->location,index++);
    }

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *) (sizeof(float) * 4));

    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *) (sizeof(float) * 8));

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *) (sizeof(float) * 12));
}