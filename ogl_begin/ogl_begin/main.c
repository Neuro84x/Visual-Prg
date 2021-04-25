#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd, hwnd2;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	float theta = 0.0f;

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* create main window */
	hwnd = CreateWindowEx(0,
		"GLSample",
		"WiFi",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1000,
		1000,
		NULL,
		NULL,
		hInstance,
		NULL);

	hwnd2 = CreateWindowEx(0,
		"GLSample",
		"Settings",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	ShowWindow(hwnd2, nCmdShow);

	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);

	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* OpenGL animation code goes here */

			glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glPushMatrix();
			//glRotatef(theta, 0.0f, 0.0f, 1.0f);

			glBegin(GL_TRIANGLES);

			static float x = -1, y = 1, routerX = 1, routerY = 0;
			const float ROUT_SIZE = 0.1;
			float step = 0.001;
			float POWER = 0, // уровень сигнала в точке 
				d = 0,	 // расстояние до точки
				k = 10;  // для перевода в метры

			for (int i = 0; i < 2000; ++i) {
				for (int j = 0; j < 2000; ++j) {

					d = sqrt(pow((x - routerX) * k, 2) + pow((y - routerY) * k, 2));
					POWER = 25 - (26 * log(5) + 22.7 + 36 * log(d));

					if (POWER >= -61) {
						//red
						glColor3f(1, 0, 0);
						glVertex2f(x, y);
						glVertex2f(x + step, y);
						glVertex2f(x, y - step);
						glVertex2f(x + step, y);
						glVertex2f(x + step, y - step);
						glVertex2f(x, y - step);
					}
					else if (POWER >= -75) {
						//orange
						glColor3f(1, 0.7, 0.1);
						glVertex2f(x, y);
						glVertex2f(x + step, y);
						glVertex2f(x, y - step);
						glVertex2f(x + step, y);
						glVertex2f(x + step, y - step);
						glVertex2f(x, y - step);
					}
					else if (POWER >= -90) {
						//yellow
						glColor3f(1, 1, 0.1);
						glVertex2f(x, y);
						glVertex2f(x + step, y);
						glVertex2f(x, y - step);
						glVertex2f(x + step, y);
						glVertex2f(x + step, y - step);
						glVertex2f(x, y - step);
					}
					else if (POWER >= -105) {
						//green
						glColor3f(0, 1, 0);
						glVertex2f(x, y);
						glVertex2f(x + step, y);
						glVertex2f(x, y - step);
						glVertex2f(x + step, y);
						glVertex2f(x + step, y - step);
						glVertex2f(x, y - step);
					}
					else {
						//blue
						glColor3f(0, 0, 0.8);
						glVertex2f(x, y);
						glVertex2f(x + step, y);
						glVertex2f(x, y - step);
						glVertex2f(x + step, y);
						glVertex2f(x + step, y - step);
						glVertex2f(x, y - step);
					}

					x += step;
				}
				x = -1;
				y -= step;
			}

			x = -1; y = 1;

			glColor3f(0, 0, 0);
			glVertex2f(routerX, routerY);
			glVertex2f(routerX + ROUT_SIZE, routerY - ROUT_SIZE);
			glVertex2f(routerX - ROUT_SIZE, routerY - ROUT_SIZE);

			glEnd();

			//glLineWidth(5);
			/*glBegin(GL_LINES);

			glColor3f(0, 0, 0);
			glVertex2f(-0.5, 1);
			glVertex2f(-0.5, -1);

			glEnd();*/

			glPopMatrix();

			SwapBuffers(hDC);

			theta += 1.0f;
			Sleep(1);
		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hwnd, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hwnd);
	DestroyWindow(hwnd2);

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}

