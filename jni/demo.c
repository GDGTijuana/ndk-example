#include <jni.h>
#include <android/log.h>
#include <GLES/gl.h>

#define MOVE 5
#define Q_SIZE 50
#define R_SIZE 200

int width;
int height;
int x = 0, y = 0, x1 = MOVE, y1 = MOVE;
int x_rect = -100;
int game_over = 0;

void draw_rect(float x, float y, float w, float h);
void clear();

void Java_com_example_demo_DemoRenderer_nativeInit( JNIEnv*  env )
{
	glEnable(GL_BLEND);
}

void
Java_com_example_demo_DemoRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
	width = (int)w;
	height = (int)h;

	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrthof(0.0f, w, 0, h, -1.0f, 1.0f);

}

void Java_com_example_demo_DemoGLSurfaceView_nativeTouch(JNIEnv* env, jobject thiz, jint x, jint y)
{
	int pos_x = (int)x;
	int pos_y = (int)y;

	if(game_over == 1)
	{
		game_over = 0;
		x = 0;
		y = 0;
	}

	if(x > width / 2 && x_rect + 200 < width)
		x_rect += 30;
	else if(x < width / 2 && x_rect > -width)
		x_rect -= 30;
}

/* Call to render the next GL frame */
void Java_com_example_demo_DemoRenderer_nativeRender(JNIEnv* env)
{
	clear();
	if(game_over == 1)
	{
		draw_rect(-200, 100, 400, 100);
		return;
	}

	if(x <= -width)
		x1 = MOVE;
	if(x >= width - Q_SIZE)
		x1 = -MOVE;
	if(y >= height - Q_SIZE)
		y1 = -MOVE;
	if(y <= -height + 100)
	{
		y1 = MOVE;
		if(x < x_rect || x > x_rect + 200)
			game_over = 1;
	}

	x += x1;
	y += y1;

	//cuadrado
	draw_rect(x, y, Q_SIZE, Q_SIZE);

	//barra
	draw_rect(x_rect, -height + 70, R_SIZE, Q_SIZE);
}

void clear()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
}

void draw_rect(float x, float y, float w, float h)
{
	x = x / width;
	y = y / height;

	w = w / width;
	h = h / height;

	float rect[] =
	{
        x, y + h,
        x + w, y + h,
        x + w, y,
        x, y
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(0.0f, 0.0f, 0.0f, 0.1f);
    glVertexPointer(2, GL_FLOAT, 0, rect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
