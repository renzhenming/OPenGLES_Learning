package com.rzm.opengles;

import android.content.res.AssetManager;

public class OpenGLNative {

    static {
        System.loadLibrary("native-lib");
    }

    public static native void initAssetManager(AssetManager am);

    public static native void initOpenGL();

    public static native void OnViewportChanged(int width,int height);

    public static native void RenderOneFrame();
}
