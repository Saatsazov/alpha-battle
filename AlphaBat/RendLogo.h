void RendLogo()
{
	DWORD Time=GetTickCount();
	//Сделать чтобы лого тоже рисовалось само не из текстуры
	GLuint tex = LoadTexture("resources\\texture\\Logo.bmp");
	while(Time+1000>GetTickCount())
	{
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glFrontFace(GL_CW);
		glEnable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	float scale =(GetTickCount() - Time)*0.000005f;
		glPushMatrix();
		glBegin(GL_QUADS/*GL_TRIANGLES*/);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.3,-0.4,-1);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.3,0.2,-1);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.3,0.2,-1);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.3,-0.4,-1);			
		}
		glEnd();
		glPopMatrix();
		glFrontFace(GL_CCW);
		glColor3f(0.7,0.4,0.5);
		PrintString(FontBig,"ALPHABAT",-0.3,0.25,-1);
		glEnable(GL_LIGHTING);
		SwapBuffers (hDC);
	}

	//Sleep(10000);
	//PostQuitMessage(0);
}