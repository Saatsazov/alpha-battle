struct INDEX
{
	int v;
	int n;
	int t;
};
struct TRIANGLE
{
	INDEX p[3];
};
struct WHEREMTL
{
	int n;
	char Mtl[100];
};
struct MTL
{
	char name[100];
	float Ka[3]; //Ambient-свойства материала  float[3] 
	float Kd[3]; //Diffuse-свойства материала 
	float Ks[3]; //Specular-свойства материала 
	float d; // Прозрачность float 0..1 
	float Ns; //Shineness (блестячесть)  float 0..? 
	float illumw; //Излучение float 0..?

	bool IsMtlHasMap_Ka;
	char map_Ka[100];  //имя файла с Ambient-текстурой      (Может отсутствовать)
	GLuint hMap_Ka;

	bool IsMtlHasMap_Kd;
	char map_Kd[100];//  имя файла с Diffuse-текстурой        (Может отсутствовать)
	GLuint hMap_Kd;

	bool IsMtlHasMap_Ks;
	char map_Ks[100];//  имя файла с Specular-текстурой      (Может отсутствовать) 
	GLuint hMap_Ks;
};
class OBJ
{
public:
	int nVertex;
	int nTexCoord;
	int nNormalVector;
	int nFace;
	int nMtl;
	int nWhereUsemtl;

	Vec3f *Vertex;
	Vec3f *NormalVector;
	Vec3f *TexCoord;
	TRIANGLE *Face;
	MTL *Mtl;
	WHEREMTL *WhereUseMtl;//!!!!!!!!!!!!!!!!!!!!!
	//Массив где записано в коком по счете треугольнике исполmьзовать метал
	

	int CountWhere;

	char filename[100];
	char filenameMtl[100];

	
	bool IsFileCheck;
	bool IsFileHasTexCoord;
	bool IsFileHasNormalVector;
	bool IsFileHasMtl;
	
	bool IsLoaded;
	//func
	void RendLikePrep();
	void LoadFile(char str[]);
	bool LoadMtl();
	bool HowManyVertex();
	bool HowManyMtl();
	void RendModel(bool mode);
	void RendModelTex(bool mode,GLuint tex);
	void CheckFile(char str[]);
	bool SaveFile(char fname[]);
	void UseMtl(char MtlName[]);
	OBJ();
	~OBJ();
	void LoadStand()
	{
		nVertex = 0;
		nNormalVector = 0;
		nTexCoord = 0;
		nFace = 0;
		CountWhere = 0;
		nMtl = 0;
		nWhereUsemtl = 0;
		IsFileCheck = false;
		IsFileHasTexCoord=false;
		IsFileHasNormalVector=false;
		IsFileHasMtl=false;
	}
};
OBJ::OBJ()
{
	LoadStand();	
	IsLoaded = false;
}
OBJ::~OBJ()
{
	if(Vertex != NULL)
		delete []Vertex;
	if(NormalVector != NULL)
		delete []NormalVector;
	if(TexCoord != NULL)
		delete []TexCoord;
	if(Face != NULL)
		delete []Face;
	if(Mtl != NULL)
		delete []Mtl;
	if(WhereUseMtl != NULL)
		delete []WhereUseMtl;
}
void OBJ::UseMtl(char MtlName[])
{
	for(int cMtl=0; cMtl<nMtl;cMtl++)//поиск металов в Mtl[a].name и сравнить с MtlName
	{
		if(!strncmp(Mtl[cMtl].name, MtlName, strlen(MtlName)))
		{	
			//использовать метал с номером cMtl
			glColor3fv(Mtl[cMtl].Ka);
			if(Mtl[cMtl].IsMtlHasMap_Ka)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, Mtl[cMtl].hMap_Ka);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST   /*GL_LINEAR*/);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
				glDisable(GL_TEXTURE_2D);
			return;
		}
	}
}
bool OBJ::HowManyMtl()
{
	FILE *file;
	file = fopen(filenameMtl,"r");
	if(file==NULL)
		return false;
	char str[100];
	while(fgets(str,100,file)!=NULL)
	{
		if(!strncmp(str,"newmtl ",7))
			nMtl++;
	}
	Mtl = new MTL[nMtl];
	fclose(file);
	return true;
}
bool OBJ::LoadMtl()
{
	if(!HowManyMtl())
		return false;
	FILE *file;
	file = fopen(filenameMtl,"r");
	if(file==NULL)
		return false;
	char str[100];
	int CountMtl = 0;
	while(fgets(str,100,file)!=NULL)
	{
		if(!strncmp(str,"newmtl ",7))
		{
			sscanf(str,"newmtl %s",Mtl[CountMtl].name);
			Mtl[CountMtl].IsMtlHasMap_Ka=false;
			if(fgets(str,100,file)==NULL)
				break;
			do
			{
				if(fgets(str,100,file)==NULL)
					break;
				if(!strncmp(str,"\tmap_Ka ",8))
				{
					Mtl[CountMtl].IsMtlHasMap_Ka=true;
					sscanf(str," map_Ka %s",Mtl[CountMtl].map_Ka);
				
					Mtl[CountMtl].hMap_Ka = LoadTexture(Mtl[CountMtl].map_Ka);

					//если загружать текстуру сразу в Mtl[CountMtl].hMap_Ka
					//то потом в UseMtl она не загружается надо разобратся
					//беда в том что когда идет загрузка то OpenGL еще не 
					//не инициализировался и потом контекст рендера меняеется!
					//!!!!!!!!!!!!!!!!!!!!!!!!!!!
					continue;
				}
				if(!strncmp(str,"\tKa ",4))
				{
					sscanf(str," Ka %f %f %f",&Mtl[CountMtl].Ka[0],&Mtl[CountMtl].Ka[1],&Mtl[CountMtl].Ka[2]);
					continue;
				}
				if(!strncmp(str,"\tKd ",4))
				{
					sscanf(str," Kd %f %f %f",&Mtl[CountMtl].Kd[0],&Mtl[CountMtl].Kd[1],&Mtl[CountMtl].Kd[2]);
					continue;
				}
			}
			while(str[0]!='\n');
			CountMtl++;
		}

	}
	fclose(file);
	return true;
}
bool OBJ::HowManyVertex()
{
	FILE *file;
	//file = new FILE;
	file = fopen(filename,"r");
	char str[100];
	if(file == NULL)
		return false;
	while(fgets(str,100,file)!=NULL)
	{
		if((str[0]=='v')&&(str[1]==' '))
		{
			nVertex++;
			continue;
		}
		if((str[0]=='v')&&(str[1]=='n'))
		{
			nNormalVector++;
			continue;
		}
		if((str[0]=='v')&&(str[1]=='t'))
		{
			nTexCoord++;
			continue;
		}
		if((str[0]=='f')&&(str[1]==' '))
		{
			nFace++;
			continue;
		}
		if(!strncmp(str,"usemtl ",7))
		{
			nWhereUsemtl++;
			continue;
		}
	}
	Vertex = new Vec3f[nVertex];
	NormalVector = new Vec3f[nNormalVector];
	TexCoord = new Vec3f[nTexCoord];
	Face = new TRIANGLE[nFace];
	WhereUseMtl = new WHEREMTL[nWhereUsemtl];
	fclose(file);
	return true;
}
void OBJ::CheckFile(char str[])
{
	IsFileHasTexCoord=true;
	IsFileHasNormalVector=true;
	IsFileCheck = true;
}
void OBJ::LoadFile(char fname[])
{
	if(IsLoaded)
	{
		delete []Vertex;
		delete []NormalVector;
		delete []TexCoord;
		delete []Face;
		delete []Mtl;
		delete []WhereUseMtl;
	}
	LoadStand();
	strcpy(filename,fname);
	if(!HowManyVertex())
		return;
	FILE *file;
	//file = new FILE;
	file = fopen(filename,"r");
	char str[100];
	if(file == NULL)
		return;
	
	int CountVertex = 0;
	int CountTexCoord = 0;
	int CountNormalVector = 0;
	int CountFace = 0;
	while(fgets(str,100,file)!=NULL)
	{
		if(!strncmp(str,"mtllib",6))
		{
			IsFileHasMtl=true;
			sscanf(str,"mtllib %s",filenameMtl);
			LoadMtl();
		}
		if(!strncmp(str,"usemtl",6))
		{
			if(IsFileHasMtl)
			{
				WhereUseMtl[CountWhere].n=CountFace;
				sscanf(str,"usemtl %s",WhereUseMtl[CountWhere].Mtl);
				CountWhere++;
			}
		}
		if((str[0]=='v')&&(str[1]==' '))
		{
			sscanf(str,"v %f %f %f",
				&Vertex[CountVertex][0],
				&Vertex[CountVertex][1],
				&Vertex[CountVertex][2]);
			CountVertex++;
		}
		if((str[0]=='v')&&(str[1]=='t'))
		{
			sscanf(str,"vt %f %f %f",
				&TexCoord[CountTexCoord][0],
				&TexCoord[CountTexCoord][1],
				&TexCoord[CountTexCoord][2]);
			CountTexCoord++;
		}
		if((str[0]=='v')&&(str[1]=='n'))
		{
			sscanf(str,"vn %f %f %f",
				&NormalVector[CountNormalVector][0],
				&NormalVector[CountNormalVector][1],
				&NormalVector[CountNormalVector][2]);
			CountNormalVector++;
		}
		if((str[0]=='f')&&(str[1]==' '))
		{
			if(!IsFileCheck)
				CheckFile(str);
			if(IsFileHasNormalVector)
				if(!IsFileHasTexCoord)
					sscanf(str,"f %d/%d %d/%d %d/%d",
					&Face[CountFace].p[0].v,&Face[CountFace].p[0].n,
					&Face[CountFace].p[1].v,&Face[CountFace].p[1].n,
					&Face[CountFace].p[2].v,&Face[CountFace].p[2].n);
				else
				sscanf(str,"f %d/%d/%d %d/%d/%d %d/%d/%d",
					&Face[CountFace].p[0].v,&Face[CountFace].p[0].t,&Face[CountFace].p[0].n,
					&Face[CountFace].p[1].v,&Face[CountFace].p[1].t,&Face[CountFace].p[1].n,
					&Face[CountFace].p[2].v,&Face[CountFace].p[2].t,&Face[CountFace].p[2].n);
			else
				if(IsFileHasTexCoord)
					sscanf(str,"f %d/%d %d/%d %d/%d",
						&Face[CountFace].p[0].v,&Face[CountFace].p[0].t,
						&Face[CountFace].p[1].v,&Face[CountFace].p[1].t,
						&Face[CountFace].p[2].v,&Face[CountFace].p[2].t);
				else
					sscanf(str,"f %d %d %d",
						&Face[CountFace].p[0].v,
						&Face[CountFace].p[1].v,
						&Face[CountFace].p[2].v);

			CountFace++;
		}

	}
	fclose(file);
	IsLoaded = true;
}
void OBJ::RendModel(bool mode)
{
	CountWhere=0;
	if(!mode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	for(int a=0;a<nFace;a++)
	{
		if(IsFileHasMtl)
		if(a==WhereUseMtl[CountWhere].n)
		{
			UseMtl(WhereUseMtl[CountWhere].Mtl);
			CountWhere++;
		}
		glBegin(GL_TRIANGLES);
		{
			if(IsFileHasNormalVector)
				glNormal3fv(NormalVector[Face[a].p[0].n-1].v); 
			if(IsFileHasTexCoord)
				glTexCoord2fv(TexCoord[Face[a].p[0].t-1].v);
			glVertex3fv(Vertex[Face[a].p[0].v-1].v);
		
			if(IsFileHasNormalVector)
				glNormal3fv(NormalVector[Face[a].p[1].n-1].v); 
			if(IsFileHasTexCoord)
				glTexCoord2fv(TexCoord[Face[a].p[1].t-1].v);
			glVertex3fv(Vertex[Face[a].p[1].v-1].v);

			if(IsFileHasNormalVector)
				glNormal3fv(NormalVector[Face[a].p[2].n-1].v); 
			if(IsFileHasTexCoord)
				glTexCoord2fv(TexCoord[Face[a].p[2].t-1].v);
			glVertex3fv(Vertex[Face[a].p[2].v-1].v);
		}
		glEnd();
	}	
	if(!mode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}
void OBJ::RendModelTex(bool mode,GLuint tex)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST   /*GL_LINEAR*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(!mode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	for(int a=0;a<nFace;a++)
	{
		glBegin(GL_TRIANGLES);
		{
			if(IsFileHasNormalVector)
				glNormal3fv(NormalVector[Face[a].p[0].n-1].v); 
			if(IsFileHasTexCoord)
				glTexCoord2fv(TexCoord[Face[a].p[0].t-1].v);
			glVertex3fv(Vertex[Face[a].p[0].v-1].v);
		
			if(IsFileHasNormalVector)
				glNormal3fv(NormalVector[Face[a].p[1].n-1].v); 
			if(IsFileHasTexCoord)
				glTexCoord2fv(TexCoord[Face[a].p[1].t-1].v);
			glVertex3fv(Vertex[Face[a].p[1].v-1].v);

			if(IsFileHasNormalVector)
				glNormal3fv(NormalVector[Face[a].p[2].n-1].v); 
			if(IsFileHasTexCoord)
				glTexCoord2fv(TexCoord[Face[a].p[2].t-1].v);
			glVertex3fv(Vertex[Face[a].p[2].v-1].v);
		}
		glEnd();
	}	
	if(!mode)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}
bool OBJ::SaveFile(char fname[])
{
	//дописать что если нет нормалей то по-другому 
	//так же как и в загрузке
	FILE *file;
	file = fopen(fname,"w");
	if(file==NULL)
		return false;
	fprintf(file,"# %d vertices\n",nVertex);
	fprintf(file,"# %d texture coords\n",nTexCoord);
	fprintf(file,"# %d normal vector\n",nNormalVector);
	fprintf(file,"# %d nFace\n\n",nFace);
	for(int a=0;a<nVertex;a++)
		fprintf(file,"v %f %f %f\n",
		Vertex[a].v[0],
		Vertex[a].v[1],
		Vertex[a].v[2]);
	for(int a=0;a<nTexCoord;a++)
		fprintf(file,"vt %f %f %f\n",
		TexCoord[a].v[0],
		TexCoord[a].v[1],
		TexCoord[a].v[2]);
	for(int a=0;a<nNormalVector;a++)
		fprintf(file,"vn %f %f %f\n",
		NormalVector[a].v[0],
		NormalVector[a].v[1],
		NormalVector[a].v[2]);
	for(int a=0;a<nFace;a++)
		fprintf(file,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					Face[a].p[0].v,Face[a].p[0].t,Face[a].p[0].n,
					Face[a].p[1].v,Face[a].p[1].t,Face[a].p[1].n,
					Face[a].p[2].v,Face[a].p[2].t,Face[a].p[2].n);
	fclose(file);
	return true;
}
void OBJ::RendLikePrep()
{
	for(int a=0;a<nFace;a++)
	{
		glBegin(GL_TRIANGLES);
		{
			glVertex3f(Vertex[Face[a].p[0].v-1].v[0],0,Vertex[Face[a].p[0].v-1].v[2]);
			glVertex3f(Vertex[Face[a].p[1].v-1].v[0],0,Vertex[Face[a].p[1].v-1].v[2]);
			glVertex3f(Vertex[Face[a].p[2].v-1].v[0],0,Vertex[Face[a].p[2].v-1].v[2]);
		}
		glEnd();
	}

}