void RendSkyBox()
{
	glDisable(GL_LIGHTING);
	glFrontFace(GL_CW);

	glBindTexture(GL_TEXTURE_2D,Sky_top);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(-10,10,10);
		glTexCoord2f(0,1);
		glVertex3f(10,10,10);
		glTexCoord2f(1,1);
		glVertex3f(10,10,-10);
		glTexCoord2f(1,0);
		glVertex3f(-10,10,-10);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Sky_right);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(-10,-10,-10);
		glTexCoord2f(0,1);
		glVertex3f(-10,10,-10);
		glTexCoord2f(1,1);
		glVertex3f(10,10,-10);
		glTexCoord2f(1,0);
		glVertex3f(10,-10,-10);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Sky_left);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(10,-10,10);
		glTexCoord2f(0,1);
		glVertex3f(10,10,10);
		glTexCoord2f(1,1);
		glVertex3f(-10,10,10);
		glTexCoord2f(1,0);
		glVertex3f(-10,-10,10);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Sky_front);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(-10,-10,10);
		glTexCoord2f(0,1);
		glVertex3f(-10,10,10);
		glTexCoord2f(1,1);
		glVertex3f(-10,10,-10);
		glTexCoord2f(1,0);
		glVertex3f(-10,-10,-10);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Sky_back);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(10,-10,-10);
		glTexCoord2f(0,1);
		glVertex3f(10,10,-10);
		glTexCoord2f(1,1);
		glVertex3f(10,10,10);
		glTexCoord2f(1,0);
		glVertex3f(10,-10,10);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Sky_bottom);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(10,-10,10);
		glTexCoord2f(0,1);
		glVertex3f(-10,-10,10);
		glTexCoord2f(1,1);
		glVertex3f(-10,-10,-10);
		glTexCoord2f(1,0);
		glVertex3f(10,-10,-10);
	}
	glEnd();
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
}
void RendPosToNextLvlMap()
{
	//glFrontFace(GL_CW);
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	{
		glVertex3f(Level.PosForNextLevel.v[0]-0.4,0,Level.PosForNextLevel.v[2]+0.4);
		glVertex3f(Level.PosForNextLevel.v[0]+0.4,0,Level.PosForNextLevel.v[2]+0.4);
		glVertex3f(Level.PosForNextLevel.v[0]+0.4,0,Level.PosForNextLevel.v[2]-0.4);
		glVertex3f(Level.PosForNextLevel.v[0]-0.4,0,Level.PosForNextLevel.v[2]-0.4);
	}
	glEnd();
	//glFrontFace(GL_CCW);
}
void RendPosForNextLvl()
{
/*	glFrontFace(GL_CW);
	glBegin(GL_QUADS);
	{
		glVertex3f(Level.PosForNextLevel[0].v[0],0,Level.PosForNextLevel[0].v[2]);
		glVertex3f(Level.PosForNextLevel[1].v[0],0,Level.PosForNextLevel[0].v[2]);
		glVertex3f(Level.PosForNextLevel[1].v[0],0,Level.PosForNextLevel[1].v[2]);
		glVertex3f(Level.PosForNextLevel[0].v[0],0,Level.PosForNextLevel[1].v[2]);
	}
	glEnd();
	glFrontFace(GL_CCW);*/
	glPushMatrix();
	glTranslatef(Level.PosForNextLevel[0],0,Level.PosForNextLevel[2]);
	//glCallList(NextLvlList);
	glCallList(IdNextLvl);
	glPopMatrix();

}
void TwichCannon()
{
	if(TCannon)
	{
		if(TCannonUP)
		{
			if(TCannonTr>0.001f)
				TCannonUP = false;
			else
				TCannonTr+=0.0005f;
		}
		else
		{
			if(TCannonTr<0.0f)
			{
				TCannon = false;
			}
			else
				TCannonTr-=0.0001f;
		}
	}
	//glTranslatef(0,TCannonTr,0);
	glRotatef(-TCannonTr*1000,1,0,0);
}
void RendScore()
{
	glPushMatrix();
	char str[100];
	if(!Pause)
	{
		glDisable(GL_LIGHTING);
		glLoadIdentity();
		glTranslatef(0,0,-1);
		glColor3f(1,0,1);
		//sprintf(str,"FPS=%d",FPS);
		//PrintString(Arial,str,0.3,0.3,-1);
		//sprintf(str,"%s",Level.MapName);
		//PrintString(Arial,str,-0.3,0.3,-1);
		//glDisable(GL_LIGHTING);
		sprintf(str,"Бали %d",Score);
		PrintString(str,-0.40,-0.35);
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();
}
void RendRadar()
{
	//glEnable(GL_STENCIL_TEST);
//	glClearStencil(0);
	//glStencilMask(1);
	glPushMatrix();
	{
		glLoadIdentity();
		//Нарисовать Карту типа компас
		
		glColor3f(1,1,1);
	/*	glClear(GL_STENCIL_BUFFER_BIT);
		glStencilFunc(GL_NEVER, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);*/
	//glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
		/*glBegin(GL_QUADS);
			glVertex3f(-0.5,-0.3,-1);
			glVertex3f(-0.5,-0.1,-1);
			glVertex3f(-0.3,-0.1,-1);
			glVertex3f(-0.3,-0.3,-1);
		glEnd();*//*
		glStencilFunc(GL_EQUAL, 0, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);*/
	/*glStencilFunc(GL_EQUAL,1, 1);
	glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);*/
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glColor3f(0.0f, 1.0f, 0.0f);
		glEnable(GL_SCISSOR_TEST);
		/*glScissor(
			48,
			105,
			185,
			185);*/
		glScissor(
			220,
			105,
			185,
			185);
		/*glScissor(
			0.1*WIDTH,
			0.1*HEIGHT,
			0.2*HEIGHT,
			0.2*HEIGHT);*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		{
			glLoadIdentity();
			GLfloat lightColor02[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
			GLfloat lightPos02[] = {-0.5f, -0.5f, 1.0f, 0.0f};
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor02);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos02);
			glTranslatef(-0.4,-0.2,-1);
			glScalef(0.05,0.05,0.05);
			glRotatef(90.0f,1.0f,0.0f,0.0f);

			glRotatef(Player.GetHAngle()*(180/PI)+90,0,1,0);
			glTranslatef(-Player.GetPosX(),0,-Player.GetPosZ());

			glColor3f(1,1,1);
			//glCallList(Level.NListObjMap);
			glColor3f(1,1,1);

			glDisable(GL_TEXTURE_2D);
			glColor3f(0.3f, 0.9f, 0.0f);
			glCallList(Level.idHeightMap);
			glDisable(GL_LIGHTING);
			glColor3f(0.7f, 0.6f, 0.1f);
			glClear(GL_DEPTH_BUFFER_BIT);
			Level.ObjMap.RendLikePrep();

			glColor3f(1,1,1);
			RendPosToNextLvlMap();
			glClear(GL_DEPTH_BUFFER_BIT);

			if(MishenHelps)
			{
				glPointSize(3);
				glBegin(GL_POINTS);
				for(int a = 0; a< Level.Mishen.nMishen; a++)
				{
					if(Level.Mishen.mishen[a].hp<0)
						continue;
					glVertex3fv(Level.Mishen.mishen[a].Coord.v);
				}
				glEnd();
				//RendMishen();
			}
		}
		glPopMatrix();
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glColor3f(1,1,1);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.5,-0.3,-1);
			glVertex3f(-0.5,-0.1,-1);
			glVertex3f(-0.3,-0.1,-1);
			glVertex3f(-0.3,-0.3,-1);
		glEnd();
		glBegin(GL_LINE_STRIP);
		{
			glVertex3f(-0.410,-0.23,-1);
			glVertex3f(-0.4,-0.2,-1);
			glVertex3f(-0.390,-0.23,-1);
			//glVertex3f(-0.4,-0.225,-1);
		}
		glEnd();
	}
	glPopMatrix();
	//glDisable(GL_STENCIL_TEST);
}
void Rendering()
{
	Player.Look();
	glColor3f(1,1,1);

	RendSkyBox();
	GLfloat lightColor0[] = {0.3f, 0.3f, 0.3f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {0.0f, 1.7f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glDisable(GL_LIGHTING);
	glMateriali(GL_FRONT,GL_SHININESS,8);
	//Level.ObjMap.RendModel(true);
	//Level.ObjMap.RendModelTex(true,Level.TexId);
	glCallList(Level.IdObjMap);
	glEnable(GL_LIGHTING);
	glMateriali(GL_FRONT,GL_SHININESS,128);

	glColor3f(0.3f, 0.9f, 0.0f);
	glCallList(Level.idHeightMap);
	bullets.RendBull();
	RendPosForNextLvl();
	glDisable(GL_LIGHTING);
	Level.Mishen.RendMishen();
	glEnable(GL_LIGHTING);
	glPushAttrib(GL_DEPTH_TEST|GL_LIGHTING|GL_TEXTURE_2D);
	glPushMatrix();
	if(!Pause)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		RendRadar();
		Level.Mishen.RendUsefulMishen();
		glColor3f(1,0,1);
		if(Sight&&!Pause)
		{
			glColor3fv(SightColor);
			glLoadIdentity();

			glBegin(GL_LINES);
			{

				glVertex3f(0.01f, 0.0f, -1.0f);
				glVertex3f(0.02f, 0.0f, -1.0f);
				
				glVertex3f(0.0f, -0.01f, -1.0f);
				glVertex3f(0.0f, -0.02f, -1.0f);
		
				glVertex3f(-0.01f, 0.0f, -1.0f);
				glVertex3f(-0.02f, 0.0f, -1.0f);

				glVertex3f(0.0f, 0.01f, -1.0f);
				glVertex3f(0.0f, 0.02f, -1.0f);
			}
			glEnd();
		}
	}
	glPopMatrix();
	glPopAttrib();
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	if(!Pause)
	{
		glLoadIdentity();
		GLfloat lightPos03[] = {0.0f, 0.3f, 1.0f, 0.0f};
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos03);

		glEnable(GL_LIGHTING);
		glClear(GL_DEPTH_BUFFER_BIT);
		TwichCannon();
		glCallList(IdCannon);
	}
	glPopMatrix();
	glPopAttrib();
	RendScore();
	if(!Pause)
	{
		GetCursorPos(&MousePos);
		SetCursorPos(WIDTH/2,HEIGHT/2);
		Player.HorRoll((float)(MousePos.x-WIDTH/2)/1000*HMouseSens);
		Player.VertRoll((float)(HEIGHT/2-MousePos.y)/1000*VMouseSens);
		Keyboard();
		bullets.DO();
		Level.Mishen.MoveMishen();
	}
	else
		Menu.Rend();
	SwapBuffers(hDC);
}