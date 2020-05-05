void PrintString(char *txt, float x,float y,float z)
{
	glRasterPos3f(x,y,z);
	glPushAttrib(GL_LIST_BIT);
	glListBase(Font - 32);
	glCallLists((GLsizei)strlen(txt), GL_UNSIGNED_BYTE, txt);
	glPopAttrib();
}
void PrintString(GLuint Font,char *txt, float x,float y)
{
	glRasterPos3f(x,y,0);
	glPushAttrib(GL_LIST_BIT);
	glListBase(Font - 32);
	glCallLists((GLsizei)strlen(txt), GL_UNSIGNED_BYTE, txt);
	glPopAttrib();
}
void PrintString(GLuint Font,char *txt, float x,float y,float z)
{
	glRasterPos3f(x,y,z);
	glPushAttrib(GL_LIST_BIT);
	glListBase(Font - 32);
	glCallLists((GLsizei)strlen(txt), GL_UNSIGNED_BYTE, txt);
	glPopAttrib();
}
void PrintString(char *txt, float x,float y)
{
	PrintString(txt, x, y,0);
}
GLuint BuildFont(int size, const char *fontname)
      {
          HFONT   font;
          HFONT   oldfont;
          GLuint basefont;
       
          basefont=glGenLists(255);
          font=CreateFontA(-size,0,0,0,   FW_BOLD,FALSE,FALSE,FALSE,
                              RUSSIAN_CHARSET,    OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,  
                              ANTIALIASED_QUALITY,    DEFAULT_QUALITY|DEFAULT_PITCH,
                              fontname);
       
          oldfont = (HFONT)SelectObject(hDC, font);
          wglUseFontBitmapsA(hDC, 32, 224, basefont);
          SelectObject(hDC, oldfont);
          DeleteObject(font);
          return basefont;
      }
       
GLvoid KillFont(GLuint basefont)
      {
          glDeleteLists(basefont, 255);
      }