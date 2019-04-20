#include "scene.h"
#include "utils.h"
#include "ground.h"

GLuint vbo, ebo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectMatrixLocation, colorLocation;
glm::mat4 modelMatrix, viewMatrix, projectMatrix;
GLint texcoordLocation, textureLocation;
GLuint texture;
Ground ground;

void Init() {
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
//    float data[] = {
//            //增加颜色属性
//            -0.2f, -0.2f, -0.6f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//            0.2f, -0.2f, -0.6f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//            0.0f, 0.2f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
//    };
//
//    //ElementBuffer控制vbo数据的绘制顺序
//    unsigned short indexes[] = {0, 1, 2};
//
//    vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(float) * 30, GL_STATIC_DRAW, data);
//    ebo = CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, GL_STATIC_DRAW,
//                             indexes);
//
//    int filesize = 0;
//    unsigned char *vShaderCode = LoadFileContent("Res/test.vs", filesize);
//    GLuint vShader = CompileShader(GL_VERTEX_SHADER, (const char *) vShaderCode);
//    delete vShaderCode;
//    unsigned char *fShaderCode = LoadFileContent("Res/test.fs", filesize);
//    GLuint fShader = CompileShader(GL_FRAGMENT_SHADER, (const char *) fShaderCode);
//    delete fShaderCode;
//    program = CreateProgram(vShader, fShader);
//    glDeleteShader(vShader);
//    glDeleteShader(fShader);
//
//    positionLocation = glGetAttribLocation(program, "position");
//    colorLocation = glGetAttribLocation(program, "color");
//    texcoordLocation = glGetAttribLocation(program, "texcoord");
//
//    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
//    viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
//    projectMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
//
//    textureLocation = glGetUniformLocation(program, "U_Texture");
//    texture = CreateTexture2DFromBMP("Res/test2.bmp");
    ground.Init();
}

void SetViewPortSize(float width, float height) {
    glViewport(0, 0, width, height);
    projectMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ground.Draw(viewMatrix, projectMatrix);
}