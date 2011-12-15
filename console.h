//class to do simple console functions that are different from the ANSI C++ version. I found tht gotoxy n textcolor etc doesn't work so...

class console
{
public:
	void static gotoxy (int x, int y)
	{
		COORD coord;
		coord.X = x; coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	int static getcursorx()
	{
		CONSOLE_SCREEN_BUFFER_INFO scrinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&scrinfo);
		return scrinfo.dwCursorPosition.X;
	}

	int static getcursory()
	{
		CONSOLE_SCREEN_BUFFER_INFO scrinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&scrinfo);
		return scrinfo.dwCursorPosition.Y;
	}

	void static textcolor(SHORT color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	void static drawHline(int startxcoord, int endxcoord)
	{
		for (int i=startxcoord;i<=endxcoord;i++)
		{
			cout<<"-";
		}
	}
};