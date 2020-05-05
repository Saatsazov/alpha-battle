//������ � WhatInMenu
#define MENU_MAIN						0
#define MENU_OPTION						1
#define MENU_OPTION_AUDIO				2
#define MENU_OPTION_GAME				3
#define MENU_MAIN_SURE_EXIT				4
#define MENU_IN_GAME					5
#define MENU_IN_GAME_SURE_EXIT			6
#define MENU_NEW_GAME					7
#define MENU_SURE_RETURN_TO_MAIN		8
#define MENU_NEXT_LVL					9
#define MENU_PROFILE_SURE_EXIT			10
#define MENU_ENTER_NAME					11
#define MENU_GAME_OVER					12
#define MENU_PROFILE_ABOUT				13
#define MENU_CHANGE_PROFILE				14
#define MENU_PROFILE					15
#define MENU_SURE_DELETE_PROFILE		16
#define MENU_CONTINUE_GAME				17
#define MENU_CHANGE_PROFILE_SURE_EXIT	18
#define	MENU_CHANGE_ALPHABET			19
int HowManyState[]={
	4,//0
	2,
	1,
	2,
	1,
	3,
	1,
	2,
	1,
	1,
	1,//10
	0,
	0,
	0,
	0,//14
	5,
	1,
	0,  //17
	1,
	1,
	1
};
float i=0;// ��� ����� � ���� ������� ���������� 
class MENU
{
public:
	int WhatInMenu;
	int MenuState;

	void CheckReturn();
	void CheckEscape();
	void CheckUp();
	void CheckDown();
	void Rend();
	void ExitMenu();
	void EnterMenu();
	void ZeroMenu();
	void InitMenu();

private:
	void RendWhatInMenu();
};
void MENU::ExitMenu()
{
	ZeroMenu();
	Pause = false;
}
void MENU::ZeroMenu()
{
	MenuState = 0;
	ZeroMemory(key,256);
}
void MENU::EnterMenu()
{
	ZeroMenu();
	Pause = true;
}
void RendScoreOnDiagram()
{
	glPushMatrix();
	glColor3f(1,0,0);
	PrintString("1",-0.24,-0.0);
	PrintString("2",-0.14,-0.0);
	PrintString("3",-0.04,-0.0);
	PrintString("5",0.06,-0.0);
	glPopMatrix();
}
void RendScoreInfo()
{
	glPushMatrix();
	{
		glTranslatef(-0.1,0.2,0);
		glColor3f(1,0,0);
		PrintString("5 - ��������!",0.25f,-0.10);
		glColor3f(0.9,0.1,0);
		PrintString("4 - �����",0.25f,-0.15);
		glColor3f(0.8,0.2,0);
		PrintString("3 - �� ������",0.25f,-0.20);
		glColor3f(0.7,0.3,0);
		PrintString("2 - �������� ��",0.25f,-0.25);
		glColor3f(0.6,0.4,0);
		PrintString("1 - ������ �������",0.25f,-0.3);
	}
}
void RendDiagramInfo()
{
	glColor3f(0.4,0.3,0.6);
	PrintString("������ ����",-0.6f,0.35);
	glColor3f(0.4,0.8,0.6);
	PrintString("ʳ������ �������",-0.6f,-0.35);

}
void RendDiagram()
{
	glPushMatrix();
	glTranslatef(-0.3,0,0);
	glLineWidth(1.5);
	
	glBegin(GL_LINES);
	{
		//VERTICAL LINE
		glVertex2f(-0.3f,-0.3);
		glVertex2f(-0.3f,0.3);
		//HORIZONTAL LINE
		glVertex2f(-0.3f,0.0);
		glVertex2f(0.3f,0.0);
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		glColor3f(0.4,0.3,0.6);
		
		// Scores
		glVertex2f(-0.25,0);
		glVertex2f(-0.2,0);
		glVertex2f(-0.2,0.15);
		glVertex2f(-0.25,0.15);

		glVertex2f(-0.15,0);
		glVertex2f(-0.1,0);
		glVertex2f(-0.1,0.20);
		glVertex2f(-0.15,0.20);

		glVertex2f(-0.05,0);
		glVertex2f(0.0,0);
		glVertex2f(0.0,0.3);
		glVertex2f(-0.05,0.3);

		glVertex2f(0.05,0);
		glVertex2f(0.1,0);
		glVertex2f(0.1,0.2);
		glVertex2f(0.05,0.2);

	}
	glEnd();
	glFrontFace(GL_CW);
	glBegin(GL_QUADS);
	{
		//Mistakes
		glColor3f(0.4,0.8,0.6);
		
		glVertex2f(-0.25,0);
		glVertex2f(-0.2,0);
		glVertex2f(-0.2,-0.2);
		glVertex2f(-0.25,-0.2);

		glVertex2f(-0.15,0);
		glVertex2f(-0.1,0);
		glVertex2f(-0.1,-0.1);
		glVertex2f(-0.15,-0.1);

		glVertex2f(-0.05,0);
		glVertex2f(0.0,0);
		glVertex2f(0.0,-0.10);
		glVertex2f(-0.05,-0.10);

		glVertex2f(0.05,0);
		glVertex2f(0.1,0);
		glVertex2f(0.1,-0.03);
		glVertex2f(0.05,-0.03);

	}
	glEnd();
	glFrontFace(GL_CCW);
	RendScoreOnDiagram();
	glPopMatrix();
}

void MENU::InitMenu()
{
	HowManyState[MENU_CHANGE_PROFILE] = profile.nUsers+1;
	HowManyState[MENU_CONTINUE_GAME] = profile.CompleteLevel;
}
void MENU::RendWhatInMenu()
{
	char str[100];
	if(WhatInMenu != MENU_PROFILE_ABOUT)
		glTranslatef(-0.1f,0,0);
	switch(WhatInMenu)
	{
	case MENU_CONTINUE_GAME:
		for(int a =0; a<profile.CompleteLevel;a++)
		{
			if(MenuState==a)
			{
				sprintf(str,"%s *",Levels[a].str);
				PrintString(str,-0.1f,0.15f-0.05f*a);
			}
			else
				PrintString(Levels[a].str,-0.1f,0.15f-0.05f*a);
		}
		if(MenuState == profile.CompleteLevel)
			PrintString("����� *",-0.1f,-0.35f);
		else
			PrintString("�����",-0.1f,-0.35f);
		break;
	case MENU_PROFILE_ABOUT:
		char str[100];
		glColor3f(0.4,0.3,0.6);
		sprintf(str,"�������: %s",profile.CurentUser);
		
		PrintString(str,		0.20f,0.35f);
		PrintString("г����: 1",		0.20f,0.30f);
		PrintString("����� *",	0.20f,-0.4f);
		
		RendDiagram();
		RendDiagramInfo();
		RendScoreInfo();
		
		break;
	case MENU_PROFILE:
		sprintf(str,"�������: %s",profile.CurentUser);
		PrintString(str,-0.1f,0.2f);
		if(MenuState==0)
			PrintString("����� *",-0.1f,0.1f);
		else
			PrintString("�����",-0.1f,0.1f);
		if(MenuState==1)
			PrintString("���� ������� *",-0.1f,0.05f);
		else
			PrintString("���� �������",-0.1f,0.05f);
		if(MenuState==2)
			PrintString("���������� *",-0.1f,0.0f);
		else
			PrintString("����������",-0.1f,0.0f);
		if(MenuState==3)
			PrintString("�������� *",-0.1f,-0.05f);
		else
			PrintString("��������",-0.1f,-0.05f);
		if(MenuState==4)
			PrintString("������ ������ *",-0.1f,-0.1f);
		else
			PrintString("������ ������",-0.1f,-0.1f);
		if(MenuState==5)
			PrintString("����� *",-0.1f,-0.15f);
		else
			PrintString("�����",-0.1f,-0.15f);
		break;
	case MENU_CHANGE_PROFILE:
		PrintString("������ ������",-0.1f,0.2f);
		for(int a =0; a<profile.nUsers;a++)
		{
			if(MenuState==a)
			{
				sprintf(str,"%s *",profile.Names[a].str);
				PrintString(str,-0.1f,0.15f-0.05f*a);
			}
			else
				PrintString(profile.Names[a].str,-0.1f,0.15f-0.05f*a);
		}
		if(MenuState==profile.nUsers)
			PrintString("����� ������� *",-0.1f,-0.20f);
		else
			PrintString("����� �������",-0.1f,-0.20f);
		if(MenuState==profile.nUsers+1)
			PrintString("����� *",-0.1f,-0.25f);
		else
			PrintString("�����",-0.1f,-0.25f);
		break;
	case MENU_GAME_OVER:
		PrintString("�� ������� ���!! ",-0.1f,0.1f);
		PrintString("�� �������",-0.1f,0.00f);
		sprintf(str,"%d ����", TotalScore);
		PrintString(str,-0.1f,-0.05f);
		break;
	case MENU_ENTER_NAME:
		PrintString("������ ��� ��'�:",-0.1f,0.1f);
		//PrintString(Name,-0.01f,-0.01);
		PrintString("�� �������� ENTER",-0.1f,-0.1f);
		break;
	case MENU_NEXT_LVL:
		//��� ������� ���� ����� ����� ��� ������ �� ��� �����������
		if(Score>=ScoreToNextLvl)
		{
			HowManyState[MENU_NEXT_LVL] = 2;
			PrintString("³����!!!",-0.1f,0.15f);
			if(MenuState==2)
				PrintString("��������� *",-0.05f,-0.25f);
			else
				PrintString("���������",-0.05f,-0.25f);
		}
		else
		{
			HowManyState[MENU_NEXT_LVL] = 1;
			PrintString("�� ��������:(",-0.1f,0.15f);
		}
		PrintString("����:",-0.2f,0.0f);

		sprintf(str,"%d",Score);
		PrintString(str,-0.20f,-0.05f);

		PrintString("���������",0.2f,0.05f);
		PrintString("����:",0.2f,0.0f);

		sprintf(str,"%d",ScoreToNextLvl);
		PrintString(str,0.20f,-0.05f);
		if(MenuState==1)
			PrintString("C������� *",0.1f,-0.2f);
		else
			PrintString("C�������",0.1f,-0.2f);
		if(MenuState==0)
			PrintString("���� *",-0.2f,-0.2f);
		else
			PrintString("����",-0.2f,-0.2f);
		break;
	case MENU_OPTION_AUDIO:
		if(MenuState==0)
		{
			if(Sound)
				PrintString("���� ��� *",-0.1f,-0.05f);
			else
				PrintString("���� ���� *",-0.1f,-0.05f);
		}
		else
		{
			if(Sound)
				PrintString("���� ��� ",-0.1f,-0.05f);
			else
				PrintString("���� ����",-0.1f,-0.05f);
		}
		if(MenuState==1)
			PrintString("����� *",-0.1f,-0.15f);
		else
			PrintString("�����",-0.1f,-0.15f);
		break;
	case MENU_OPTION_GAME:
		if(MenuState==0)
		{
			if(MishenHelps)
				PrintString("ϳ������ ��� *",-0.1f,-0.05f);
			else
				PrintString("ϳ������ ���� *",-0.1f,-0.05f);
		}
		else
		{
			if(MishenHelps)
				PrintString("ϳ������ ���",-0.1f,-0.05f);
			else
				PrintString("ϳ������ ����",-0.1f,-0.05f);
		}
		if(MenuState==1)
		{
			sprintf(str,"�������� %.1f *",GameSpeed);
			PrintString(str,-0.1f,-0.1f);
		}
		else
		{
			sprintf(str,"�������� %.1f",GameSpeed);
			PrintString(str,-0.1f,-0.1f);
		}
		if(MenuState==3)
			PrintString("����� *",-0.1f,-0.15f);
		else
			PrintString("�����",-0.1f,-0.15f);
		break;
	case MENU_OPTION:
		PrintString("������������:",-0.1f, 0.15f);
		if(MenuState==0)
			PrintString("���� *",-0.1f, 0.05f);
		else
			PrintString("����",-0.1f, 0.05f);
		if(MenuState==1)
			PrintString("������������ ��� *",-0.1f,0.0f);
		else
			PrintString("������������ ���",-0.1f,0.0f);

		if(MenuState==2)
			PrintString("����� *",-0.1f,-0.1f);
		else
			PrintString("�����",-0.1f,-0.1f);
			break;
		break;
	case MENU_SURE_RETURN_TO_MAIN:
	case MENU_IN_GAME_SURE_EXIT:
	case MENU_MAIN_SURE_EXIT:
	case MENU_CHANGE_PROFILE_SURE_EXIT:
	case MENU_PROFILE_SURE_EXIT:
		PrintString("�� �������?",-0.1f, 0.2f);

		if(MenuState==0)
			PrintString("��� *",-0.1f,-0.05f);
		else
			PrintString("���",-0.1f,-0.05f);
		if(MenuState==1)
			PrintString("ͳ *",-0.1f,-0.1f);
		else
			PrintString("ͳ",-0.1f,-0.1f);
		break;
	case MENU_IN_GAME:
		if(MenuState==0)
			PrintString("����������� �� ��� *",-0.1f, 0.05f);
		else
			PrintString("����������� �� ���",-0.1f, 0.05f);
		if(MenuState==1)
			PrintString("��������� ����� *",-0.1f,0.0f);
		else
			PrintString("��������� �����",-0.1f,0.0f);
		if(MenuState==2)
			PrintString("������� ���� *",-0.1f,-0.05f);
		else
			PrintString("������� ����",-0.1f,-0.05f);

		if(MenuState==3)
			PrintString("����� *",-0.1f,-0.1f);
		else
			PrintString("�����",-0.1f,-0.1f);
			break;
	case MENU_NEW_GAME:
		PrintString("������ ��� ���",-0.2f, 0.15f);
		if(MenuState==0)
			PrintString("��� ���� *",-0.2f, 0.05f);
		else
			PrintString("��� ����",-0.2f, 0.05f);
		glColor3f(0.4,0.1,0.3);
		PrintString("� �������",-0.2f,0.0f);
		if(MenuState==1)
			PrintString("(������ �������) *",-0.17f,-0.05f);
		else
			PrintString("(������ �������)",-0.17f,-0.05f);
		glColor3f(0.7,0.1,0.4);
		PrintString("� �������",-0.2f,-0.1f);
		if(MenuState==2)
			PrintString("(���������� �������) *",-0.17f,-0.15f);
		else
			PrintString("(���������� �������)",-0.17f,-0.15f);
		break;
	case MENU_MAIN:
	default:
		if(MenuState==0)
			PrintString("���� ��� *",-0.1f, 0.05f);
		else
			PrintString("���� ���",-0.1f, 0.05f);
		if(MenuState==1)
			PrintString("���������� ��� *",-0.1f,0.0f);
		else
			PrintString("���������� ���",-0.1f,0.0f);
		if(MenuState==2)
			PrintString("���� ������ *",-0.1f,-0.05f);
		else
			PrintString("���� ������",-0.1f,-0.05f);
		if(MenuState==3)
			PrintString("������������ *",-0.1f,-0.1f);
		else
			PrintString("������������",-0.1f,-0.1f);
		if(MenuState==4)
			PrintString("����� *",-0.1f,-0.15f);
		else
			PrintString("�����",-0.1f,-0.15f);
			break;
	}
}

void MENU::CheckEscape()
{
	switch(WhatInMenu)
	{
	case MENU_MAIN:
		WhatInMenu = MENU_PROFILE;
		break;
	case MENU_OPTION:
		WhatInMenu = MENU_MAIN;
		break;
	case MENU_OPTION_AUDIO:
		WhatInMenu = MENU_OPTION;
		break;
	case MENU_OPTION_GAME:
		WhatInMenu = MENU_OPTION;
		break;
	case MENU_IN_GAME:
		ExitMenu();
		break;
	case MENU_IN_GAME_SURE_EXIT:
		WhatInMenu = MENU_IN_GAME;
		break;
	case MENU_NEW_GAME:
		break;
	case MENU_SURE_RETURN_TO_MAIN:
		WhatInMenu = MENU_IN_GAME;
		break;
	case MENU_NEXT_LVL:
		break;
	case MENU_ENTER_NAME:
		break;
	case MENU_GAME_OVER:
		break;
	case MENU_PROFILE_ABOUT:
		WhatInMenu = MENU_PROFILE;
		break;
	case MENU_PROFILE:
		WhatInMenu = MENU_MAIN;
		break;
	case MENU_SURE_DELETE_PROFILE:
		WhatInMenu = MENU_PROFILE;
		break;
	case MENU_CONTINUE_GAME:
		WhatInMenu = MENU_MAIN;
		break;
	case MENU_CHANGE_PROFILE:
		WhatInMenu = MENU_CHANGE_PROFILE_SURE_EXIT;
		break;
	case MENU_CHANGE_PROFILE_SURE_EXIT:
		WhatInMenu = MENU_CHANGE_PROFILE;
		break;
	case MENU_PROFILE_SURE_EXIT:
		WhatInMenu = MENU_PROFILE;
		break;
	}
	//ExitMenu();
}
void MENU::Rend()
{
	glLoadIdentity();
	glTranslatef(0,0,-1);
	GLfloat lightPos02[] = {0.0f, .0f, 2.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos02);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	//Rendering();
	
	glDisable(GL_TEXTURE_2D);
	

	glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBegin(GL_QUADS);
		{
			glColor3f(1,1,1);
				glVertex2f(1.3f,0.5);
				glVertex2f(-1.3f,0.5);
			glColor3f(0,1,1);
				glVertex2f(-1.3f,-0.5);
				glVertex2f(1.3f,-0.5);
		}
		glEnd();
	glDisable(GL_BLEND);
	if(!((WhatInMenu == MENU_PROFILE_ABOUT)||(WhatInMenu == MENU_NEXT_LVL)))
	{
		//������ ��������
		glPushMatrix();
		{
			glColor3f(1,1,1);
			//glTranslatef(0,0,-1);
			for(float i=0;i<10;i+=0.5f)
			{
				glPushMatrix();
				{
					float angle=2*PI*(i)/10;
					glTranslatef(0.4*cos(angle),0.4*sin(angle),0);
					glutSolidSphere(0.05f,32,2);
				}
				glPopMatrix();
			}

		}
		glPopMatrix();
		glPushMatrix();
		{
			if(i<0)
				i=10;
			glColor3f(0.1,0.3,1);

			float angle;

			glPushMatrix();
			angle=2*PI*(i)/10;

			glTranslatef(0.4*cos(angle),0.4*sin(angle),0);
			glutSolidSphere(0.05f,32,2);

			glPopMatrix();
			glPushMatrix();

			glColor3f(0.3,0.5,1);
			angle=2*PI*(i-0.5)/10;
			glTranslatef(0.4*cos(angle),0.4*sin(angle),0);
			glutSolidSphere(0.05f,32,2);
			glPopMatrix();

			glColor3f(0.7,0.5,1);
			angle=2*PI*(i-1)/10;
			glTranslatef(0.4*cos(angle),0.4*sin(angle),0);
			glutSolidSphere(0.05f,32,2);
			if(WhatInMenu!=MENU_PROFILE_ABOUT)
				i-=0.5f;
		}
		glPopMatrix();
	}
	glDisable(GL_LIGHTING);
	glColor3f(0.4,0.3,0.6);
	RendWhatInMenu();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	Sleep(50);
}

void MENU::CheckUp()
{
	if(Pause)
		if(MenuState>0)
			MenuState--;
		else
			MenuState=HowManyState[WhatInMenu];
}
void MENU::CheckDown()
{
	if(Pause)
		if(MenuState<HowManyState[WhatInMenu])
			MenuState++;
		else
			MenuState=0;
}