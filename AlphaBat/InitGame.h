void LoadTex()
{
	Sky_top = LoadTexture("Resources\\texture\\SkyBox\\Top.bmp");
	Sky_right = LoadTexture("Resources\\texture\\SkyBox\\Right.bmp");
	Sky_left = LoadTexture("Resources\\texture\\SkyBox\\Left.bmp");
	Sky_bottom = LoadTexture("Resources\\texture\\SkyBox\\Bottom.bmp");
	Sky_front = LoadTexture("Resources\\texture\\SkyBox\\Front.bmp");
	Sky_back = LoadTexture("Resources\\texture\\SkyBox\\Back.bmp");

	TexMishen = LoadTexture("Resources\\texture\\mishen.bmp");

	//CreateTex(TexMishenId,'À',2);
}
OBJ Cannon;
	OBJ NextLvl;
	OBJ Mishen;
void InitGame()
{
	LoadLevelsList();
	strcpy(NeedLoadLvl,FirstLvl);
	LoadAlphabet();
	IsLoadedMap = false; 
	LoadTex();
	Pause = !true;
	Menu.WhatInMenu = MENU_CHANGE_PROFILE;
	Sound = !true;
	Sight = true;
	MishenHelps = true;
	GameSpeed = 1.0f;
	HMouseSens = 1.2f;
	VMouseSens = 1.0f;
	SightColor[0] = 1.f;
	SightColor[1] = 0.0f;
	SightColor[2] = 1.0f;
	LoadSetting();
	TCannon = false;
	TCannonUP = true;
	Alphabet = !false;
	Dificult = !false;
	TCannonTr=0.0f;
	TotalScore = 0;
	Score = 0;
	LoadSetting();
	profile.LoadProfiles();
	Menu.InitMenu();
	Level.LoadMap(FirstLvl);
	RestartLevel();
	bullets.Reset();
	ShowCursor(CursorState=FALSE);

	

	Cannon.LoadFile("resources\\model\\cannon.obj");
	NextLvl.LoadFile("resources\\model\\NextLvl.obj");
	Mishen.LoadFile("resources\\model\\mishen.obj");
	IdCannon = glGenLists(1);
	glNewList(IdCannon,GL_COMPILE);
	{
		Cannon.RendModel(true);
	}
	glEndList();
	IdNextLvl = glGenLists(1);
	glNewList(IdNextLvl,GL_COMPILE);
	{
		NextLvl.RendModel(true);
	}
	glEndList();
	IdMishen = glGenLists(1);
	glNewList(IdMishen,GL_COMPILE);
	{
		Mishen.RendModel(true);
	}
	glEndList();
	//OpenAl
	alGenSources (1, &FireSrc);
	FireBuffer = alutCreateBufferFromFile("Resources\\Sound\\fire.wav");
	alSourcei (FireSrc, AL_BUFFER, FireBuffer);


	alGenSources (1, &ShotSrc);
	ShotBuffer = alutCreateBufferFromFile("Resources\\Sound\\shot.wav");
	alSourcei (ShotSrc, AL_BUFFER, ShotBuffer);

	alGenSources (1, &DieSrc);
	DieBuffer = alutCreateBufferFromFile("Resources\\Sound\\die.wav");
	alSourcei (DieSrc, AL_BUFFER, DieBuffer);
}