void CleanUp()
{
	SaveSetting();
	profile.SaveProfile();
	KillFont(Font);
	KillFont(FontBig);
	alutExit();
	DisableOpenGL(hWnd, hDC, hRC);
	DestroyWindow(hWnd);
}