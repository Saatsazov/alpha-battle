//Type of move mishen
//Типы движения мишеней
#define LINIAR_MOVE			0
#define SIN_MOVE			1
#define COS_MOVE			2
#define SIZE_MOVE			3 //Увеличение и уменьшение мишени
#define LINIAR_SIZE_MOVE	4
#define SIN_SIZE_MOVE		5
#define COS_SIZE_MOVE		6
#define STATIC				7



//Scn
int UsefulMishen;
int ScoreToNextLvl;
struct MISHEN
{
	//int					Id; //temp
	GLuint TexId;
	Vec3f Coord; //координаты
	Vec3f StartCoord; //координаты при страте
	float Size;
	float StartSize;
	float hp; //сколько hp
	bool WhereGo;
	//true <-   false ->
	float Amplitude;
	int TypeMove;
	bool IsNeedKillIt;
	//int bukva;
	int color;
};
bool IsLoadedMap; 
class Mish
{
public:
	char Fname[100];
	MISHEN *mishen;
	int nMishen;
	int NeedColor;
	int NeedBukva;
	GLuint TexId;

	void Reset();
	void LoadMishenFile(char filename[]);
	void LoadRandMishen();
	void RendMishen();
	void MoveMishen();
	int GetScore(int id);
	void RendUsefulMishen();
};
void Mish::Reset()
{
	LoadMishenFile(Fname);
}
void Mish::RendUsefulMishen()
{
	glPushMatrix();
	{
		glColor3f(1,1,1);
		glLoadIdentity();
		glTranslatef(0.25,-0.30,-1);
		glScalef(0.5,0.5,0.5);
		glRotated(90,1,0,0);
		glRotated(90,0,1,0);
		glEnable(GL_TEXTURE_2D);
		if(Alphabet)
		{
			glBindTexture(GL_TEXTURE_2D,TexId);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, TexMishen);
			glColor3fv(color[NeedColor]);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST   /*GL_LINEAR*/);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glCallList(IdMishen);
	}
	glPopMatrix();
}
int Mish::GetScore(int id)
{
	switch(mishen[id].TypeMove)
	{
	case LINIAR_MOVE:
		return 5;
		break;
	case SIN_MOVE:
		return 10;
		break;
	case COS_MOVE:
		return 10;
		break;
	case SIZE_MOVE:
		return 3;
		break;
	case LINIAR_SIZE_MOVE:
		return 7;
		break;
	case SIN_SIZE_MOVE:
		return 15;
		break;
	case COS_SIZE_MOVE:
		return 15;
		break;
	case STATIC:
		return 3;
		break;
	default:
		return 3;
	}
	return 10;
}
void Mish::RendMishen()
{
	for(int a=0; a<nMishen;a++)
	{
		if(mishen[a].hp<0)
		{
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_ONE, GL_ONE);
			continue;
		}
		glPushMatrix();	
		{
			glTranslatef(
				mishen[a].Coord[0],
				mishen[a].Coord[1],
				mishen[a].Coord[2]);
			glRotated(90,1,0,0);
			glRotated(90,0,1,0);
			glScalef(
				mishen[a].Size,
				mishen[a].Size,
				mishen[a].Size);
			//glColor3ub(255,100+mishen[a].hp-210,100+mishen[a].hp-210);
			/*switch(a%7)
			{
			case 0:
				glColor3f(0.6,0.1,0.6);
				break;
			case 1:
				glColor3f(0.3,0.5,0.3);
				break;
			case 2:
				glColor3f(0.1,0.5,0.6);
				break;
			case 3:
				glColor3f(0.2,0.7,0.1);
		
				break;
			case 4:
				glColor3f(0.1,0.7,0.1);
				break;
			default:
				glColor3f(1,0,0);
				break;
			}*/
			/*if(!Alphabet)
			{
				Mishen.RendModelTex(true,Level.Mishen.mishen[a].TextureId);
			}
			else
				Mishen.RendModelTex(true,Level.Mishen.mishen[a].TextureId);*/
			//glCallList(IdMishen);
			glColor3f(1,1,1);
			//glColor3fv(color[mishen[a].color]);
			glEnable(GL_TEXTURE_2D);
			if(Alphabet)
				glBindTexture(GL_TEXTURE_2D, mishen[a].TexId);
			else
			{
				glBindTexture(GL_TEXTURE_2D, TexMishen);
				glColor3fv(color[mishen[a].color]);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST   /*GL_LINEAR*/);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glCallList(IdMishen);
			//	Mishen.RendModelTex(true,AlphTex[Level.Mishen.mishen[a].Bukva]);
		}
		glPopMatrix();
		//glDisable(GL_BLEND);

	}
}
void Mish::MoveMishen()
{
	for(int a=0;a<nMishen;a++)
	{
		if(mishen[a].TypeMove == STATIC)
			continue;
		if(mishen[a].WhereGo)//false ->
		{
			if(mishen[a].TypeMove==SIZE_MOVE)
			{
				if(mishen[a].Size<(mishen[a].StartSize+mishen[a].Amplitude/2))
				{
					mishen[a].Size+=0.5*timeDelta/1000.0f*GameSpeed;				
				}
				else
					mishen[a].WhereGo=false;
				continue;
			}
			if(mishen[a].Coord[0]>(mishen[a].StartCoord[0])-mishen[a].Amplitude/2)
			{
				switch(mishen[a].TypeMove)
				{
				case LINIAR_MOVE:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					break;
				case SIN_MOVE:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=sin((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					break;
				case COS_MOVE:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					break;
				case LINIAR_SIZE_MOVE:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Size=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*4);
					break;
				case SIN_SIZE_MOVE:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=sin((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					mishen[a].Size=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*4);
					break;
				case COS_SIZE_MOVE:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					mishen[a].Size=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*4);
					break;
				default:
					mishen[a].Coord[0]-=0.5*timeDelta/1000.0f*GameSpeed;
					break;
				}
			}
			else
			{
				mishen[a].WhereGo=false;
			}
		}
		else
		{
			if(mishen[a].TypeMove==SIZE_MOVE)
			{
				if(mishen[a].Size>(mishen[a].StartSize-mishen[a].Amplitude/2))
				{
					mishen[a].Size-=0.5*timeDelta/1000.0f*GameSpeed;			
				}
				else
					mishen[a].WhereGo=true;
				continue;
			}
			if(mishen[a].Coord[0]<(mishen[a].Amplitude/2+mishen[a].StartCoord[0]))
			{
				switch(mishen[a].TypeMove)
				{
				case LINIAR_MOVE:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					break;
				case SIN_MOVE:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=sin((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					break;
				case COS_MOVE:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					break;
				case LINIAR_SIZE_MOVE:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Size=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*4);
					break;
				case SIN_SIZE_MOVE:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=sin((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					mishen[a].Size=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*4);
					break;
				case COS_SIZE_MOVE:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					mishen[a].Coord[1]=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*6)/6+mishen[a].StartCoord[1];
					mishen[a].Size=cos((mishen[a].Coord[0]-mishen[a].StartCoord[0])*4);
					break;
				default:
					mishen[a].Coord[0]+=0.5*timeDelta/1000.0f*GameSpeed;
					break;
				}
			}
			else
			{
				mishen[a].WhereGo=true;
			}
		}
	}
}
void Mish::LoadRandMishen()
{
	if(IsLoadedMap)
	{
		//glDeleteTextures(1,&TexId);
		//for(int a = 0; a< nMishen; a++)
		//{
			
		//}
	}
	srand(time(NULL));
	NeedColor = rand()%ALL_COLOR;
	if(Alphabet)
	{
		NeedBukva = rand()%nSymbol;
		CreateTex(TexId,Alph[NeedBukva],NeedColor);
	}
	for(int a=0,b=0; a<nMishen; a++)//b - количество "полезных" мишеней
	{
		mishen[a].IsNeedKillIt = false;
		if((rand()%2 ==0)&&(b<UsefulMishen)||((UsefulMishen-b)>=(nMishen-a)))
											//если осталось "сделать" "полезных" 
											//мишеней столько жк сколько осталось шагов цыкла
		{
			b++;
			mishen[a].IsNeedKillIt = true;
			if(Alphabet)
			{
				mishen[a].TexId = TexId;
			}
			else
			{
				mishen[a].color = NeedColor;
			}
		}
		else
		{
			if(Alphabet)
			{
				if(Dificult)
				{
					//color
					int RandColor = rand()%ALL_COLOR;
					if(RandColor == NeedColor)
					{
						if(RandColor > ALL_COLOR)
							RandColor--;
						else
							RandColor++;
					}
					//bukva
					int RandBukva = rand()%nSymbol;
					if(RandBukva == NeedBukva)
					{
						if(RandBukva > nSymbol)
							RandBukva--;
						else
							RandBukva++;
					}
					CreateTex(mishen[a].TexId,Alph[RandBukva],RandColor);
				}
				else
				{
					//bukva
					int RandBukva = rand()%nSymbol;
					if(RandBukva == NeedBukva)
					{
						if(RandBukva > nSymbol)
							RandBukva--;
						else
							RandBukva++;
					}
					CreateTex(mishen[a].TexId,Alph[RandBukva],NeedColor);
				}
			}
			else
			{
				int RandColor = rand()%ALL_COLOR;
				if(RandColor == NeedColor)
				{
					if(RandColor > ALL_COLOR)
						RandColor--;
					else
						RandColor++;
				}
				mishen[a].color = RandColor;
			}
		}
	}
}
void Mish::LoadMishenFile(char filename[])
{
	strcpy(Fname,filename);
	FILE *file;
	file = fopen( filename, "r");
	if(file == NULL)
		return;
	if(IsLoadedMap)
	{
		delete []mishen;
	}
	fscanf(file,"%d\n",&nMishen);
	mishen = new MISHEN[nMishen];
	for(int a = 0;a<nMishen; a++)
	{
		fscanf(file,"%f %f %f %f %d %f %f",
			&mishen[a].Coord[0],
			&mishen[a].Coord[1],
			&mishen[a].Coord[2],
			&mishen[a].hp,
			&mishen[a].TypeMove,
			&mishen[a].Amplitude,
			&mishen[a].Size);
		mishen[a].StartCoord=mishen[a].Coord;
		mishen[a].StartSize=mishen[a].Size;
		mishen[a].WhereGo=false;
	}
	fclose(file);
	LoadRandMishen();
}
class MAP
{
public:
	float WMapSize;
	float LMapSize;

	char PrepMap[100];
	float PrepSens;
	bool **Prep;

	float HeightMapAmplitude;
	Terrain *HeightMap;
	float HeightmapSens;
	GLuint idHeightMap;
	//PlayerPos 1.555364 0.157059 1.761345 -0.203000 10.161199
	//PosForNextLevel -1.5 -1.5

	char NextLevelName[100];
	OBJ ObjMap;
	GLuint IdObjMap;

	char ScnFile[100];
	char FileMishen[100];
	Vec3f PosForNextLevel;

	//mishen
	Mish Mishen;
	//int nMishen;
	//MISHEN mishen[1];


	Vec3f PlayerPos;
	float PlayerHAngle;
	float PlayerVAngle;

	GLuint TexId;
	char filename[100];
	char MapName[100];
	void LoadMap(char name[]);
	void LoadNextLvl();
	MAP();
	~MAP();
private:
	void LoadPrep(char name[]);
	void RendTerrain();
	void ChoiceTexId();
	void LoadScnFile();
};
void MAP::LoadNextLvl()
{
	if(profile.CompleteLevel<(GetIdLevel(MapName)+1))
		profile.CompleteLevel = GetIdLevel(MapName)+2;
	//записать очки которые на этом уровне заработал
	profile.SaveProfile();
	TotalScore += Score;
	Score = 0;
	char str[100];
	strcpy(str,NextLevelName);
	LoadMap(str);
}
MAP::~MAP()
{
	if(IsLoadedMap)
	{
		delete HeightMap;
		//delete ObjMap;
		/*if(Prep!=NULL)
		for(int a=0;a<LMapSize/PrepSens;a++)
		{
			delete Prep[a];
		}*/
	}
}
void MAP::ChoiceTexId()
{
	if(IsLoadedMap)
		glDeleteTextures(1,&TexId);
	srand(time(NULL));
	int id = rand()%9+1;
	char str[100];
	sprintf(str,"resources\\texture\\levels\\%d.bmp",id);
	TexId = LoadTexture(str);
}
void MAP::LoadScnFile()
{
	FILE *file;
	file = fopen(ScnFile,"r");
	if(file == NULL)
		return;
	fscanf(file,"UsefulMishen %d\n",&UsefulMishen);
	fscanf(file,"ScoreToNextLvl %d\n",&ScoreToNextLvl);
	fclose(file);
}
void MAP::RendTerrain()
{
	if(!IsLoadedMap)
		idHeightMap = glGenLists(1);
	glEnable(GL_LIGHTING);
	glNewList(idHeightMap,GL_COMPILE);
	{
	//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glPushMatrix();
		{
			glRotated(180,0,1,0);
			glTranslatef(-LMapSize/2,0,-WMapSize/2);
			glScalef(HeightmapSens,1,HeightmapSens);
			glColor3f(0.3f, 0.9f, 0.0f);
			for(int z = 0; z < HeightMap->length() - 1; z++)
			{
				glBegin(GL_TRIANGLE_STRIP);
				for(int x = 0; x < HeightMap->width(); x++)
				{
					Vec3f normal = HeightMap->getNormal(x, z);
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f(x, HeightMap->getHeight(x, z), z);
					normal = HeightMap->getNormal(x, z + 1);
					glNormal3f(normal[0], normal[1], normal[2]);
					glVertex3f(x, HeightMap->getHeight(x, z + 1), z + 1);
				}
				glEnd();
			}
		}
		glPopMatrix();
	//	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	}
	glEndList();
}
MAP::MAP()
{
	IsLoadedMap = false;
}
MAP Level;
void MAP::LoadPrep(char name[])
{
	Image  *img = loadBMP(name);
	//char str[100];
	//sprintf(str,"Width %d Heiht %d",img->width,img->height);
	//MessageBoxA(NULL,str,name,MB_OK);
	Prep=new bool*[img->width];
	for(int i = 0; i < img->width; i++) 
		Prep[i] = new bool[img->height];
	//забить нулями
	for(int a=0;a<img->width;a++)
	{
		for(int b=0;b<img->height;b++)
		{
			Prep[a][b]=false;
		}
	}

	//MessageBoxA(NULL,PrepMap,"Wnd",MB_OK);
	for(int y = 0; y < img->height; y++)
	{
		for(int x = 0; x < img->width; x++)
		{
			if((img->pixels[3 * (y * img->width + x)])!=0)		
				Prep[x][y]=false;
			else
				Prep[x][y]=true;
		}
	}
	delete img;
}
void MAP::LoadMap(char name[])
{
	ChoiceTexId();
	Level.Mishen.nMishen = NULL;
	char str[100];
	sprintf(filename,"resources\\maps\\%s\\Level.map",name);
	FILE *file;
	file = fopen(filename,"r");
	if(file == NULL)
		return;
	if(!IsLoadedMap)
	{
		delete HeightMap;
		for(int a=0;a<LMapSize/PrepSens;a++)
		{
			delete Prep[a];
		}
	}
	strcpy(MapName,name);

	while(fgets(str,100,file)!=NULL)
	{
		if(!strncmp(str,"WMapSize ",9))
		{
			sscanf(str,"WMapSize %f",&WMapSize);
			continue;
		}
		if(!strncmp(str,"LMapSize ",9))
		{
			sscanf(str,"LMapSize %f",&LMapSize);
			continue;
		}
		if(!strncmp(str,"PrepSens ",9))
		{
			sscanf(str,"PrepSens %f",&PrepSens);
			continue;
		}
		if(!strncmp(str,"PrepMap ",8))
		{
			sscanf(str,"PrepMap %s",PrepMap);
			char buf[100];
			sprintf(buf,"resources\\maps\\%s\\%s",name,PrepMap);
			strcpy(PrepMap,buf);
			continue;
		}
		if(!strncmp(str,"HeightMapAmplitude ",19))
		{
			sscanf(str,"HeightMapAmplitude %f",&HeightMapAmplitude);
			continue;
		}
		if(!strncmp(str,"Heightmap ",10))
		{
			char HeightmapName[100];
			sscanf(str,"Heightmap %s",HeightmapName);
			char buf[100];
			sprintf(buf,"Resources\\maps\\%s\\%s",name,HeightmapName);
			sprintf(HeightmapName,"%s",buf);
			HeightMap = loadTerrain(HeightmapName, HeightMapAmplitude);
			continue;
		}
		if(!strncmp(str,"HeightmapSens ",14))
		{
			sscanf(str,"HeightmapSens %f",&HeightmapSens);
			continue;
		}
		if(!strncmp(str,"PlayerPos ",10))
		{
			sscanf(str,"PlayerPos %f %f %f %f %f",
				&PlayerPos[0],&PlayerPos[1],&PlayerPos[2],
				&PlayerVAngle,&PlayerHAngle);
			continue;
		}
		if(!strncmp(str,"PosForNextLevel ",16))
		{
			sscanf(str,"PosForNextLevel %f %f",
				&PosForNextLevel[0],
				&PosForNextLevel[2]);
			continue;
		}
		if(!strncmp(str,"NextLevelName ",14))
		{
			sscanf(str,"NextLevelName %s",NextLevelName);
			continue;
		}
		if(!strncmp(str,"ObjMap ",7))
		{
			char ObjMapName[100];
			sscanf(str,"ObjMap %s",ObjMapName);
			char buf[100];
			sprintf(buf,"Resources\\maps\\%s\\%s",name,ObjMapName);
			strcpy(ObjMapName,buf);
			ObjMap.LoadFile(ObjMapName);
			if(IsLoadedMap)
				glDeleteLists(IdObjMap,1);
			IdObjMap = glGenLists(1);
			glNewList(IdObjMap,GL_COMPILE);
			ObjMap.RendModelTex(true,Level.TexId);
			glEndList();
			continue;
		}
		if(!strncmp(str,"ScnFile ",8))
		{
			sscanf(str,"ScnFile %s",ScnFile);
			char buf[100];
			sprintf(buf,"Resources\\maps\\%s\\%s",Level.MapName,ScnFile);
			strcpy(ScnFile,buf);
			LoadScnFile();
			continue;
		}
		if(!strncmp(str,"FileMishen ",11))
		{
			sscanf(str,"FileMishen %s",FileMishen);
			char buf[100];
			sprintf(buf,"Resources\\maps\\%s\\%s",MapName,FileMishen);
			strcpy(FileMishen,buf);
			continue;
		}
	}

	//MessageBoxA(NULL,PrepMap,"Wnd",MB_OK);
	LoadPrep(PrepMap);
	//MessageBoxA(NULL,PrepMap,"Wnd",MB_OK);
	RendTerrain();
	Mishen.LoadMishenFile(FileMishen);
	fclose(file);
	IsLoadedMap = true;
}