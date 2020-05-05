void CreateTex(GLuint &tex,char bukva,int Idcolor)
{	
	if(Idcolor>ALL_COLOR)
	{
		MessageBox(NULL,L"Неправильный ид цвета",L"Waring",MB_OK);
		Idcolor = 0;
	}
	if(!glIsTexture(tex))
	{
		glDeleteTextures(1,&tex);
	}
	glGenTextures(1,&tex);
	glViewport(0, 0,512, 512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1, 0.0001, 6.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glColor3fv(color[Idcolor]);

	glBindTexture(GL_TEXTURE_2D, TexMishen);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFrontFace(GL_CW);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.414,-0.414,-1);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.414,0.414,-1);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.414,0.414,-1);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.414,-0.414,-1);			
		}
		glEnd();
	}
	glFrontFace(GL_CCW);
	glTranslatef(-0.2,-0.2,-1);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1,1,1);
	glRasterPos3f(0,0,0);
	glPushAttrib(GL_LIST_BIT);
	glListBase(FontVeryBig - 32);
	glCallLists(1, GL_UNSIGNED_BYTE, &bukva);
	glPopAttrib();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 512, 512, 0 );
	/*glTranslatef(-0.1,-0.1,0);
	char str[100];
	sprintf(str,"%d %.1f %.1f %.1f",Idcolor,color[Idcolor][1],color[Idcolor][2],color[Idcolor][3]);
	PrintString(str,0,0);
	SwapBuffers(hDC);
	Sleep(500);*/
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	WindowResize();
}