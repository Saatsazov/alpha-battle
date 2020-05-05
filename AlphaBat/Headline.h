#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <glut.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <alut.h>
#pragma comment(lib, "alut.lib")
#pragma comment(lib, "OpenAL32.lib")

#include "String.h"
#include "resource.h"
#include "vector.h"
#include "Texture.h"

#include "SysGVar.h"
#include "Setting.h"
#include "SystemConst.h"
#include "WindowResize.h"
#include "Text.h"
#include "InitOpenGL.h"
#include "SystemInit.h"

#include "Alphabet.h"
#include "LoadLevelList.h"
#include "CreateTex.h"
#include "Profile.h"
#include "obj_loader_v2.h"
#include "GVar.h"
#include "Terrain.h"
#include "MAP_class.h"
#include "Menu_Class.h"
#include "GlobalEngineVar.h"
#include "Person.h"

#include "GlobalGameVar.h"
#include "bull.h"
#include "Restart.h"
#include "InitGame.h"
#include "Menu_Func.h"
#include "WndProc.h"
#include "Keyboard.h"
#include "RendLogo.h"
#include "Rendering.h"
#include "CleanUP.h"