//Much System
HWND hWnd;
HDC hDC;
HGLRC hRC;
DWORD timeDelta;
DWORD LTime;
POINT MousePos;
BOOL CursorState; // состояние курсора

GLuint Font;
GLuint FontBig;
GLuint FontVeryBig;
GLuint FontSmall;
bool Pause;//Состояние игры
char FirstLvl[] = "Level0";
char NeedLoadLvl[100];

bool key[256];

//game
int Score;
int TotalScore;
int numMistakes;
int IsGameOver;
bool Alphabet;
bool Dificult;
int nLevel;
String *Levels;

//OpenAL
ALuint ShotSrc,ShotBuffer,
ReloadSrc,ReloadBuffer,
DieSrc,DieBuffer,
FireSrc,FireBuffer;

bool TCannon;
bool TCannonUP;
float TCannonTr;

//temp for DEBUG
GLuint TexMishen;
//GLuint TexMishenId;

//Mishen
#define ALL_COLOR			4
float color[ALL_COLOR][3] = {{0.6,0.1,0.6},{0.3,0.5,0.3},{0.1,0.5,0.6},{0.1,0.7,0.1}};
