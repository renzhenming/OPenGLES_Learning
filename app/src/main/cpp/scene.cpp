#include "scene.h"
#include "utils.h"

GLuint vbo, ebo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectMatrixLocation, colorLocation;
glm::mat4 modelMatrix, viewMatrix, projectMatrix;
GLint texcoordLocation, textureLocation;
GLuint texture;

void Init() {
    //glClearColor(0.1f,0.4f,0.6f,1.0f);
    float data[] = {
//            -0.2f,-0.2f,-0.6f,1.0f,
//            0.2f,-0.2f,-0.6f,1.0f,
//            0.0f,0.2f,-0.6f,1.0f
            //去掉0.6的偏移，交给modelMatrix去做
//            -0.2f,-0.2f,0.0f,1.0f,
//            0.2f,-0.2f,0.0f,1.0f,
//            0.0f,0.2f,0.0f,1.0f
            //增加颜色属性
            -0.2f, -0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.2f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //传递到显卡
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //ElementBuffer控制vbo数据的绘制顺序
    unsigned short indexes[] = {0, 1, 2};
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    int filesize = 0;
    unsigned char *vShaderCode = LoadFileContent("Res/test.vs", filesize);
    GLuint vShader = CompileShader(GL_VERTEX_SHADER, (const char *) vShaderCode);
    delete vShaderCode;
    unsigned char *fShaderCode = LoadFileContent("Res/test.fs", filesize);
    GLuint fShader = CompileShader(GL_FRAGMENT_SHADER, (const char *) fShaderCode);
    delete fShaderCode;
    program = CreateProgram(vShader, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    positionLocation = glGetAttribLocation(program, "position");
    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
    projectMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
    colorLocation = glGetAttribLocation(program, "color");

    texcoordLocation = glGetAttribLocation(program, "texcoord");
    textureLocation = glGetUniformLocation(program, "U_Texture");
    texture = CreateTexture2DFromBMP("Res/test.bmp");

    //modelmatrix做偏移
    modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);
}

void SetViewPortSize(float width, float height) {
    projectMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void Draw() {
    float frameTime = GetFrameTime();
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectMatrix));

    glBindTexture(GL_TEXTURE_2D,texture);
    glUniform1i(textureLocation,0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);

    glEnableVertexAttribArray(colorLocation);
    //sizeof(float)*8 表示两个color的起始位置相距8个点，(void*)(sizeof(float)*4)表示第一个color的位置是4
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10,
                          (void *) (sizeof(float) * 4));
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,4,GL_FLOAT,GL_FALSE, sizeof(float)*10, (void *)(sizeof(float)*8));
    //glDrawArrays(GL_TRIANGLES,0,3);
    //使用ebo绘制
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(0);
}