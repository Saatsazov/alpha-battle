#include "headline.h"
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
	//MSG msg;
	alutInit(NULL,NULL);
	WNDCLASS wc;

    MSG msg;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"OpenGl Game";
    RegisterClass (&wc);
	hWnd = CreateWindow (L"OpenGL Game", L"AlphaBat",
	WS_POPUP | /*WS_THICKFRAME   |*/ WS_CLIPCHILDREN | WS_CLIPSIBLINGS ,
		0, 0, WIDTH, HEIGHT,NULL, NULL, hInstance, NULL);
	EnableOpenGL (hWnd, &hDC, &hRC);
	InitOpenGL();
	SystemInit();//в ней вызывать функции ShowWindow SetForegroundWindow

	ShowWindow(hWnd,SW_NORMAL);
	SetForegroundWindow(hWnd);
	RendLogo();
	InitGame();
	ShowWindow(hWnd,SW_NORMAL);
	SetForegroundWindow(hWnd);
	Pause = !false;
	//Menu.WhatInMenu = MENU_PROFILE_ABOUT;
	do
	{   
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
		else
		{
			LTime=GetTickCount();
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			Rendering();
			timeDelta=GetTickCount()-LTime;
		}
	}
	while (msg.message != WM_QUIT);
	CleanUp();
	return msg.wParam;
}