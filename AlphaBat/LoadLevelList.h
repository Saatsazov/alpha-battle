void LoadLevelsList()
{
	FILE *file;
	fopen_s(&file,"Resources\\Maps\\LevelsList.txt","r");
	if(file == NULL)
		return;
	char str[100];
	int CountLevel=0;
	fscanf(file,"%d\n",&nLevel);
	Levels = new String[nLevel];
	while(fgets(str,100,file))
	{
		sscanf(str,"%s",Levels[CountLevel].str);
		CountLevel++;
	}
}
int GetIdLevel(char name[])
{
	for(int a=0; a<nLevel; a++)
	{
		if(!_stricmp(Levels[a].str,name))
			return a;
	}
	return 0;
}