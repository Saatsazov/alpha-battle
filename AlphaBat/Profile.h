struct Game
{
	int Score;
	int mistakeScore;
};
class Profile
{
public:
	int nUsers;
	String *Names;
	Game **games;
	//Game CurentGame;
	char CurentUser[10];
	int Alph; // 0 - English 1 - Український 2 - Русский
	int CompleteLevel;
	int *nGameInLevel;//Количество игр на a'том уровне, временная переменная

	void LoadProfile();
	void SaveProfile();
	void LoadProfiles();
};
void Profile::LoadProfile()
{
	FILE *file;
	char fname[100];
	sprintf(fname,"resources\\profiles\\%s.txt",CurentUser);
	file = fopen(fname,"r");
	fscanf(file,"Alphabet %d\n",&Alph);
	fscanf(file,"CompleteLevel %d",&CompleteLevel);
	/*games = new Game* [CompleteLevel];
	nGameInLevel = new int[CompleteLevel];
	for(int a =0; a<CompleteLevel; a++)
	{
		fscanf(file,"\n%d",&nGameInLevel[a]);
		games[a] = new Game[nGameInLevel[a]];
		for(int b=0; b<nGameInLevel[a]; b++)
		{
			fscanf(file," %d %d",&games[a][b].Score,&games[a][b].mistakeScore);
		}
	}*/
	fclose(file);
}
void Profile::SaveProfile()
{
	/*FILE *file;
	char fname[100];
	sprintf(fname,"resources\\profiles\\%s.txt",CurentUser);
	file = fopen(fname,"w");
	fprintf(file,"Alphabet %d\n",Alph);
	fprintf(file,"CompleteLevel %d",CompleteLevel);
	for(int a =0; a<CompleteLevel; a++)
	{
		fprintf(file,"\n%d",&nGameInLevel);
		for(int b=0; b<nGameInLevel[a]; b++)
		{
			fprintf(file," %d %d",games[a][b].Score,games[a][b].mistakeScore);
		}
	}
	fclose(file);*/
}
void Profile::LoadProfiles()
{
	FILE *file;
	file = fopen("resources\\profiles\\main.txt","r");
	if(file == NULL)
	{
		file = fopen("resources\\profiles\\main.txt","w");
		fprintf(file,"\n");
		nUsers = 0;
		fclose(file);
		return;
	}
	fscanf(file,"%d",&nUsers);
	Names = new String[nUsers];
	for(int a = 0; a< nUsers; a++)
	{
		fscanf(file,"\n%s",Names[a].str);
	}
}
