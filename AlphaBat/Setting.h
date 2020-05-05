bool Sound;
bool MishenHelps;
float GameSpeed;
float HMouseSens;
float VMouseSens;
bool Sight;
float SightColor[3];

void SaveSetting()
{
	FILE *file;
	fopen_s(&file,"Resources\\Setting.ini","w");
	fprintf(file,"MouseSens %f %f\n",VMouseSens,HMouseSens);
	fprintf(file,"Sight %d %f %f %f\n",Sight,SightColor[0],SightColor[1],SightColor[2]);
	fprintf(file,"Sound %d\n",Sound);
	fprintf(file,"MishenHelps %d\n",MishenHelps);
	fprintf(file,"GameSpeed %f",GameSpeed);
	fclose(file);
}
void LoadSetting()
{

	FILE *file;
	fopen_s(&file,"Resources\\Setting.ini","r");
	if(file == NULL)
	{
		SaveSetting();
		return;
	}
	fscanf(file,"MouseSens %f %f\n",&VMouseSens,&HMouseSens);
	fscanf(file,"Sight %d %f %f %f\n",&Sight,&SightColor[0],&SightColor[1],&SightColor[2]);
	fscanf(file,"Sound %d\n",&Sound);
	fscanf(file,"MishenHelps %d\n",&MishenHelps);
	fscanf(file,"GameSpeed %f",&GameSpeed);
	fclose(file);
}
