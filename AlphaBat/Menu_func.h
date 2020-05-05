void MENU::CheckReturn()
{
	InitMenu();
	switch(WhatInMenu)
	{
	case MENU_OPTION:
		switch(MenuState)
		{
		case 0:
			WhatInMenu  = MENU_OPTION_AUDIO;
			break;
		case 1:
			WhatInMenu  = MENU_OPTION_GAME;
			break;
		case 2:
			WhatInMenu  = MENU_MAIN;
			break;
		}
		break;
	case MENU_OPTION_AUDIO:
		switch(MenuState)
		{
		case 0:
			Sound = !Sound;
			SaveSetting();
			break;
		case 1:
			WhatInMenu  = MENU_OPTION;
			break;
		}
		break;
	case MENU_OPTION_GAME:
		switch(MenuState)
		{
		case 0:
			MishenHelps = !MishenHelps;
			SaveSetting();
			break;
		case 1:
			WhatInMenu  = MENU_OPTION;
			break;
		}
		break;
	case MENU_PROFILE_ABOUT:
		switch(MenuState)
		{
		case 0:
			WhatInMenu = MENU_PROFILE;
			break;
		}
		break;
	/*case :
		switch(MenuState)
		{
		case:
			break;
		}
		break;
	case :
		switch(MenuState)
		{
		case:
			break;
		}
		break;
	case :
		switch(MenuState)
		{
		case:
			break;
		}
		break;*/
	case MENU_CONTINUE_GAME:
		if(MenuState == profile.CompleteLevel)
		{
			WhatInMenu = MENU_MAIN;
			break;
		}
		strcpy(NeedLoadLvl,Levels[MenuState].str); 
		WhatInMenu = MENU_NEW_GAME;
		break;
	case MENU_NEXT_LVL:
		switch(MenuState)
		{
		case 0:
			WhatInMenu = MENU_MAIN;
			TotalScore += Score;
			Score = 0;
			break;
		case 1:
			RestartLevel();
			ExitMenu();
			break;
		case 2:
			Level.LoadNextLvl();
			RestartLevel();
			ExitMenu();
		}
		break;
	case MENU_CHANGE_PROFILE:
		if(MenuState == profile.nUsers)
		{
			WhatInMenu = MENU_ENTER_NAME;
			break;
		}
		if(MenuState == profile.nUsers+1)
		{
			WhatInMenu = MENU_CHANGE_PROFILE_SURE_EXIT;
			break;
		}
		strcpy(profile.CurentUser,profile.Names[MenuState].str);
		WhatInMenu = MENU_PROFILE;
		profile.LoadProfile();
		InitMenu();
		break;
	case MENU_PROFILE:
		switch(MenuState)
		{
		case 0:
			WhatInMenu  = MENU_MAIN;
			break;
		case 1:
			WhatInMenu = MENU_CHANGE_ALPHABET;
			break;
		case 2:
			WhatInMenu  = MENU_PROFILE_ABOUT;
			break;
		case 3:
			WhatInMenu  = MENU_SURE_DELETE_PROFILE;
			break;
		case 4:
			WhatInMenu  = MENU_CHANGE_PROFILE;
			break;
		case 5:
			WhatInMenu  = MENU_PROFILE_SURE_EXIT;
			break;
		}
		break;
	case MENU_NEW_GAME:
		switch(MenuState)
		{
		case 0:
			Alphabet = false;
			Level.LoadMap(NeedLoadLvl);
			RestartLevel();
			ExitMenu();
			break;
		case 1:
			Alphabet = true;
			Level.LoadMap(NeedLoadLvl);
			RestartLevel();
			ExitMenu();
			break;
		case 2:
			Dificult = false;
			Alphabet = true;
			Level.LoadMap(NeedLoadLvl);
			RestartLevel();
			ExitMenu();
			break;
		}
		WhatInMenu = MENU_IN_GAME;
		break;
	case MENU_SURE_RETURN_TO_MAIN:
		switch(MenuState)
		{
		case 0:
			WhatInMenu = MENU_MAIN;
			break;
		case 1:
			WhatInMenu = MENU_IN_GAME;
			break;
		}
		break;
	case MENU_IN_GAME_SURE_EXIT:
		switch(MenuState)
		{
		case 1:
			WhatInMenu = MENU_IN_GAME;
			break;
		case 0:
			PostQuitMessage(0);
			break;
		}
		break;
	case MENU_MAIN_SURE_EXIT:
		switch(MenuState)
		{
		case 1:
			WhatInMenu = MENU_MAIN;
			break;
		case 0:
			PostQuitMessage(0);
			break;
		}
		break;
	case MENU_PROFILE_SURE_EXIT:
		switch(MenuState)
		{
		case 1:
			WhatInMenu = MENU_PROFILE;
			break;
		case 0:
			PostQuitMessage(0);
			break;
		}
		break;
	case MENU_CHANGE_PROFILE_SURE_EXIT:
		switch(MenuState)
		{
		case 1:
			WhatInMenu = MENU_CHANGE_PROFILE;
			break;
		case 0:
			PostQuitMessage(0);
			break;
		}
		break;
	case MENU_IN_GAME:
		switch(MenuState)
		{
		case 0:
			ExitMenu();
			break;
		case 1:
			RestartLevel();
			ExitMenu();
			break;
		case 2:
			WhatInMenu = MENU_SURE_RETURN_TO_MAIN;
			break;
		case 3:
			WhatInMenu = MENU_IN_GAME_SURE_EXIT;
			break;
		}
		break;
	case MENU_MAIN:
	default:
		switch(MenuState)
		{
		case 0:
			strcpy(NeedLoadLvl,FirstLvl);
			WhatInMenu  = MENU_NEW_GAME;
			break;
		case 1:
			WhatInMenu  = MENU_CONTINUE_GAME;
			break;
		case 2:
			WhatInMenu  = MENU_PROFILE;
			break;
		case 3:
			WhatInMenu  = MENU_OPTION;
			break;
		case 4:
			WhatInMenu  = MENU_MAIN_SURE_EXIT;
			break;
		}
		break;
	}
	ZeroMenu();
	//ExitMenu();
}