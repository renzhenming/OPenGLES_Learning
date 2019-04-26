//
// Created by renzhenming on 2019/4/22.
//

#include "model.h"
#include "utils.h"

Model::Model() {

}

void Model::Init(const char *modelPath) {
    struct FloatData {
        float v[3];
    };
    struct VertexDefine {
        int posIndex;
        int texcoordIndex;
        int normalIndex;
    };
    int fileSize = 0;
    unsigned char *fileContent = LoadFileContent(modelPath, fileSize);
    if (fileContent == NULL) {
        return;
    }
    std::vector<FloatData> positions, texcoords, normals;
    std::vector<VertexDefine> vertexes;
    std::string temp;
    std::stringstream ssFileContent((char *) fileContent);
    char onLine[256];
    while (!ssFileContent.eof()) {
        memset(onLine, 0, 256);
        ssFileContent.getline(onLine, 256);
        if (strlen(onLine) > 0) {
            if (onLine[0] == 'v') {
                std::stringstream ssOneLine(onLine);
                if (onLine[1] == 't') {
                    //把模型数据第一个开头的v或者f拿走
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    //存储纹理数据
                    texcoords.push_back(floatData);
                    printf("texcoord:%s\n", onLine);
                } else if (onLine[1] == 'n') {
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    ssOneLine >> floatData.v[2];
                    //存储法线数据
                    normals.push_back(floatData);
                    printf("normal:%s\n", onLine);
                } else {
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    ssOneLine >> floatData.v[2];
                    //存储顶点数据
                    positions.push_back(floatData);
                    printf("position:%s\n", onLine);
                }
            } else if (onLine[0] == 'f') {
                std::stringstream ssOneLine(onLine);
                ssOneLine >> temp;
                std::string vertexStr;
                for (int i = 0; i < 3; i++) {
                    //转移到字符串中
                    ssOneLine >> vertexStr;
                    size_t pos = vertexStr.find_first_of('/');
                    std::string posIndexStr = vertexStr.substr(0, pos);

                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);

                    std::string normalIndexStr = vertexStr.substr(pos2 + 1,
                                                                  vertexStr.length() - 1 - pos2);

                    VertexDefine vd;
                    vd.posIndex = atoi(posIndexStr.c_str());
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
                    vd.normalIndex = atoi(normalIndexStr.c_str());

                    vertexes.push_back(vd);

                }

                printf("draw command:%s\n", onLine);
            }
        }
    }
    delete fileContent;
    int vertextCount = vertexes.size();
    vertexBuffer = new VertexBuffer;
    vertexBuffer->SetSize(vertextCount);
    for (int i = 0; i < vertextCount; ++i) {
        float *temp = positions[vertexes[i].posIndex - 1].v;
        vertexBuffer->SetPosition(i, temp[0], temp[1], temp[2]);

        temp = texcoords[vertexes[i].texcoordIndex - 1].v;
        vertexBuffer->SetTexcoord(i, temp[0], temp[1]);

        temp = normals[vertexes[i].normalIndex - 1].v;
        vertexBuffer->SetNormal(i, temp[0], temp[1], temp[2]);
    }
    shader = new Shader;
    shader->Init("Res/model.vs", "Res/model.fs");
}

void Model::Draw(float *viewMatrix, float *projectionMatrix) {
    glEnable(GL_DEPTH_TEST);
    vertexBuffer->Bind();
    shader->Bind(modelMatrix, viewMatrix, projectionMatrix);
    glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->vertexCount);
    vertexBuffer->UnBind();
}

void Model::SetPosition(float x, float y, float z) {
    modelMatrix = (float *) glm::value_ptr(glm::translate(x, y, z));
}