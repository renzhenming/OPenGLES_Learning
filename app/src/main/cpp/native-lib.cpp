#include "ggl.h"
#include "scene.h"

static AAssetManager *assetManager = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_initAssetManager(JNIEnv *env, jclass type, jobject am) {


    assetManager = AAssetManager_fromJava(env,am);
}extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_initOpenGL(JNIEnv *env, jclass type) {

    Init();


}extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_OnViewportChanged(JNIEnv *env, jclass type, jint width,
                                                     jint height) {

    SetViewPortSize(width,height);

}extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_OpenGLNative_RenderOneFrame(JNIEnv *env, jclass type) {

    Draw();

}