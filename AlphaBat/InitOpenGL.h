void EnableOpenGL (HWND hWnd,
				   HDC *hDC,
				   HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;    
    *hDC = GetDC (hWnd);   
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
	pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
}
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
void InitOpenGL()
{
	glClearColor(0.4,0.3,0.6,1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	GLfloat ambientColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT,GL_SHININESS,128);

	WindowResize();

}