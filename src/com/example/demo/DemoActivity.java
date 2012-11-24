package com.example.demo;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.MotionEvent;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


public class DemoActivity extends Activity
{

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		glView = new DemoGLSurfaceView(this);
        setContentView(glView);
	}

	@Override
	protected void onResume() 
	{
		super.onResume();
		glView.onResume();
	}

	@Override
	protected void onPause() 
	{
		super.onPause();
		glView.onPause();
	}

	private DemoGLSurfaceView glView;
	
	static
    {
    	System.loadLibrary("demo");
    }
}

class DemoGLSurfaceView extends GLSurfaceView 
{
    public DemoGLSurfaceView(Context context) 
    {
        super(context);
        mRenderer = new DemoRenderer();
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event) 
    {
        if (event.getAction() == MotionEvent.ACTION_DOWN) 
        {
        	int x = (int)event.getX();
            int y = (int)event.getY();
            nativeTouch(x, y);
        }
        return true;
    }

    DemoRenderer mRenderer;

    private native void nativeTouch(int x, int y);
}

class DemoRenderer implements GLSurfaceView.Renderer 
{
    public void onSurfaceCreated(GL10 gl, EGLConfig config) 
    {
        nativeInit();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) 
    {
        //gl.glViewport(0, 0, w, h);
        nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) 
    {
        nativeRender();
    }

    private static native void nativeInit();
    private static native void nativeResize(int w, int h);
    private static native void nativeRender();
    private static native void nativeDone();
}



