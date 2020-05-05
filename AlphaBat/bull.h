struct bulet
{
	Vec3f Pos;
	Vec3f Vel;
	bool isZabraliScore;
};
class BULL
{
public:
	int n;
	bulet bull[50];
	void RendBull();
	void Reset()
	{
		n = 0;
		for(int a = 0; a<50; a++)
		{
			bull[a].Pos[0] = Level.LMapSize/2-Level.PrepSens;
			bull[a].Pos[1] = 0;
			bull[a].Pos[2] = Level.WMapSize/2-Level.PrepSens;
			bull[a].Vel[0] = bull[a].Vel[0] = bull[a].Vel[0] = 0;
			bull[a].isZabraliScore = true;
		}
	}
	BULL()
	{
		Reset();
	}
	void NewBull();
	void DO()
	{
		for(int x = 0 ; x < 50; x++)
		{
			for(int a=0;a<15;a++)
			{
				bull[x].Pos += bull[x].Vel;

				for(int a=0; a<Level.Mishen.nMishen; a++)
				{
					if(((bull[x].Pos[0]>Level.Mishen.mishen[a].Coord[0]-0.12*Level.Mishen.mishen[a].Size)&&(bull[x].Pos[0]<Level.Mishen.mishen[a].Coord[0]+0.12*Level.Mishen.mishen[a].Size))&&
							((bull[x].Pos[2]>Level.Mishen.mishen[a].Coord[2]-0.01*Level.Mishen.mishen[a].Size)&&(bull[x].Pos[2]<Level.Mishen.mishen[a].Coord[2]+0.01*Level.Mishen.mishen[a].Size))&&
							((bull[x].Pos[1]>Level.Mishen.mishen[a].Coord[1]-0.12*Level.Mishen.mishen[a].Size)&&(bull[x].Pos[1]<Level.Mishen.mishen[a].Coord[1]+0.12*Level.Mishen.mishen[a].Size)))

						{
							
							if(Level.Mishen.mishen[a].hp>0)
							{
								bull[x].isZabraliScore = true;
								if(Level.Mishen.mishen[a].IsNeedKillIt)
									Score+=abs
									(((Level.Mishen.mishen[a].Coord[0]-Player.GetPosX())*(Level.Mishen.mishen[a].Coord[0]-Player.GetPosX())+
									(Level.Mishen.mishen[a].Coord[2]-Player.GetPosX())*(Level.Mishen.mishen[a].Coord[2]-Player.GetPosZ()))*Level.Mishen.GetScore(a));
								else
								{
									Score-=10/abs(
									((Level.Mishen.mishen[a].Coord[0]-Player.GetPosX())*(Level.Mishen.mishen[a].Coord[0]-Player.GetPosX())+
									(Level.Mishen.mishen[a].Coord[2]-Player.GetPosX())*(Level.Mishen.mishen[a].Coord[2]-Player.GetPosZ()))*Level.Mishen.GetScore(a));
										numMistakes++;								
								}
								//PlaySound(L"Resources//shot.wav",NULL,SND_FILENAME | SND_ASYNC);
								if(Sound)
									alSourcePlay (ShotSrc);
								bull[x].Pos[0] = Level.LMapSize/2;
								bull[x].Pos[1] = 0;
								bull[x].Pos[2] = Level.WMapSize/2;
								bull[x].Vel[0] = bull[x].Vel[1] = bull[x].Vel[2] = 0;
								
								Level.Mishen.mishen[a].hp-=21;
								if(Level.Mishen.mishen[a].hp<0)
								{
									//"мишень умерла"
									if(Level.Mishen.mishen[a].IsNeedKillIt)
										Score+=3;
									else
										Score-=30;
									if(Sound)
										alSourcePlay (DieSrc);
								}
							
						}
					}
				}
				//и если координат по x больше чем Level.WMapSize » по y польше чем Level.LMapSize
				//то стоп пули
				if((bull[n].Pos[0]>Level.LMapSize/2)||(bull[n].Pos[0]<-Level.LMapSize/2)||(bull[n].Pos[2]>Level.WMapSize/2)||(bull[n].Pos[2]<-Level.WMapSize/2))
				{
					bull[x].Vel[0] = bull[x].Vel[1] = bull[x].Vel[2] = 0;
					bull[x].Pos[0] = Level.LMapSize/2;
					bull[x].Pos[1] = 0;
					bull[x].Pos[2] = Level.WMapSize/2;
					continue;
				}
				if(Level.Prep[int((Level.LMapSize/2-bull[x].Pos[0])/Level.PrepSens)][int((Level.WMapSize/2-bull[x].Pos[2])/Level.PrepSens)])
				{
					bull[x].Vel[0] = bull[x].Vel[1] = bull[x].Vel[2] = 0;
					if(!bull[x].isZabraliScore)
					{
						bull[x].isZabraliScore = true;
						Score-=5;
						numMistakes++;
					}
					//return /*Level.CoordBullets[Level.CountShot]=bull[x].Pos*/;	
				}
			}
			
		}
	}
};
float BullSize = 0.01f;
void BULL::NewBull()
{
	bull[n].isZabraliScore = false;
	bull[n].Pos = Player.GetPosition();
	bull[n].Pos[0] += cos(Player.GetHAngle())*(0.3f);
	bull[n].Pos[1] += sin(Player.GetVAngle())*(0.3f);
	bull[n].Pos[2] += sin(Player.GetHAngle())*(0.3f);
	if((bull[n].Pos[0]>Level.LMapSize/2)||(bull[n].Pos[0]<-Level.LMapSize/2)||(bull[n].Pos[2]>Level.WMapSize/2)||(bull[n].Pos[2]<-Level.WMapSize/2))
		return;
	bull[n].Vel[0]=cos(Player.GetHAngle())*(0.01f)*GameSpeed;//скорость
	bull[n].Vel[1]=sin(Player.GetVAngle())*(0.01f)*GameSpeed;
	bull[n].Vel[2]=sin(Player.GetHAngle())*(0.01f)*GameSpeed;
	if(n <49)
		n++;
	else
		n = 0;

}
void BULL::RendBull()
{
	for(int a = 0; a<50 ; a++)
	{
		switch(a%7)
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
		}
		if((bull[a].Vel[0]==bull[a].Vel[1])&&(bull[a].Vel[1]==bull[a].Vel[2])&&(bull[a].Vel[2]==0))
			glColor3f(0,0,0);
		glPushMatrix();
		{
			glTranslatef(bull[a].Pos.v[0],bull[a].Pos.v[1],bull[a].Pos.v[2]);
			glutSolidSphere(BullSize,16,16);
		}
		glPopMatrix();
	}
}

BULL bullets;
