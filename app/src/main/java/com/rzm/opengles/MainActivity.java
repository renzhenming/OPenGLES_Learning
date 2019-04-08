package com.rzm.opengles;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


class MyGLRender implements GLSurfaceView.Renderer{

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        //设置清除颜色，就是背景色，使用gl.glClear清除颜色缓冲区之后就是这个颜色
        gl.glClearColor(1f,0f,0f,0.1f);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        gl.glViewport(0,0,width,height);

    }

    @Override
    public void onDrawFrame(GL10 gl) {
        gl.glClear(gl.GL_COLOR_BUFFER_BIT);
    }
}

class MYGLSurface extends GLSurfaceView{

    private final MyGLRender render;

    public MYGLSurface(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        render = new MyGLRender();
        setRenderer(render);
    }
}

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MYGLSurface myglSurface = new MYGLSurface(getApplicationContext());
        setContentView(myglSurface);

    }


}
