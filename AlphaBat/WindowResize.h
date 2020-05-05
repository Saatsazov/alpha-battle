void WindowResize()
{
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)WIDTH / (float)HEIGHT, 0.0001, 600.0);
	glMatrixMode(GL_MODELVIEW);
}