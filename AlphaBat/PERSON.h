float NewX, NewZ;
class PERSON 
{
private:
	Vec3f Position;//точка где находится
	Vec3f Center;//точка куда смотрит
	float VAngle;//вертикальный угол наблюдателя
	float HAngle;//горизонтальный угол наблюдателя
	float Speed;//скоросьто на которую все скорости умножаються
	float ForwardSpeed;
	float BackSpeed;
	float LateralSpeed;
	//int Device;//на чем персонаж (машина пешком или на вертолете)))
	//пока не использую
	bool God; // как в кс
public:
	PERSON();
	void Look();
	void Forward();
	void Back();
	void Left();
	void Right();
	void SetPosition(Vec3f Pos);
	Vec3f GetPosition() const;
	void SetPosition(float x, float z);
	void HorRoll(float angle);
	void VertRoll(float angle);
	float GetHAngle() const;
	float GetVAngle() const;
	void SetHAngle(float angle);
	void SetVAngle(float angle);
	float GetPosX() const;
	float GetPosY() const;
	float GetPosZ() const;
	void Run(bool mode);
	//void Jump();
	//void SetDown();
	//void GetUp();
	//Vec3f Shot();
	void GOD()
	{
		God=!God;
	}

};
/*void PERSON::Jump()
{
}*/
void PERSON::Run(bool mode)
{
	if(mode)
		Speed=2.0f;
	else
		Speed=1.0f;
}

PERSON::PERSON()
{
	ForwardSpeed=0.01f;
	BackSpeed=0.009;
	LateralSpeed=0.005;
	Speed=1.0f;
	Position[1]=0.3f;
	Position[2]=0.5f;
	Center[1]=0.25f;
	HAngle=-1.3f;
	VAngle=0.1f;
	God=false;
}
void PERSON::SetPosition(float x,float z)
{
	Position[0]=x;
	Position[2]=z;
}
void PERSON::Forward()
{
	if(God)
	{
		Position[0]+=cos(HAngle)*Level.PrepSens;
		Position[2]+=sin(HAngle)*Level.PrepSens;
		Position[1]+=sin(VAngle)*Level.PrepSens;
	}

	else
	for(float units=0.0f; units<ForwardSpeed*Speed*(timeDelta/100.0f); units+=Level.PrepSens)
	{
		NewX=Position[0]+cos(HAngle)*Level.PrepSens*4;
		NewZ=Position[2]+sin(HAngle)*Level.PrepSens*4;
		for(int a=0; a<Level.Mishen.nMishen; a++)
		{
			if(Level.Mishen.mishen[a].hp<0)
				continue;
			if( (NewX>Level.Mishen.mishen[a].Coord[0]-0.12*Level.Mishen.mishen[a].Size)&&(NewX<Level.Mishen.mishen[a].Coord[0]+0.12*Level.Mishen.mishen[a].Size)&&//ox
				(abs(NewZ-Level.Mishen.mishen[a].Coord[2])<0.03))//oz
				return;
		}
		//+0.5f для математического округление!!
		if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
		{
			Position[0]=NewX-cos(HAngle)*Level.PrepSens*3;
			Position[2]=NewZ-sin(HAngle)*Level.PrepSens*3;
			Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
		}
		else
		{
			if(!Level.Prep[int((Level.LMapSize/2-Position[0])/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
			{
				Position[2]=NewZ-sin(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-Position[2])/Level.PrepSens)])	
			{
				Position[0]=NewX-cos(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			else
				break;
		}
	}	
	if((Level.PosForNextLevel[0] - Position[0])*(Level.PosForNextLevel[0] - Position[0])+
		(Level.PosForNextLevel[1] - Position[1])*(Level.PosForNextLevel[1] - Position[1])+
		(Level.PosForNextLevel[2] - Position[2])*(Level.PosForNextLevel[2] - Position[2])<0.09)
	{
		if(!_stricmp(Level.MapName,"Level9"))
		{
			Menu.WhatInMenu = MENU_GAME_OVER;
		}
		else
		{
			Menu.WhatInMenu = MENU_NEXT_LVL;
		}
		Menu.EnterMenu();
	}
}
/*void PERSON::Forward()
{
	if(God)
	{
		Position[0]+=cos(HAngle)*Level.PrepSens;
		Position[2]+=sin(HAngle)*Level.PrepSens;
		Position[1]+=sin(VAngle)*Level.PrepSens;
	}

	else
		//for()
		for(int a=0;a<Level.ObjMap.nFace;a++)
		{
			if(CollDetect(
				Level.ObjMap.Vertex[Level.ObjMap.Face[a].p[0].v-1],
				Level.ObjMap.Vertex[Level.ObjMap.Face[a].p[1].v-1],
				Level.ObjMap.Vertex[Level.ObjMap.Face[a].p[2].v-1],
				Center,Position))
				return;
			

		}
		{
					Position[0]+=cos(HAngle)*Level.PrepSens;
					Position[2]+=sin(HAngle)*Level.PrepSens;
			}
}*/
void PERSON::Back()
{
	if(God)
	{
		Position[0]-=cos(HAngle)*Level.PrepSens;
		Position[2]-=sin(HAngle)*Level.PrepSens;
		Position[1]-=sin(VAngle)*Level.PrepSens;
	}
	else
	for(float units=0.0f; units<BackSpeed*Speed*timeDelta/100.0f; units+=Level.PrepSens)
	{
		NewX=Position[0]-cos(HAngle)*Level.PrepSens*4;
		NewZ=Position[2]-sin(HAngle)*Level.PrepSens*4;
		for(int a=0; a<Level.Mishen.nMishen; a++)
		{
			if(Level.Mishen.mishen[a].hp<0)
				continue;
			if( (NewX>Level.Mishen.mishen[a].Coord[0]-0.12*Level.Mishen.mishen[a].Size)&&(NewX<Level.Mishen.mishen[a].Coord[0]+0.12*Level.Mishen.mishen[a].Size)&&//ox
				(abs(NewZ-Level.Mishen.mishen[a].Coord[2])<0.03))//oz
				return;
		}
		//+0.5f для математического округление!!
		if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
		{
			Position[0]=NewX+cos(HAngle)*Level.PrepSens*3;
			Position[2]=NewZ+sin(HAngle)*Level.PrepSens*3;
			Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
		}
		else
		{
			if(!Level.Prep[int((Level.LMapSize/2-Position[0])/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
			{
				Position[2]=NewZ+sin(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeight((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-Position[2])/Level.PrepSens)])	
			{
				Position[0]=NewX+cos(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			else
				break;
		}
		
	}
	if((Level.PosForNextLevel[0] - Position[0])*(Level.PosForNextLevel[0] - Position[0])+
		(Level.PosForNextLevel[1] - Position[1])*(Level.PosForNextLevel[1] - Position[1])+
		(Level.PosForNextLevel[2] - Position[2])*(Level.PosForNextLevel[2] - Position[2])<0.09)
	{
		if(!_stricmp(Level.MapName,"Level9"))
		{
			Menu.WhatInMenu = MENU_GAME_OVER;
		}
		else
		{
			Menu.WhatInMenu = MENU_NEXT_LVL;
		}
		Menu.EnterMenu();
	}
}
void PERSON::Left()
{
	if(God)
	{
		Position[0]+=sin(HAngle)*Level.PrepSens;
		Position[2]-=cos(HAngle)*Level.PrepSens;
	}
	else
	for(float units=0.0f; units<LateralSpeed*Speed*timeDelta/100.0f; units+=Level.PrepSens)
	{
		NewX=Position[0]+sin(HAngle)*Level.PrepSens*4;
		NewZ=Position[2]-cos(HAngle)*Level.PrepSens*4;
		for(int a=0; a<Level.Mishen.nMishen; a++)
		{
			if(Level.Mishen.mishen[a].hp<0)
				continue;
			if( (NewX>Level.Mishen.mishen[a].Coord[0]-0.12*Level.Mishen.mishen[a].Size)&&(NewX<Level.Mishen.mishen[a].Coord[0]+0.12*Level.Mishen.mishen[a].Size)&&//ox
				(abs(NewZ-Level.Mishen.mishen[a].Coord[2])<0.03))//oz
				return;
		}
		//+0.5f для математического округление!!
		if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
		{
			Position[0]=NewX-sin(HAngle)*Level.PrepSens*3;
			Position[2]=NewZ+cos(HAngle)*Level.PrepSens*3;
			Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
		}
		else
		{
			if(!Level.Prep[int((Level.LMapSize/2-Position[0])/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
			{
				Position[2]=NewZ+cos(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-Position[2])/Level.PrepSens)])	
			{
				Position[0]=NewX-sin(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			else
				break;
		}
	}	
	if((Level.PosForNextLevel[0] - Position[0])*(Level.PosForNextLevel[0] - Position[0])+
		(Level.PosForNextLevel[1] - Position[1])*(Level.PosForNextLevel[1] - Position[1])+
		(Level.PosForNextLevel[2] - Position[2])*(Level.PosForNextLevel[2] - Position[2])<0.09)
	{
		if(!_stricmp(Level.MapName,"Level9"))
		{
			Menu.WhatInMenu = MENU_GAME_OVER;
		}
		else
		{
			Menu.WhatInMenu = MENU_NEXT_LVL;
		}
		Menu.EnterMenu();
	}
}
void PERSON::Right()
{
	if(God)
	{
		Position[0]-=sin(HAngle)*Level.PrepSens;
		Position[2]+=cos(HAngle)*Level.PrepSens;
	}
	else
	for(float units=0.0f; units<LateralSpeed*Speed*timeDelta/100.0f; units+=Level.PrepSens)
	{
		NewX=Position[0]-sin(HAngle)*Level.PrepSens*4;
		NewZ=Position[2]+cos(HAngle)*Level.PrepSens*4;
		for(int a=0; a<Level.Mishen.nMishen; a++)
		{
			if(Level.Mishen.mishen[a].hp<0)
				continue;
			if( (NewX>Level.Mishen.mishen[a].Coord[0]-0.12*Level.Mishen.mishen[a].Size)&&(NewX<Level.Mishen.mishen[a].Coord[0]+0.12*Level.Mishen.mishen[a].Size)&&//ox
				(abs(NewZ-Level.Mishen.mishen[a].Coord[2])<0.03))//oz
				return;
		}
		//+0.5f для математического округление!!
		if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
		{
			Position[0]=NewX+sin(HAngle)*Level.PrepSens*3;
			Position[2]=NewZ-cos(HAngle)*Level.PrepSens*3;
			Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
		}
		else
		{
			if(!Level.Prep[int((Level.LMapSize/2-Position[0])/Level.PrepSens)][int((Level.WMapSize/2-NewZ)/Level.PrepSens)])
			{
				Position[2]=NewZ-cos(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			if(!Level.Prep[int((Level.LMapSize/2-NewX)/Level.PrepSens)][int((Level.WMapSize/2-Position[2])/Level.PrepSens)])	
			{
				Position[0]=NewX+sin(HAngle)*Level.PrepSens*3;
				Position[1]=Level.HeightMap->
				getHeightPerson((Level.LMapSize/2-Position[0])/Level.HeightmapSens,
				(Level.WMapSize/2-Position[2])/Level.HeightmapSens)+0.3f;
			}
			else
				break;
		}
	}	
	if((Level.PosForNextLevel[0] - Position[0])*(Level.PosForNextLevel[0] - Position[0])+
		(Level.PosForNextLevel[1] - Position[1])*(Level.PosForNextLevel[1] - Position[1])+
		(Level.PosForNextLevel[2] - Position[2])*(Level.PosForNextLevel[2] - Position[2])<0.09)
	{
		if(!_stricmp(Level.MapName,"Level9"))
		{
			Menu.WhatInMenu = MENU_GAME_OVER;
		}
		else
		{
			Menu.WhatInMenu = MENU_NEXT_LVL;
		}
		Menu.EnterMenu();
	}
}

void PERSON::Look()
{
	Center[0]=Position[0]+cos(HAngle);
	Center[1]=Position[1]+sin(VAngle);
	Center[2]=Position[2]+sin(HAngle);
	gluLookAt(
		Position[0],Position[1],Position[2],
		Center[0],Center[1],Center[2],
		0,1,0);
}
void PERSON::SetPosition(Vec3f Pos)
{
	Position=Pos;
}
Vec3f PERSON::GetPosition() const
{
	return Position;
}
void PERSON::HorRoll(float angle)
{
	HAngle+=angle;
}
void PERSON::VertRoll(float angle)
{
	if(((VAngle<0.8f)&&(angle>0))||((angle<0)&&(VAngle>-0.8f)))
		VAngle+=angle;
}
float PERSON::GetHAngle() const
{
	return HAngle;
}
float PERSON::GetVAngle() const
{
	return VAngle;
}
float PERSON::GetPosX() const
{
	return Position[0];
}
float PERSON::GetPosY() const
{
	return Position[1];
}
float PERSON::GetPosZ() const
{
	return Position[2];
}
void PERSON::SetHAngle(float angle)
{
	HAngle=angle;
}
void PERSON::SetVAngle(float angle)
{
	VAngle=angle;
}
