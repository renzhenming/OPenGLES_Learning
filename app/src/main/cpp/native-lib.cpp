#include "ggl.h"
#include "scene.h"
#include "utils.h"

static AAssetManager *assetManager = NULL;

unsigned char *LoadFileContent(const char *path, int &filesize) {
    unsigned char *fileContent = NULL;
    filesize = 0;
    AAsset *asset = AAssetManager_open(assetManager, path, AASSET_MODE_UNKNOWN);
    if (asset == NULL) {
        return NULL;
    }
    filesize = AAsset_getLength(asset);
    fileContent = new unsigned char[filesize + 1];
    AAsset_read(asset, fileContent, filesize);
    //末尾增加0，更稳健
    fileContent[filesize] = '\0';
    AAsset_close(asset);
    return fileContent;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_initAssetManager(JNIEnv *env, jclass type, jobject am) {


    assetManager = AAssetManager_fromJava(env, am);
}extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_initOpenGL(JNIEnv *env, jclass type) {

    Init();


}extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_OnViewportChanged(JNIEnv *env, jclass type, jint width,
                                                     jint height) {

    SetViewPortSize(width, height);

}extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_RenderOneFrame(JNIEnv *env, jclass type) {

    Draw();

}